#include "log_sink_stdout.h"
#include "log_sink_interface.h"

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/

// Private object definition

struct log_sink_stdout
{
	log_sink_t sink;
};

/*****************************************************************************/

// Private interface declaration

static void log_sink_stdout_log_message (log_sink_stdout_t *sink, log_level_t level, const char *source, const char *message);

/*****************************************************************************/

// Interface definition

static void log_sink_stdout_log_message_fn (log_sink_t *sink, log_level_t level, const char *source, const char *message)
{
	log_sink_stdout_log_message ((log_sink_stdout_t *) sink, level, source, message);
}

static log_sink_interface_t log_sink_stdout_interface =
{
	log_sink_stdout_log_message_fn,
};

/*****************************************************************************/

// Private interface definition

static void log_sink_stdout_log_message (log_sink_stdout_t *sink, log_level_t level, const char *source, const char *message)
{
       printf ("%s: [%s]: %s", log_level_to_string (level), source, message);
}

/*****************************************************************************/

// Public interface definition

log_sink_stdout_t *log_sink_stdout_create (log_level_t threshold)
{
	log_sink_stdout_t *sink = (log_sink_stdout_t *) malloc (sizeof (log_sink_stdout_t));
	if (!sink) return NULL;

	sink->sink.obj = sink;
	sink->sink.interface = &log_sink_stdout_interface;
    sink->sink.threshold = threshold;
	return sink;
}

void log_sink_stdout_destroy (log_sink_stdout_t *sink)
{
	free (sink);
}

log_sink_t *log_sink_stdout_get_sink (log_sink_stdout_t *sink)
{
	return &sink->sink;
}
