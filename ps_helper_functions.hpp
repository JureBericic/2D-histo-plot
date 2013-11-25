#pragma once
#ifndef PS_HELPER_FUNCTIONS_HPP_INCLUDED
#define PS_HELPER_FUNCTIONS_HPP_INCLUDED


#include <fstream>


#include "settings.hpp"


using namespace std;


void define_boundingbox (ofstream& outfile);

void def_sizes (ofstream& outfile, int& x_bins, int& y_bins);

void def_pixel (ofstream& outfile);

void def_colorscale (ofstream& outfile, int no_colors);

void def_border_main (ofstream& outfile);

void def_border_scale (ofstream& outfile);

void def_shows (ofstream& outfile);

void def_fonts (ofstream& outfile);

void write_title (ofstream& outfile, string title);

void write_labels (ofstream& outfile, string labelx, string labely);

void write_axis (ofstream& outfile, double minx, double maxx, double miny, double maxy);

void write_scale (ofstream& outfile, double min, double max);


#endif // PS_HELPER_FUNCTIONS_HPP_INCLUDED
