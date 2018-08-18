#ifndef COLOURRGB565_HXX_
#define COLOURRGB565_HXX_

#include <string>

class ColourRGB565
{
	enum COLOURS {PURE_RED = 0xf800, PURE_GREEN = 0x07e0, PURE_BLUE = 0x001f, BLACK = 0x0000, WHITE = 0xffff}; // checked

public:
	// checked
	ColourRGB565(unsigned short col_ = 0)
		: col(col_)
	{}

	// Constructor taking unsigned short colour codes for each component
	// where first 5 or 6 bits are relevant
	ColourRGB565(unsigned short R_, unsigned short G_, unsigned short B_)
	{
		// check ranges and set to extremes
		// dont need to worry about R_, just shift it 11 times (it then cannot exceed PURE_RED)
		R_ <<= 11;
		if((G_ <<=5) > PURE_GREEN) G_ = PURE_GREEN;
		if(B_ > PURE_BLUE) B_ = PURE_BLUE;

		col = 0;
		col |= R_;
		col |= G_;
		col |= B_;
	}

	//accessors to colour components
	unsigned short red_comp() const {return (PURE_RED & col) >> 11;}
	unsigned short green_comp() const {return (PURE_GREEN & col) >> 5;}
	unsigned short blue_comp() const {return PURE_BLUE & col;}
	unsigned short get_col() const {return col;}

	//1D linear interpolation method
	const ColourRGB565 static interpolate(const ColourRGB565& A, const ColourRGB565& B, float frac);

private:
	unsigned short col;
};

bool operator==(const ColourRGB565& A, const ColourRGB565& B);

#endif
