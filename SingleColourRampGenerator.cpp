#include "SingleColourRampGenerator.h"
#include "ColourRampGenerator.h"
#include "ColourRGB565.h"

SingleColourRampGenerator::SingleColourRampGenerator(const ColourRGB565& tl_,
													 unsigned int width_,
													 unsigned int height_,
													 unsigned int min_row_,
													 unsigned int min_col_)
													:
													 ColourRampGenerator(width_, height_, min_row_, min_col_),
													 c(tl_)
{}

bool SingleColourRampGenerator::get_row(unsigned int col_,
										unsigned int row_,
										unsigned int width_,
										unsigned short *pixels)
{
	if(!valid_row(row_) || !valid_col(col_))
		return false;
	for(unsigned int i = 0; i < width_ && valid_col(col_+i); ++i)
		pixels[i] = c.get_col();
	return true;
}




