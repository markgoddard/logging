#include "logger_interface.h"

/*****************************************************************************/

void log_message (logger_t *logger, log_level_t level, const char *fmt, ...)
{
	va_list va_args;
	va_start (va_args, fmt);
	logger->interface->log_message (logger->obj, level, fmt, va_args);
	va_end (va_args);
}

void log_vmessage (logger_t *logger, log_level_t level, const char *fmt, va_list va_args)
{
	logger->interface->log_message (logger->obj, level, fmt, va_args);
}

logger_t *logger_create_child (logger_t *logger, const char *name)
{
	return logger->interface->create_child (logger->obj, name);
}

void logger_reference (logger_t *logger)
{
	logger->interface->reference (logger);
}

void logger_dereference (logger_t *logger)
{
	logger->interface->dereference (logger);
}

