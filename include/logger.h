#ifndef LOGGER_H
#define LOGGER_H

#include "log_level.h"

#include <stdarg.h>

typedef struct logger logger_t;

void log_message (logger_t *logger, log_level_t level, const char *fmt, ...);
void log_vmessage (logger_t *logger, log_level_t level, const char *fmt, va_list va_args);

logger_t *logger_create_child (logger_t *logger, const char *name);
void logger_reference (logger_t *logger);
void logger_dereference (logger_t *logger);

#endif // LOGGER_H
