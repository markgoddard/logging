#include "log_sink_file.h"
#include "log_sink_interface.h"

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/

// Private object definition

struct log_sink_file
{
	log_sink_t sink;

	log_level_t level;

	const char *filename;
	FILE *file;
};

/*****************************************************************************/

// Private interface declaration

static void log_sink_file_log_message (log_sink_file_t *sink, log_level_t level, const char *source, const char *message);
static log_level_t log_sink_file_get_level (log_sink_file_t *sink);
static void log_sink_file_set_level (log_sink_file_t *sink, log_level_t level);

/*****************************************************************************/

// Interface definition

static void log_sink_file_log_message_fn (log_sink_t *sink, log_level_t level, const char *source, const char *message)
{
	log_sink_file_log_message ((log_sink_file_t *) sink, level, source, message);
}

static log_level_t log_sink_file_get_level_fn (log_sink_t *sink)
{
	return log_sink_file_get_level ((log_sink_file_t *) sink);
}

static void log_sink_file_set_level_fn (log_sink_t *sink, log_level_t level)
{
	log_sink_file_set_level ((log_sink_file_t *) sink, level);
}

static log_sink_interface_t log_sink_file_interface =
{
	log_sink_file_log_message_fn,
	log_sink_file_get_level_fn,
	log_sink_file_set_level_fn,
};

/*****************************************************************************/

// Private interface definition

static void log_sink_file_log_message (log_sink_file_t *sink, log_level_t level, const char *source, const char *message)
{
	if (level >= sink->level)
	{
		fprintf (sink->file, "%s: [%s]: %s", log_level_to_string (level), source, message);
	}
}

static log_level_t log_sink_file_get_level (log_sink_file_t *sink)
{
	return sink->level;
}

static void log_sink_file_set_level (log_sink_file_t *sink, log_level_t level)
{
	sink->level = level;
}

/*****************************************************************************/

// Public interface definition

log_sink_file_t *log_sink_file_create (const char *filename, log_level_t level)
{
	log_sink_file_t *sink = (log_sink_file_t *) malloc (sizeof (log_sink_file_t));
	if (!sink) return NULL;

	sink->sink.obj = sink;
	sink->sink.interface = &log_sink_file_interface;
	sink->level = level;

	sink->filename = filename;
	sink->file = fopen (filename, "w");
	if (!sink->file)
	{
		free (sink);
		return NULL;
	}

	return sink;
}

void log_sink_file_destroy (log_sink_file_t *sink)
{
	fflush (sink->file);
	fclose (sink->file);
	free (sink);
}

log_sink_t *log_sink_file_get_sink (log_sink_file_t *sink)
{
	return &sink->sink;
}
