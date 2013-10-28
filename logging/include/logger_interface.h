#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include "logger.h"
#include <stdarg.h>

typedef struct logger_interface
{
	logger_t *(*create_child) (void *obj, const char *name);
	void (*reference) (void *obj);
	void (*dereference) (void *obj);

	void (*log_message) (void *obj, log_level_t level, const char *fmt, va_list va_args);

} logger_interface_t;

struct logger
{
	void *obj;
	logger_interface_t *interface;
};

#endif // LOGGER_INTERFACE_H
