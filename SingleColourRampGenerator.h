#ifndef SINGLECOLOURRAMPGENERATOR_H_
#define SINGLECOLOURRAMPGENERATOR_H_

#include "ColourRGB565.h"
#include "ColourRampGenerator.h"

class SingleColourRampGenerator : public ColourRampGenerator
{
public:
	SingleColourRampGenerator(const ColourRGB565& tl_,
							  unsigned int width_,
							  unsigned int height_,
							  unsigned int min_row_,
							  unsigned int min_col_);

	bool get_row(unsigned int start_col_,
					 unsigned int row_,
					 unsigned int width_,
					 unsigned short *pixels);

private:
	const ColourRGB565& c;
};

#endif
