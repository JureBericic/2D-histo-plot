set (ps_helper_functions_SRCS ps_helper_functions.cpp)


include_directories (${PROJECT_SOURCE_DIR}/settings)


add_library (ps_helper_functions ${ps_helper_functions_SRCS})
target_link_libraries (ps_helper_functions settings)
