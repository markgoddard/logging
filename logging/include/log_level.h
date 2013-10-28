#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

typedef enum
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
} log_level_t;

const char *log_level_to_string (log_level_t level);

#endif // LOG_LEVEL_H
