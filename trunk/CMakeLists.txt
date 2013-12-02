cmake_minimum_required (VERSION 2.6)
project (2D-histo-plot)


add_subdirectory (settings)
add_subdirectory (ps_helper_functions)
add_subdirectory (color_palettes)


include_directories (${PROJECT_SOURCE_DIR}/settings)
include_directories (${PROJECT_SOURCE_DIR}/ps_helper_functions)
include_directories (${PROJECT_SOURCE_DIR}/color_palettes)


set (2D_histo_plot_SRCS 2D_histo_plot.cpp)
add_executable (plot ${2D_histo_plot_SRCS})
target_link_libraries (plot color_palettes ps_helper_functions settings )
