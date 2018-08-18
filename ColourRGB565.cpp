#include "ColourRGB565.h"
#include <cmath>
#include <string>
#include "Utilities.h"
#include <iostream>

using std::string; using std::cerr;
using std::endl;

bool operator==(const ColourRGB565& A, const ColourRGB565& B)
{
	return A.get_col() == B.get_col();
}

//1D linear interpolation method
const ColourRGB565 ColourRGB565::interpolate(const ColourRGB565& A, const ColourRGB565& B, float frac)
{
	if(frac < 0.0F)
	{
		cerr << "Warning: ColourRGB565::interpolate: frac <= 0. - returning A" << endl;
		return A;
	}

	if (frac > 1.0F)
	{
		cerr << "Warning: ColourRGB565::interpolate: frac >= 1. - returning B" << endl;
		return B;
	}

	if(A == B)
	{
		return A;
	}

	// linearly interpolate individual components of A and B
	const float redf  = (B.red_comp() - A.red_comp())*frac + A.red_comp();
	const float greenf = (B.green_comp() - A.green_comp())*frac + A.green_comp();
	const float bluef = (B.blue_comp() - A.blue_comp())*frac + A.blue_comp();

	//round each fractional colour component to nearest integer
	const unsigned short red = round(redf);
	const unsigned short green = round(greenf);
	const unsigned short blue = round(bluef);

	return ColourRGB565(red, green, blue);
}

