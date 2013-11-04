#ifndef LOG_SINK_H
#define LOG_SINK_H

#include "log_level.h"

typedef struct log_sink log_sink_t;

void log_sink_log_message (log_sink_t *sink, log_level_t level, const char *source, const char *message);
void log_sink_set_threshold (log_sink_t *sink, log_level_t threshold);

#endif // LOG_SINK_H
