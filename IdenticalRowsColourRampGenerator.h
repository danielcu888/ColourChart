#ifndef IDENTICALROWSCOLOURRAMPGENERATOR_H_
#define IDENTICALROWSCOLOURRAMPGENERATOR_H_

#include "ColourRGB565.h"
#include "ColourRampGenerator.h"

class IdenticalRowsColourRampGenerator : public ColourRampGenerator
{
public:
	IdenticalRowsColourRampGenerator(const ColourRGB565& tl_,
									 const ColourRGB565& tr_,
									 unsigned int width_,
									 unsigned int height_,
									 unsigned int min_row_,
									 unsigned int min_col_);

	bool get_row(unsigned int col_,
				 unsigned int row_,
				 unsigned int width_,
				 unsigned short *pixels);

private:
	const ColourRGB565& left_col, right_col;
};

#endif
