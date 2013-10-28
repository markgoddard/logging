#include "log_sink.h"
#include "log_sink_interface.h"

/*****************************************************************************/

void log_sink_log_message (log_sink_t *sink, log_level_t level, const char *source, const char *message)
{
	sink->interface->log_message (sink->obj, level, source, message);
}

void log_sink_set_level (log_sink_t *sink, log_level_t level)
{
	sink->interface->set_level (sink->obj, level);
}
