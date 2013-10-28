#ifndef LOG_SINK_FILE_H
#define LOG_SINK_FILE_H

#include "log_sink.h"

typedef struct log_sink_file log_sink_file_t;

log_sink_file_t *log_sink_file_create (const char *filename, log_level_t level);
void log_sink_file_destroy (log_sink_file_t *sink);

log_sink_t *log_sink_file_get_sink (log_sink_file_t *sink);

#endif // LOG_SINK_FILE_H
