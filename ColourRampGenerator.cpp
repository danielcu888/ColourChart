#include "ColourRampGenerator.h"
#include "SingleColourRampGenerator.h"
#include "IdenticalRowsColourRampGenerator.h"
#include "IdenticalColsColourRampGenerator.h"
#include "GenericColourRampGenerator.h"

ColourRampGenerator::ColourRampGenerator(unsigned int width_,
										 unsigned int height_,
										 unsigned int min_row_,
										 unsigned int min_col_)
										:
										 width(width_),
										 height(height_),
										 min_row(min_row_),
										 min_col(min_col_)
{}

ColourRampGenerator* ColourRampGenerator::create(
								   const ColourRGB565& tl_,
								   const ColourRGB565& tr_,
								   const ColourRGB565& bl_,
								   const ColourRGB565& br_,
								   unsigned int width_,
								   unsigned int height_,
								   unsigned int min_row_,
								   unsigned int min_col_)
{
	if(tl_ == bl_ && tr_ == br_)
	{
		// Each row will be identical
		if(tl_ == tr_)
			{
			 // each pixel has same colour
			return new SingleColourRampGenerator(tl_, width_, height_, min_row_, min_col_);
			}

		// shouldn't have width=1 here other wise we have a single colour ramp, caught above
		return new IdenticalRowsColourRampGenerator(tl_, tr_, width_, height_, min_row_, min_col_);
	}

	if(tl_ == tr_ && bl_ == br_)
		{
		// Each column will be identical

		// shouldn't have height == 1 here otherwise we have a single colour ramp
		return new IdenticalColsColourRampGenerator(tl_, bl_, width_, height_, min_row_, min_col_);
		}

	// Generic case - 2D interpolation
	return new GenericColourRampGenerator(tl_, tr_, bl_, br_, width_, height_, min_row_, min_col_);
}
