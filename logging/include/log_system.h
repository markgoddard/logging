#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include "logger.h"
#include "log_sink.h"

typedef struct log_system log_system_t;

log_system_t *log_system_create (log_level_t level);
void log_system_destroy (log_system_t *system);

logger_t *log_system_get_root_logger (log_system_t *system);

void log_system_add_sink (log_system_t *system, log_sink_t *sink);
void log_system_remove_sink (log_system_t *system, log_sink_t *sink);

#endif // LOG_SYSTEM_H
