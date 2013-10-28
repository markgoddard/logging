#include "log_system.h"
#include "log_sink_stdout.h"
#include "log_sink_file.h"
#include "module.h"

int main (void)
{
	log_system_t *system = log_system_create (0);

	log_sink_stdout_t *stdout_sink = log_sink_stdout_create (0);
	log_sink_t *stdout_handle = log_sink_stdout_get_sink (stdout_sink);
	log_system_add_sink (system, stdout_handle);

	log_sink_file_t *file_sink = log_sink_file_create ("main.log", 0);
	log_sink_t *file_handle = log_sink_file_get_sink (file_sink);
	log_system_add_sink (system, file_handle);

	logger_t *root = log_system_get_root_logger (system);
	logger_t *child = logger_create_child (root, "child");

	do_stuff (root);
	do_stuff (child);

	logger_dereference (child);

	log_system_remove_sink (system, file_handle);
	log_sink_file_destroy (file_sink);

	log_system_remove_sink (system, stdout_handle);
	log_sink_stdout_destroy (stdout_sink);

	log_system_destroy (system);
}

