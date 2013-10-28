#ifndef LOG_SOURCE_H
#define LOG_SOURCE_H

#include "logger.h"

typedef struct log_source log_source_t;

typedef struct
{
	void (*lock) (void *obj);
	void (*unlock) (void *obj);
	void (*log_message) (void *obj, log_source_t *source, log_level_t level, const char *fmt, va_list va_args);

} log_source_interface_t;

log_source_t *log_source_create_root (void *obj, const log_source_interface_t *interface);

void log_source_destroy_root (log_source_t *root);

logger_t *log_source_get_logger (log_source_t *source);

unsigned log_source_get_name (const log_source_t *source, char *name_buf, unsigned name_buf_len, const char *separator);

log_level_t log_source_get_level (log_source_t *source);

void log_source_set_level (log_source_t *source, log_level_t level);

#endif // LOG_SOURCE_H
