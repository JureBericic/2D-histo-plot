#include "color_palettes.hpp"


using namespace std;


void palette_colz (vector<double>& reds,
                   vector<double>& greens,
                   vector<double>& blues,
                   int& no_colors)
{
    for (int i=0; i<no_colors; i++)
    {
        double x = 1.0*i / (no_colors - 1);

        if (x<0.11)
        {
            reds.at(i) = -3.636*x + 0.400;  greens.at(i) = 0;  blues.at(i) = 1;
        }
        else if (x<0.33)
        {
            reds.at(i) = 0;  greens.at(i) = 4.545*x - 0.500;  blues.at(i) = 1;
        }
        else if (x<0.56)
        {
            reds.at(i) = 0;  greens.at(i) = 1;  blues.at(i) = -4.348*x + 2.435;
        }
        else if (x<0.78)
        {
            reds.at(i) = 4.545*x - 2.545;  greens.at(i) = 1;  blues.at(i) = 0;
        }
        else
        {
            reds.at(i) = 1;  greens.at(i) = -4.545*x + 4.545;  blues.at(i) = 0;
        }
	}
	// NaN colors
	reds.at(no_colors) = 0.2;
	greens.at(no_colors) = 0.2;
	blues.at(no_colors) = 0.2;
	// Inf colors
	reds.at(no_colors) = 0.6;
	greens.at(no_colors) = 0.6;
	blues.at(no_colors) = 0.6;
}


void palette_grayscale (vector<double>& reds,
                        vector<double>& greens,
                        vector<double>& blues,
                        int& no_colors)
{
    for (int i=0; i<no_colors; i++)
    {
        double x = 1.0*i / (no_colors - 1);

        reds.at(i) = greens.at(i) = blues.at(i) = 1 - x;
    }
}


void palette_inv_grayscale (vector<double>& reds,
                            vector<double>& greens,
                            vector<double>& blues,
                            int& no_colors)
{
    for (int i=0; i<no_colors; i++)
    {
        double x = 1.0*i / (no_colors - 1);

        reds.at(i) = greens.at(i) = blues.at(i) = x;
    }
}


void palette_heat (vector<double>& reds,
                   vector<double>& greens,
                   vector<double>& blues,
                   int& no_colors)
{
    for (int i=0; i<no_colors; i++)
    {
        double x = 1.0*i / (no_colors - 1);

        if (x<0.33)
        {
            reds.at(i) = 3.0303*x;  greens.at(i) = 0;  blues.at(i) = 0;
        }
        else if (x<0.67)
        {
            reds.at(i) = 1;  greens.at(i) = 2.94118*x-0.970588;  blues.at(i) = 0;
        }
        else
        {
            reds.at(i) = 1;  greens.at(i) = 1;  blues.at(i) = 3.0303*x-2.0303;
        }
	}
}


void palette_inv_heat (vector<double>& reds,
                       vector<double>& greens,
                       vector<double>& blues,
                       int& no_colors)
{
    for (int i=0; i<no_colors; i++)
    {
        double x = 1.0*i / (no_colors - 1);

        if (x<0.33)
        {
            reds.at(i) = 1;  greens.at(i) = 1;  blues.at(i) = 1-3.0303*x;
        }
        else if (x<0.67)
        {
            reds.at(i) = 1;  greens.at(i) = 1.97059-2.94118*x;  blues.at(i) = 0;
        }
        else
        {
            reds.at(i) = 3.0303-3.0303*x;  greens.at(i) = 0;  blues.at(i) = 0;
        }
	}
}





