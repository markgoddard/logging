#include "module.h"
#include <pthread.h>
#include <unistd.h>

static void *thread_fn (void *arg)
{
	logger_t *logger = (logger_t *) arg;

	logger_reference (logger);

	for (unsigned i = 0; i < 5; i++)
	{
		log_message (logger, 0, "Hello, %s\n", "world (0)");
		log_message (logger, 1, "Hello, %s\n", "world (1)");
		//sleep (1);
	}

	logger_dereference (logger);

	return NULL;
}

void do_stuff (logger_t *logger)
{
	logger_t *module_logger = logger_create_child (logger, "module");

	pthread_t thid1;
	pthread_t thid2;
	
	logger_t *logger1 = logger_create_child (module_logger, "thread 1");
	logger_t *logger2 = logger_create_child (module_logger, "thread 2");

	logger_dereference (module_logger);

	log_message (module_logger, 0, "Starting thread 1\n");
	pthread_create (&thid1, NULL, thread_fn, (void *) logger1);

	log_message (module_logger, 0, "Starting thread 2\n");
	pthread_create (&thid2, NULL, thread_fn, (void *) logger2);

	pthread_join (thid1, NULL);
	pthread_join (thid2, NULL);

	logger_dereference (logger1);
	logger_dereference (logger2);
}

