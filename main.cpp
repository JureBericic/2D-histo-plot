#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include "color_palettes.hpp"
#include "ps_helper_functions.hpp"
#include "settings.hpp"


using namespace std;


int main()
{
    cout << endl << "Welcome to plotter!" << endl << endl << endl;


	bool adv_settings = 0;
    cout << endl << "Change default settings: (0/1)" << endl << " -> ";
    cin >> adv_settings;

    if (adv_settings) settings::change_settings();


	string in_file = "input.txt";
	string out_file = "output.ps";
	int x_bins = 0;
	int y_bins = 0;
	int pages = 0;
	int color_palette = 0;
	int no_colors = 0;

	cout << "Name of input file:" << endl << " -> ";
	cin >> in_file;
	cout << endl << "Name of output file: " << endl << " -> ";
	cin >> out_file;
	cout << endl << "Binning (x_bins y_bins pages): " << endl << " -> ";
	cin >> x_bins >> y_bins >> pages;
	cout << endl << "Select color palette: " << endl;
	cout << " 1 : colz" << endl;
	cout << " 2 : grayscale" << endl;
	cout << " 3 : inverted grayscale" << endl;
	cout << " 4 : heat" << endl;
	cout << " 5 : inverted heat" << endl;
	cout << " -> ";
	cin >> color_palette;
	cout << endl << "Number of colors in palette: " << endl << " -> ";
	cin >> no_colors;

	vector<double> minxs (pages, 0);
	vector<double> maxxs (pages, 0);
	vector<double> minys (pages, 0);
	vector<double> maxys (pages, 0);
	vector<string> xlabels (pages, "");
	vector<string> ylabels (pages, "");
	vector<string> titles (pages, "");
	string dummy;

	for (int i=0; i<pages; i++)
	{
		cout << endl << "Plot " << i+1 << ":";
		if (settings::display_axis)
		{
		    cout << endl << "Range for x axis:" << endl << " -> ";
            cin >> minxs.at(i) >> maxxs.at(i);
            cout << endl << "Range for y axis:" << endl << " -> ";
            cin >> minys.at(i) >> maxys.at(i);
            // Need to read dummy line because cin and getline() do not match well.
            getline (cin, dummy);
		}
		if (settings::display_title)
		{
		    cout << endl << "Plot title:" << endl << " -> ";
            getline (cin, titles.at(i));
		}
        if (settings::display_label)
        {
            cout << endl << "Label for x axis:" << endl << " -> ";
            getline (cin, xlabels.at(i));
            cout << endl << "Label for y axis:" << endl << " -> ";
            getline (cin, ylabels.at(i));
        }
	}


    ifstream infile (in_file);

    // Min and max data value will be needed for scaling the color palette.
    // This values will get overwritten at the beginning of the search.
	double min = 0;
	double max = 0;
    bool tmp_b = 1;
    double tmp_d;
    string tmp_s = "";

    if (settings::scale_range_type==2)
    {
        min = settings::scale_min;
        max = settings::scale_max;
    }
    else
    {
        // Trying to support NaN and Inf. This is to get first values for min and max.
        // Need to skip NaNs and Infs here.
        while (tmp_b)
        {
            infile >> tmp_s;
            if (tmp_s=="NAN" || tmp_s=="NaN" || tmp_s=="Nan" || tmp_s=="nan") continue;
            else if (tmp_s=="INF" || tmp_s=="Inf" || tmp_s=="inf") continue;
            else
            {
                min = max = strtod(tmp_s.c_str(), NULL);
                tmp_b = 0;
            }
        }
        // Trying to support NaN and Inf. This is to get values for min and max.
        // Need to skip NaNs and Infs here.
        while (infile >> tmp_s)
        {
            if (tmp_s=="NAN" || tmp_s=="NaN" || tmp_s=="Nan" || tmp_s=="nan") continue;
            else if (tmp_s=="INF" || tmp_s=="Inf" || tmp_s=="inf") continue;
            else
            {
                tmp_d = strtod(tmp_s.c_str(), NULL);
                if (tmp_d<min) min = tmp_d;
                if (tmp_d>max) max = tmp_d;
            }
        }
    }
    vector<double> reds (no_colors+2, 0);
    vector<double> greens (no_colors+2, 0);
    vector<double> blues (no_colors+2, 0);

    switch (color_palette)
    {
        case 1:
            palette_colz (reds, greens, blues, no_colors);
            break;
        case 2:
            palette_grayscale (reds, greens, blues, no_colors);
            break;
        case 3:
            palette_inv_grayscale (reds, greens, blues, no_colors);
            break;
        case 4:
            palette_heat (reds, greens, blues, no_colors);
            break;
        case 5:
            palette_inv_heat (reds, greens, blues, no_colors);
            break;
    }


    ofstream outfile (out_file);

    outfile << "%!PS" << endl;
    outfile << "%%Pages: " << pages << " " << pages << endl;
    define_boundingbox (outfile);

    def_sizes (outfile, x_bins, y_bins);

	def_pixel (outfile);

    outfile << endl;
    for (int i=0; i<no_colors+2; i++)
    {
        outfile << "/color" << i << " {" << reds.at(i) << " " << greens.at(i) << " " << blues.at(i) << " setrgbcolor} def" << endl;
    }

	def_colorscale (outfile, no_colors);
	def_border_main (outfile);
	def_border_scale (outfile);

	def_fonts (outfile);
	def_shows (outfile);

	outfile << "%%EndProlog" << endl;


	// Go to beginning of the infile.
	infile.clear();
	infile.seekg(0, ios::beg);

	// To not calculate it over and over again in the while loop.
	double k = 1.0*no_colors / (max-min);

	int xbin = 1;
	int ybin = 1;
	int page = 1;

    // Trying to support NaN and Inf. This is to make actual plot.
    // Need to assing correct colors to NaNs and Infs (no_colors and no_colors+1).
	while (infile >> tmp_s)
	{
	    int color = 0;
	    if (tmp_s=="NAN" || tmp_s=="NaN" || tmp_s=="Nan" || tmp_s=="nan") color = no_colors;
        else if (tmp_s=="INF" || tmp_s=="Inf" || tmp_s=="inf") color = no_colors + 1;
        else
        {
            tmp_d = strtod(tmp_s.c_str(), NULL);
            color = (tmp_d - min) * k;
            // Colors go from 0 to no_colors, but at max range, we would get no_colors.
            if (color>=no_colors) color = no_colors - 1;
            if (color<0) color = 0;
        }

		if (xbin==1 && ybin==1)
		{
			outfile << endl << "%%Page: " << page << " " << page << endl << endl;
			outfile << "72 72 translate" << endl;
			outfile << "gsave" << endl << endl;
		}
		outfile << "color" << color << " pixel";

		if (xbin==x_bins &&  ybin==y_bins)
		{
		    outfile << " grestore gsave" << endl << endl;
		    if (settings::display_color_scale) outfile << "colorscale grestore gsave" << endl;
		    if (settings::display_border) outfile << "border_main" << endl;
		    if (settings::display_color_scale && settings::display_border) outfile << "border_scale grestore gsave" << endl;

		    if (settings::display_title) write_title(outfile, titles.at(page-1));
		    if (settings::display_label) write_labels (outfile, xlabels.at(page-1), ylabels.at(page-1));
		    if (settings::display_axis) write_axis (outfile, minxs.at(page-1), maxxs.at(page-1), minys.at(page-1), maxys.at(page-1));
		    if (settings::display_color_scale && settings::display_scale) {write_scale (outfile, min, max); outfile << "grestore gsave" << endl;}

			outfile << endl << "showpage" << endl;
			xbin = 1;
			ybin = 1;
			page++;
		}
		else if (ybin==y_bins)
		{
			outfile << " nextcolumn" << endl << endl;
			ybin = 1;
			xbin++;
		}
		else
		{
			outfile << " nextpixel" << endl;
			ybin++;
		}
	}

	outfile << endl << "%%EOF";



    outfile.close();

	infile.close();




    cout << endl << endl << endl << "Finished!" << endl;
    return 0;
}























