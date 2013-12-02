#pragma once
#ifndef COLOR_PALETTES_HPP_INCLUDED
#define COLOR_PALETTES_HPP_INCLUDED


#include <iostream>
#include <vector>


using namespace std;


void palette_colz (vector<double>& reds,
                   vector<double>& greens,
                   vector<double>& blues,
                   int& no_colors);

void palette_grayscale (vector<double>& reds,
                        vector<double>& greens,
                        vector<double>& blues,
                        int& no_colors);

void palette_inv_grayscale (vector<double>& reds,
                            vector<double>& greens,
                            vector<double>& blues,
                            int& no_colors);

void palette_heat (vector<double>& reds,
                   vector<double>& greens,
                   vector<double>& blues,
                   int& no_colors);

void palette_inv_heat (vector<double>& reds,
                       vector<double>& greens,
                       vector<double>& blues,
                       int& no_colors);

#endif // COLOR_PALETTES_HPP_INCLUDED
