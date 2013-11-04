#ifndef LOG_SINK_STDOUT_H
#define LOG_SINK_STDOUT_H

#include "log_sink.h"

typedef struct log_sink_stdout log_sink_stdout_t;

log_sink_stdout_t *log_sink_stdout_create (log_level_t threshold);
void log_sink_stdout_destroy (log_sink_stdout_t *sink);

log_sink_t *log_sink_stdout_get_sink (log_sink_stdout_t *sink);

#endif // LOG_SINK_STDOUT_H
