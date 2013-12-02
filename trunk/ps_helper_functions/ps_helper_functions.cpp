#include "ps_helper_functions.hpp"


using namespace std;


void define_boundingbox (ofstream& outfile)
{
	int x0 = 0;   // Lower left corner.
	int y0 = 0;
	int x1 = 0;   // Upper right corner.
	int y1 = 0;

	// Yes, this is very ugly, but I did't want to write all the if statements. Maybe I will rewrite this, maybe not :)
	// And no, I will not comment why it is like this :)
	// Edit: This will need a rewrite, because an assumption is made that label font is bigger (or equal) than axis font.
	x0 = y0 = 72 - static_cast<int>(settings::display_label) * settings::label_size * 4./3
	          - static_cast<int>(settings::display_axis && !settings::display_label) * settings::axis_size * 4./3
	          - static_cast<int>(settings::display_border) * 1;
	x1 = 72 + settings::plot_size_x * 72
	     + static_cast<int>(settings::display_color_scale) * (settings::color_palette_width + settings::color_palette_margin) * 72
	     + static_cast<int>(settings::display_border) * 1;
	y1 = 72 + settings::plot_size_y * 72
	     + static_cast<int>(settings::display_title) * settings::title_size * 4./3
	     + static_cast<int>(settings::display_border) * 1;

	outfile << "%%BoundingBox: " << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
}


void def_sizes (ofstream& outfile, int& x_bins, int& y_bins)
{
	outfile << "/inch {72 mul} def" << endl;
    outfile << "/sizex {" << settings::plot_size_x << " inch} def  /sizey {" << settings::plot_size_y << " inch} def" << endl;
    outfile << "/nx " << x_bins << " def  /ny " << y_bins << " def" << endl;
    outfile << "/xpixsize {sizex nx div} def  /ypixsize {sizey ny div} def" << endl;
    outfile << "/titlesize {" << settings::title_size << "} def ";
    outfile << "/labelsize {" << settings::label_size << "} def ";
    outfile << "/axissize {" << settings::axis_size << "} def" << endl;
}


void def_pixel (ofstream& outfile)
{
	outfile << "/nextpixel {0 ypixsize translate} def" << endl;
    outfile << "/nextcolumn {xpixsize ny 1 sub -1 mul ypixsize mul translate} def" << endl;
	outfile << "/pixel {" << endl;
    outfile << "\tnewpath" << endl;
    outfile << "\t\t0 0 moveto" << endl;
    outfile << "\t\txpixsize 0 lineto" << endl;
    outfile << "\t\txpixsize ypixsize lineto" << endl;
    outfile << "\t\t0 ypixsize lineto" << endl;
    outfile << "\tclosepath fill" << endl;
    outfile << "} def" << endl;
}


void def_colorscale (ofstream& outfile, int no_colors)
{
	outfile << endl << "/csmargin {" << settings::color_palette_margin << " inch} def  /cswidth {" << settings::color_palette_width << " inch} def";
	outfile << endl << "/colorscale {" << endl;
	outfile << "\tsizex csmargin add 0 translate" << endl;
	for (int i=0; i<no_colors; i++)
	{
		outfile << "\tcolor" << i << " newpath" << endl;
		outfile << "\t\t0 " << i << " sizey mul " << no_colors << " div moveto" << endl;
		outfile << "\t\tcswidth " << i << " sizey mul " << no_colors << " div lineto" << endl;
		outfile << "\t\tcswidth "  << i << " 1 add sizey mul "  << no_colors << " div lineto" << endl;
		outfile << "\t\t0 " << i << " 1 add sizey mul " << no_colors << " div lineto" << endl;
		outfile << "\tclosepath fill" << endl;
	}
	outfile << "} def" << endl;
}


void def_border_main (ofstream& outfile)
{
	outfile << endl << "/border_main {" << endl;
	outfile << "\t2 setlinewidth" << endl;
	outfile << "\tnewpath" << endl;
	outfile << "\t\t0 0 moveto" << endl;
	outfile << "\t\t0 sizey lineto" << endl;
	outfile << "\t\tsizex sizey lineto" << endl;
	outfile << "\t\tsizex 0 lineto" << endl;
	outfile << "\tclosepath stroke" << endl;
	for (int i=1; i<=3; i++)
	{
		outfile << "\tnewpath" << endl;
		outfile << "\t\tsizex " << i << " 4 div mul 0 moveto" << endl;
		outfile << "\t\tsizex " << i << " 4 div mul 11 lineto" << endl;
		outfile << "\tstroke" << endl;
		outfile << "\tnewpath" << endl;
		outfile << "\t\tsizex " << i << " 4 div mul sizey moveto" << endl;
		outfile << "\t\tsizex " << i << " 4 div mul sizey 11 sub lineto" << endl;
		outfile << "\tstroke" << endl;
		outfile << "\tnewpath" << endl;
		outfile << "\t\t0 sizey " << i << " 4 div mul moveto" << endl;
		outfile << "\t\t11 sizey " << i << " 4 div mul lineto" << endl;
		outfile << "\tstroke" << endl;
		outfile << "\tnewpath" << endl;
		outfile << "\t\tsizex sizey " << i << " 4 div mul moveto" << endl;
		outfile << "\t\tsizex 11 sub sizey " << i << " 4 div mul lineto" << endl;
		outfile << "\tstroke" << endl;
	}
	outfile << "} def" << endl;
}


