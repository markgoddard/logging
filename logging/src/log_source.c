#include "log_source.h"
#include "logger_interface.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*****************************************************************************/

// Private object definition

struct log_source
{
	logger_t logger;

	void *obj;
	const log_source_interface_t *interface;

	log_source_t *parent;
	log_source_t *children;
	log_source_t *next_child;

	unsigned ref_count;

	const char *name;
	bool level_applied;
	log_level_t level;
};

/*****************************************************************************/

// Private interface declaration

static log_source_t *log_source_create (void *obj, const log_source_interface_t *interface, const char *name);
static log_source_t *log_source_create_child (log_source_t *parent, const char *name);
static void log_source_destroy (log_source_t *source);
static void log_source_reference (log_source_t *source);
static void log_source_dereference (log_source_t *source);
static void log_source_lock (log_source_t *source);
static void log_source_unlock (log_source_t *source);
static void log_source_log_message (log_source_t *source, log_level_t level, const char *fmt, va_list va_args);

/*****************************************************************************/

// Logger interface

static logger_t *log_source_create_child_fn (void *obj, const char *name)
{
	log_source_t *parent = (log_source_t *) obj;

	log_source_lock (parent);
	log_source_t *source = log_source_create_child (parent, name);
	log_source_unlock (parent);

	if (!source) return NULL;

	return &source->logger;
}

static void log_source_reference_fn (void *obj)
{
	log_source_t *parent = (log_source_t *) obj;

	log_source_lock (parent);
	log_source_reference (parent);
	log_source_unlock (parent);
}

static void log_source_dereference_fn (void *obj)
{
	log_source_t *parent = (log_source_t *) obj;

	log_source_lock (parent);
	log_source_dereference (parent);
	log_source_unlock (parent);
}

static void log_source_log_message_fn (void *obj, log_level_t level, const char *fmt, va_list va_args)
{
	log_source_t *parent = (log_source_t *) obj;

	log_source_lock (parent);
	log_source_log_message (parent, level, fmt, va_args);
	log_source_unlock (parent);
}

static logger_interface_t log_source_interface =
{
	log_source_create_child_fn,
	log_source_reference_fn,
	log_source_dereference_fn,
	log_source_log_message_fn,
};

/*****************************************************************************/

// Private interface

static void log_source_add_child (log_source_t *parent, log_source_t *child)
{
	child->parent = parent;
	assert (child->next_child == NULL);

	if (!parent->children)
	{
		// First child
		parent->children = child;
	}
	else
	{
		// Add to end of children list
		log_source_t *next = parent->children;
		while (next->next_child) next = next->next_child;
		next->next_child = child;
	}
}

static void log_source_remove_child (log_source_t *parent, log_source_t *child)
{
	child->parent = NULL;

	if (parent->children == child)
	{
		parent->children = child->next_child;
	}
	else
	{
		log_source_t *prev = parent->children;
		while (prev->next_child != child) prev = prev->next_child;

		assert (prev->next_child == child);
		prev->next_child = child->next_child;
	}
}

static log_source_t *log_source_create (void *obj, const log_source_interface_t *interface, const char *name)
{
	log_source_t *source = (log_source_t *) malloc (sizeof (log_source_t));
	if (!source) return NULL;

	source->logger.obj = source;
	source->logger.interface = &log_source_interface;
	source->obj = obj;
	source->interface = interface;
	source->parent = NULL;
	source->children = NULL;
	source->next_child = NULL;
	source->ref_count = 1;
	source->name = name;
	source->level_applied = false;
	source->level = LOG_DEBUG;
	return source;
}

static log_source_t *log_source_create_child (log_source_t *parent, const char *name)
{
	log_source_t *child = log_source_create (parent->obj, parent->interface, name);
	if (!child) return NULL;

	log_source_add_child (parent, child);
	log_source_reference (parent);

	return child;
}

static void log_source_destroy (log_source_t *source)
{
	assert (!source->children);

	if (source->parent)
	{
		log_source_t *parent = source->parent;
		log_source_remove_child (parent, source);
		log_source_dereference (parent);
	}

	free (source);
}

static void log_source_reference (log_source_t *source)
{
	source->ref_count++;
}

static void log_source_dereference (log_source_t *source)
{
	source->ref_count--;
	if (source->ref_count == 0)
	{
		log_source_destroy (source);
	}
}

static void log_source_lock (log_source_t *source)
{
	source->interface->lock (source->obj);
}

static void log_source_unlock (log_source_t *source)
{
	source->interface->unlock (source->obj);
}

static void log_source_log_message (log_source_t *source, log_level_t level, const char *fmt, va_list va_args)
{
	if (!source->level_applied || level >= source->level)
		source->interface->log_message (source->obj, source, level, fmt, va_args);
}

/*****************************************************************************/

// Public interface

log_source_t *log_source_create_root (void *obj, const log_source_interface_t *interface)
{
	log_source_t *root = log_source_create (obj, interface, NULL);
	if (!root) return NULL;

	return root;
}

void log_source_destroy_root (log_source_t *root)
{
	assert (root->ref_count == 1);

	log_source_dereference (root);
}

logger_t *log_source_get_logger (log_source_t *source)
{
	return &source->logger;
}

unsigned log_source_get_name (const log_source_t *source, char *name_buf, unsigned name_buf_len, const char *separator)
{
	if (name_buf_len == 0) return 0;

	name_buf[0] = '\0';

	unsigned r = 0;
	if (source->parent)
	{
		r += log_source_get_name (source->parent, name_buf, name_buf_len, separator);
	}

	if (source->name)
	{
		r += snprintf (&name_buf[r], name_buf_len - r, "%s%s", r > 0 ? separator : "", source->name);
	}
	return r;
}

log_level_t log_source_get_level (log_source_t *source)
{
	return source->level;
}

void log_source_set_level (log_source_t *source, log_level_t level)
{
	source->level = level;
}
