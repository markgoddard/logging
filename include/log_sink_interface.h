#ifndef LOG_SINK_INTERFACE_H
#define LOG_SINK_INTERFACE_H

#include "log_sink.h"

typedef struct
{
	void (*log_message) (log_sink_t *sink, log_level_t level, const char *source, const char *message);

} log_sink_interface_t;

struct log_sink
{
	void *obj;
	log_sink_interface_t *interface;
    log_level_t threshold;
};

#endif // LOG_SINK_INTERFACE_H
