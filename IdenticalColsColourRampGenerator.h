#ifndef IDENTICALCOLSCOLOURRAMPGENERATOR_H_
#define IDENTICALCOLSCOLOURRAMPGENERATOR_H_

#include "ColourRGB565.h"
#include "ColourRampGenerator.h"

class IdenticalColsColourRampGenerator : public ColourRampGenerator
{
public:
	IdenticalColsColourRampGenerator(const ColourRGB565& tl_, const ColourRGB565& bl_, unsigned int width_, unsigned int height_, unsigned int min_row_,
			unsigned int min_col_);
	bool get_row(unsigned int col_,
					 unsigned int row_,
					 unsigned int width_,
					 unsigned short *pixels);

private:
	const ColourRGB565& top_col, bottom_col;
};

#endif
