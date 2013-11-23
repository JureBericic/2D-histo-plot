cmake_minimum_required (VERSION 2.6)
project (2D-histo-plot)

set (color_palettes_SRCS color_palettes.cpp)
set (ps_helper_functions_SRCS ps_helper_functions.cpp)
set (settings_SRCS settings.cpp)

add_library (color_palettes ${color_palettes_SRCS})
add_library (ps_helper_functions ${ps_helper_functions_SRCS})
add_library (settings ${settings_SRCS})

set (2D_histo_plot_SRCS 2D_histo_plot.cpp)
add_executable (plot ${2D_histo_plot_SRCS})
target_link_libraries (plot color_palettes ps_helper_functions settings )



