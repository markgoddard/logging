#include "log_system.h"
#include "log_source.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __USE_UNIX98
#include <pthread.h>
#include <assert.h>

/*****************************************************************************/

// Private object definition

struct log_system
{
	pthread_mutex_t mutex;

	log_level_t level;

	log_source_t *root;

	log_sink_t **sinks;
	unsigned num_sinks;
};

/*****************************************************************************/

// Private interface

static void log_system_lock (log_system_t *system)
{
	assert (pthread_mutex_lock (&system->mutex) == 0);
}

static void log_system_unlock (log_system_t *system)
{
	assert (pthread_mutex_unlock (&system->mutex) == 0);
}

static void log_system_log_message (log_system_t *system, log_source_t *source, log_level_t level, const char *fmt, va_list va_args)
{
	char source_name[256];
	unsigned r = log_source_get_name (source, source_name, sizeof source_name, "/");

	char message_str[256];
	vsprintf (message_str, fmt, va_args);

	for (unsigned i = 0; i < system->num_sinks; i++)
	{
		log_sink_log_message (system->sinks[i], level, source_name, message_str);
	}
}

/*****************************************************************************/

// Source interface

static void log_system_lock_fn (void *system)
{
	log_system_lock ((log_system_t *) system);
}

static void log_system_unlock_fn (void *system)
{
	log_system_unlock ((log_system_t *) system);
}

static void log_system_log_message_fn (void *system, log_source_t *source, log_level_t level, const char *fmt, va_list va_args)
{
	log_system_log_message ((log_system_t *) system, source, level, fmt, va_args);
}

static const log_source_interface_t log_system_source_interface =
{
	log_system_lock_fn,
	log_system_unlock_fn,
	log_system_log_message_fn,
};

/*****************************************************************************/

// Public interface

log_system_t *log_system_create (log_level_t level)
{
	log_system_t *system = (log_system_t *) malloc (sizeof (log_system_t));

	system->root = log_source_create_root ((void *) system, &log_system_source_interface);
	if (!system->root)
	{
		free (system);
		return NULL;
	}

	pthread_mutex_init (&system->mutex, NULL);
	system->level = level;
	system->sinks = NULL;
	system->num_sinks = 0;
	return system;
}

void log_system_destroy (log_system_t *system)
{
	assert (system->num_sinks == 0);

	if (system->sinks)
	{
		free (system->sinks);
		system->sinks = NULL;
	}

	log_source_destroy_root (system->root);
	system->root = NULL;

	free (system);
}

logger_t *log_system_get_root_logger (log_system_t *system)
{
	return log_source_get_logger (system->root);
}

void log_system_add_sink (log_system_t *system, log_sink_t *sink)
{
	log_system_lock (system);
	system->sinks = (log_sink_t **) realloc (system->sinks, (system->num_sinks + 1) * sizeof (log_sink_t *));
	system->sinks[system->num_sinks] = sink;
	system->num_sinks++;
	log_system_unlock (system);
}

void log_system_remove_sink (log_system_t *system, log_sink_t *sink)
{
	log_system_lock (system);
	for (unsigned i = 0; i < system->num_sinks; i++)
	{
		if (system->sinks[i] == sink)
		{
			memmove (&system->sinks[i], &system->sinks[i+1], system->num_sinks - i - 1);
			break;
		}
	}

	system->sinks = (log_sink_t **) realloc (system->sinks, (system->num_sinks - 1) * sizeof (log_sink_t *));
	system->num_sinks--;
	log_system_unlock (system);
}

