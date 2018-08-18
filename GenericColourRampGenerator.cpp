#include "GenericColourRampGenerator.h"
#include "ColourRGB565.h"

GenericColourRampGenerator::GenericColourRampGenerator(const ColourRGB565& tl_,
													   const ColourRGB565& tr_,
													   const ColourRGB565& bl_,
													   const ColourRGB565& br_,
													   unsigned int width_,
													   unsigned int height_,
													   unsigned int min_row_,
													   unsigned int min_col_)
													   :
													   ColourRampGenerator(width_, height_, min_row_, min_col_),
													   tl(tl_),
													   tr(tr_),
													   bl(bl_),
													   br(br_)
{}

bool GenericColourRampGenerator::get_row(unsigned int col_,
										 unsigned int row_,
										 unsigned int width_,
										 unsigned short *pixels)
{
	if(!valid_row(row_) || !valid_col(col_) || get_width() == 1 || get_height() == 1)
		return false;
	// do interpolation from tl to bl and tr to br
	const float row_frac = static_cast<float>(row_-get_min_row())/static_cast<float>(get_height()-1);
	const ColourRGB565 left_col = ColourRGB565::interpolate(tl, bl, row_frac);
	const ColourRGB565 right_col = ColourRGB565::interpolate(tr, br, row_frac);

	// now do interpolation between these two colours along the relevant pixels in the row.
	for(unsigned int i = 0; i < width_ && valid_col(col_+i); ++i)
	{
		const float col_frac = static_cast<float>(col_+i-get_min_col())/static_cast<float>(get_width()-1);
		pixels[i] = ColourRGB565::interpolate(left_col, right_col, col_frac).get_col();
	}
	return true;
}
