#include "settings.hpp"


namespace settings
{
// Sizes in points.
int title_size = 18;
int label_size = 16;
int axis_size = 14;

bool display_color_scale = 1;
bool display_border = 1;
bool display_title = 1;
bool display_label = 1;
bool display_axis = 1;
bool display_scale = 1;

// Sizes in inches.
double plot_size_x = 5;
double plot_size_y = 5;
double color_palette_width = 0.2;
double color_palette_margin = 0.3;

int scale_range_type = 1;


double scale_min = 0;
double scale_max = 0;


void list_settings()
{
    std::cout << std::endl << "Settings available:" << std::endl << std::endl;
    std::cout << "1 -> Display color scale: " << display_color_scale << std::endl;
    std::cout << "2 -> Display border: " << display_border << std::endl;
    std::cout << "3 -> Display title: " << display_title << std::endl;
    std::cout << "4 -> Display label: " << display_label << std::endl;
    std::cout << "5 -> Display axis: " << display_axis << std::endl;
    std::cout << "6 -> Display scale: " << display_scale << std::endl;
    std::cout << "7 -> Title text size: " << title_size << std::endl;
    std::cout << "8 -> Label text size: " << label_size << std::endl;
    std::cout << "9 -> Axis text size: " << axis_size << std::endl;
    std::cout << "10 -> Plot size x: " << plot_size_x << std::endl;
    std::cout << "11 -> Plot size y: " << plot_size_y << std::endl;
    std::cout << "12 -> Color palette width: " << color_palette_width << std::endl;
    std::cout << "13 -> Color palette margin: " << color_palette_margin << std::endl;
    std::cout << "14 -> Scale range type: " << scale_range_type << std::endl;
    std::cout << std::endl << "15 -> Show list of settings again" << std::endl;
    std::cout << "16 -> Exit settings editor and run program" << std::endl;
}

void change_settings()
{
    list_settings();

    bool read_settings = 1;
    while (read_settings)
    {
        int num = 0;
        std::cout << std::endl << "num: ";
        std::cin >> num;

        switch (num)
        {
        case 1:
            std::cout << "val: ";
            std::cin >> display_color_scale;
            break;
        case 2:
            std::cout << "val: ";
            std::cin >> display_border;
            break;
        case 3:
            std::cout << "val: ";
            std::cin >> display_title;
            break;
        case 4:
            std::cout << "val: ";
            std::cin >> display_label;
            break;
        case 5:
            std::cout << "val: ";
            std::cin >> display_axis;
            break;
        case 6:
            std::cout << "val: ";
            std::cin >> display_scale;
            break;
        case 7:
            std::cout << "val: ";
            std::cin >> title_size;
            break;
        case 8:
            std::cout << "val: ";
            std::cin >> label_size;
            break;
        case 9:
            std::cout << "val: ";
            std::cin >> axis_size;
            break;
        case 10:
            std::cout << "val: ";
            std::cin >> plot_size_x;
            break;
        case 11:
            std::cout << "val: ";
            std::cin >> plot_size_y;
            break;
        case 12:
            std::cout << "val: ";
            std::cin >> color_palette_width;
            break;
        case 13:
            std::cout << "val: ";
            std::cin >> color_palette_margin;
            break;
        case 14:
            std::cout << "  1 -> min/max from data" << std::endl;
            std::cout << "  2 -> user defined range" << std::endl;
            std::cout << "  num: ";
            std::cin >> scale_range_type;
            if (scale_range_type==2)
            {
                std::cout << "  min max: ";
                std::cin >> scale_min >> scale_max;
            }
            break;

        case 15:
            list_settings();
            break;
        case 16:
            read_settings = 0;
            break;
        default:
            break;
        }
    }

    std::cout << std::endl;
}
}
