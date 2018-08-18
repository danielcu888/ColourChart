#include "IdenticalColsColourRampGenerator.h"
#include "ColourRampGenerator.h"
#include "ColourRGB565.h"

IdenticalColsColourRampGenerator::IdenticalColsColourRampGenerator(const ColourRGB565& tl_,
																   const ColourRGB565& bl_,
																   unsigned int width_,
																   unsigned int height_,
																   unsigned int min_row_,
																   unsigned int min_col_)
																   :
																   ColourRampGenerator(width_, height_, min_row_, min_col_),
																   top_col(tl_),
																   bottom_col(bl_)
{}

bool IdenticalColsColourRampGenerator::get_row(unsigned int col_,
											   unsigned int row_,
											   unsigned int width_,
											   unsigned short *pixels)
{
	// Each column is identical so each pixel in the row will be the same
	if(!valid_row(row_) || !valid_col(col_) || get_height() == 1)
		return false;
	// interpolate between top and bottom row to desired row
	const float frac = static_cast<float>(row_ - get_min_row())/static_cast<float>(get_height()-1);
	const unsigned short c = ColourRGB565::interpolate(top_col, bottom_col, frac).get_col(); // top colours are at row zero
	for(unsigned int i = 0; i < width_ && valid_col(col_+i); ++i)
		pixels[i] = c;
	return true;
}

