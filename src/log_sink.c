#include "log_sink.h"
#include "log_sink_interface.h"

/*****************************************************************************/

void log_sink_log_message (log_sink_t *sink, log_level_t level, const char *source, const char *message)
{
    if (level >= sink->threshold)
    {
        sink->interface->log_message (sink->obj, level, source, message);
    }
}

void log_sink_set_threshold (log_sink_t *sink, log_level_t threshold)
{
    sink->threshold = threshold;
}
