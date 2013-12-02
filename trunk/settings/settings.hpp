#pragma once
#ifndef SETTINGS_HPP_INCLUDED
#define SETTINGS_HPP_INCLUDED 1


#include <string>
#include <iostream>


namespace settings
{
    extern int title_size;
    extern int label_size;
    extern int axis_size;

    extern bool display_color_scale;
    extern bool display_border;
    extern bool display_title;
    extern bool display_label;
    extern bool display_axis;
    extern bool display_scale;

	extern double plot_size_x;
	extern double plot_size_y;
    extern double color_palette_width;
    extern double color_palette_margin;

    extern int scale_range_type;


    extern double scale_min;
    extern double scale_max;


    void list_settings();

    void change_settings();
}


#endif // SETTINGS_HPP_INCLUDED
