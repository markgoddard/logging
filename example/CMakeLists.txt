include_directories(${PROJECT_SOURCE_DIR}/include)

list(APPEND LOGGING_EXAMPLE_SRC main.c)
list(APPEND LOGGING_EXAMPLE_SRC module.c)

add_executable(main ${LOGGING_EXAMPLE_SRC})
target_link_libraries(main logging pthread rt)