void def_border_scale (ofstream& outfile)
{
	outfile << endl << "/border_scale {" << endl;
	outfile << "\tsizex csmargin add 0 translate" << endl;
	outfile << "\t2 setlinewidth" << endl;
	outfile << "\tnewpath" << endl;
	outfile << "\t\t0 0 moveto" << endl;
	outfile << "\t\t0 sizey lineto" << endl;
	outfile << "\t\tcswidth sizey lineto" << endl;
	outfile << "\t\tcswidth 0 lineto" << endl;
	outfile << "\tclosepath stroke" << endl;
	for (int i=1; i<=3; i++)
	{
		outfile << "\tnewpath" << endl;
		outfile << "\t\t0 sizey " << i << " 4 div mul moveto" << endl;
		outfile << "\t\tcswidth sizey " << i << " 4 div mul lineto" << endl;
		outfile << "\tstroke" << endl;
	}
	outfile << "} def" << endl;
}


void def_shows (ofstream& outfile)
{
	outfile << endl << "/centershow {" << endl;
	outfile << "\tdup stringwidth pop" << endl;
	outfile << "\t0 exch sub 2 div" << endl;
	outfile << "\t0 rmoveto" << endl;
	outfile << "\tshow" << endl;
	outfile << "} def" << endl;

	outfile << endl << "/rightshow {" << endl;
	outfile << "\tdup stringwidth pop" << endl;
	outfile << "\t0 exch sub" << endl;
	outfile << "\t0 rmoveto" << endl;
	outfile << "\tshow" << endl;
	outfile << "} def" << endl;
}


void def_fonts (ofstream& outfile)
{
	outfile << endl << "/titlefont {/Helvetica findfont titlesize scalefont setfont} def" << endl;
	outfile << endl << "/labelfont {/Helvetica findfont labelsize scalefont setfont} def" << endl;
	outfile << endl << "/axisfont {/Helvetica findfont axissize scalefont setfont} def" << endl;
}


void write_title (ofstream& outfile, string title)
{
	outfile << endl << "titlefont" << endl;
	// Displace text for 1 point if border is present.
	if (settings::display_border) outfile << "sizex 2 div sizey titlesize 3 div add 1 add moveto (" << title << ") centershow" << endl;
	else outfile << "sizex 2 div sizey titlesize 3 div add moveto (" << title << ") centershow" << endl;
}


void write_labels (ofstream& outfile, string labelx, string labely)
{
	outfile << endl << "labelfont" << endl;
	// Displace text for 1 point if border is present.
	if (settings::display_border)
	{
		outfile << "sizex 2 div -1 labelsize mul 1 sub moveto (" << labelx << ") centershow" << endl;
		outfile << "90 rotate sizey 2 div labelsize 3 div 1 add moveto (" << labely << ") centershow -90 rotate" << endl;
	}
	else
	{
		outfile << "sizex 2 div -1 labelsize mul moveto (" << labelx << ") centershow" << endl;
		outfile << "90 rotate sizey 2 div labelsize 3 div moveto (" << labely << ") centershow -90 rotate" << endl;
	}
}


void write_axis (ofstream& outfile, double minx, double maxx, double miny, double maxy)
{
	// Displace text for 1 point if border is present.
	if (settings::display_border)
	{
		outfile << endl << "axisfont" << endl;
		outfile << "0 -1 axissize mul 1 sub moveto (" << minx << ") show" << endl;
		outfile << "sizex -1 axissize mul 1 sub moveto (" << maxx << ") rightshow" << endl;
		outfile << "90 rotate 0 axissize 3 div 1 add moveto (" << miny << ") show" << endl;
		outfile << "sizey axissize 3 div 1 add moveto (" << maxy << ") rightshow -90 rotate" << endl;
	}
	else
	{
		outfile << endl << "axisfont" << endl;
		outfile << "0 -1 axissize mul moveto (" << minx << ") show" << endl;
		outfile << "sizex -1 axissize mul moveto (" << maxx << ") rightshow" << endl;
		outfile << "90 rotate 0 axissize 3 div moveto (" << miny << ") show" << endl;
		outfile << "sizey axissize 3 div moveto (" << maxy << ") rightshow -90 rotate" << endl;
	}
}


void write_scale (ofstream& outfile, double min, double max)
{
	outfile << endl << "axisfont" << endl;
	// Need to make two rotations for 45deg, since one 90deg rotation also rotates the paper.
	// This only happens if only write_scale is called, without other texts.
	// Have not found legit solution, so hack it is...
	outfile << "sizex csmargin add 0 translate 45 rotate 45 rotate" << endl;
	outfile << "0 axissize 3 div moveto (" << min << ") show" << endl;
	outfile << "sizey axissize 3 div moveto (" << max << ") rightshow" << endl;
}


