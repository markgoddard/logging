#ifndef LOG_SINK_INTERFACE_H
#define LOG_SINK_INTERFACE_H

#include "log_sink.h"

typedef struct log_sink_interface
{
	void (*log_message) (log_sink_t *sink, log_level_t level, const char *source, const char *message);
	log_level_t (*get_level) (log_sink_t *sink);
	void (*set_level) (log_sink_t *sink, log_level_t level);

} log_sink_interface_t;

struct log_sink
{
	void *obj;
	log_sink_interface_t *interface;
};

#endif // LOG_SINK_INTERFACE_H
