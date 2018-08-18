#ifndef GENERICCOLOURRAMPGENERATOR_H_
#define GENERICCOLOURRAMPGENERATOR_H_

#include "ColourRGB565.h"
#include "ColourRampGenerator.h"

class GenericColourRampGenerator : public ColourRampGenerator
{
public:
	GenericColourRampGenerator(const ColourRGB565& tl_,
							   const ColourRGB565& tr_,
							   const ColourRGB565& bl_,
							   const ColourRGB565& br_,
							   unsigned int width_,
							   unsigned int height_,
							   unsigned int min_row_,
							   unsigned int min_col_);

	bool get_row(unsigned int col_,
					 unsigned int row_,
					 unsigned int width_,
					 unsigned short *pixels);

private:
	const ColourRGB565& tl, tr, bl, br;
};

#endif
