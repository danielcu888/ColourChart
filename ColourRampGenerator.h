#ifndef COLOURRAMPGENERATOR_H_
#define COLOURRAMPGENERATOR_H_

#include "ColourRGB565.h"

class ColourRampGenerator
{
public:
	// static factory method
	static ColourRampGenerator* create(const ColourRGB565& tl_,	// top-left colour
									   const ColourRGB565& tr_,	// top-right colour
									   const ColourRGB565& bl_,	// bottom-left colour
									   const ColourRGB565& br_,	// bottom-right colour
									   unsigned int width_,		// number of pixels between left and right colours
									   unsigned int height_,	// number of pixels between top and bottom pixels
									   unsigned int min_row_ = 0, // minimum row from which we wish to interpolate
									   unsigned int min_col_ = 0); // minimum column from which we wish to interpolate
	virtual ~ColourRampGenerator() {}
	virtual bool get_row(unsigned int col_,	// column of the first desired pixel in the specified row
						 unsigned int row_,	// specified row
						 unsigned int width_,	// number of pixels in row that you desire
						 unsigned short *pixels	// client-supplied return array
						 ) = 0; //

protected:
	ColourRampGenerator(unsigned int width_, unsigned int height_, unsigned int min_row_, unsigned int min_col_);
	unsigned int get_width() const {return width;}
	unsigned int get_height() const {return height;}
	unsigned int get_min_row() const {return min_row;}
	unsigned int get_min_col() const {return min_col;}
	bool valid_col(unsigned int col_) const {return col_ >= min_col && col_ < min_col + width;}
	bool valid_row(unsigned int row_) const {return row_ >= min_row && row_ < min_row + height;}

private:
	const unsigned int width, height;
	const unsigned int min_row, min_col;
};

#endif
