include_directories(${PROJECT_SOURCE_DIR}/include)

list(APPEND LOGGING_SRC logger.c)
list(APPEND LOGGING_SRC log_level.c)
list(APPEND LOGGING_SRC log_sink.c)
list(APPEND LOGGING_SRC log_sink_file.c)
list(APPEND LOGGING_SRC log_sink_stdout.c)
list(APPEND LOGGING_SRC log_source.c)
list(APPEND LOGGING_SRC log_system.c)

add_library(logging ${LOGGING_SRC})
