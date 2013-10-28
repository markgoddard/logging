#include "log_level.h"

const char *log_level_to_string (log_level_t level)
{
	switch (level)
	{
		case LOG_DEBUG: return "D";
		case LOG_INFO: return "I";
		case LOG_WARNING: return "W";
		case LOG_ERROR: return "E";
		default: return "?";
	}
}

