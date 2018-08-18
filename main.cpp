#define CONDUCT_UNIT_TESTING 1 //Set to 1 for unit testing, otherwise 0 to run normal application.
#include <cstdlib>
#include <iostream>
#include <string>
#include "Utilities.h"
#include "Display.h"
#include "ColourRGB565.h"
#include "ColourRampGenerator.h"
#include "unit_tests.h"

using std::cerr; using std::endl;
using std::string; using std::cout;

int main(int argc, char *argv[])
{
#if CONDUCT_UNIT_TESTING
	// conduct unit testing
	call_unit_tests();
#else
	// check for correct number of arguments (min 2 colours, max of 4 colours)
	if(argc < 4 || argc > 6)
	{
		cerr << "Usage: <program name> <display name> <top left colour (hex or dec)> <top right colour (hex or dec)> "
				"[<bottom left colour (hex or dec)>] [<bottom right colour (hex or dec)>]" << endl;
		return EXIT_FAILURE;
	}

	const string display_name = argv[1]; // get display device name

	// get [2,4] 16-bit RGB colour codes from CL arguments:
	bool *valid = new bool[4]; // check if valid input
	for(unsigned int i = 0; i < 4; ++i) // set validity to false by default
		valid[i] = false;
	unsigned short *cols = new unsigned short[4]; // storage for colour codes (we read up to 4)

	//get colours passed in via command line
	for(unsigned int i = 0; i < static_cast<unsigned int>(argc-2); ++i)
	{
		const string tmp = argv[i+2]; // next argument
		if(utilities::valid_16bit_hex(tmp)) // check if its a valid hex
		{
			valid[i] = true;
			cols[i] = utilities::hex_to_ushort(tmp);
		}
		else if(utilities::valid_ushort(tmp))
		{
			valid[i] = true;
			cols[i] = utilities::str_to_ushort(tmp);
		}
		else
		{
			cerr << "Warning: invalid colour!" << endl;
			// skip argument, validity still false
		}
	}

	// Get 4 colours' codes, utilising valid inputs, if possible. If not, exit.
	if(valid[0] && !valid[2])
		cols[2] = cols[0];
	else if(!valid[0] && valid[2])
	{
		cerr << "Warning: Invalid top-left colour - replacing with bottom-left colour." << endl;
		cols[0] = cols[2];
	}
	else if(!valid[0] && !valid[2])
	{
		cout << "ERROR: Insufficient colours on left hand side - exiting." << endl;
		return EXIT_FAILURE;
	}
	if(valid[1] && !valid[3])
		cols[3] = cols[1];
	else if(!valid[1] && valid[3])
		{
		cout << "Warning: Invalid top-right colour - replacing with bottom-right colour." << endl;
		cols[1] = cols[3];
		}
	else if(!valid[1] && !valid[3])
	{
		cerr << "Insufficient colours on right hand side - exiting." << endl;
		return EXIT_FAILURE;
	}

	delete [] valid; valid = NULL;

	// Now we should have 4 unsigned shorts corresponding to 4 colours.

	// set up display object and connect to device
	Display display;
	if(!display.connect(display_name.c_str()))
	{
		cerr << "ERROR: Cannot connect to display device - exiting!" << endl;
		return EXIT_FAILURE;
	}

	// get screen dimensions
	int screen_width, screen_height;
	display.get_size(screen_width, screen_height);
	if (screen_width < 1 || screen_height < 1)
	{
		cerr << "ERROR: Area of screen is zero - exiting!" << endl;
		return EXIT_FAILURE;
	}

	// construct the 4 corner colours
	const ColourRGB565 tl(cols[0]), tr(cols[1]), bl(cols[2]), br(cols[3]);

	const unsigned int min_row = 0, min_col = 0; // we are to fill entire screen

	// get abstract base class reference to generator of rows of pixels via static factory method
	ColourRampGenerator* crg = ColourRampGenerator::create(tl, tr, bl, br, screen_width, screen_height, min_row, min_col);

	// populate screen with interpolate rows of pixels
	unsigned short *pixels = new unsigned short[screen_width];
	for(unsigned int row = 0; row < static_cast<unsigned int>(screen_height); ++row)
	{
		crg->get_row(min_col, row, screen_width, pixels);
		display.draw_raster(min_col, row, pixels, screen_width);
	}

	// free resources
	delete [] pixels; pixels = NULL;
	delete [] cols; cols = NULL;
	delete crg; crg = NULL;
#endif
	return EXIT_SUCCESS;
}
