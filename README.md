# ColourChart
An application to generate a colour ramp

Brief Description:
------------------

The enclosed application is designed to generate a colour ramp in RGB 565 format.

The main() method (in main.cpp) firstly checks for correctly formatted command line arguments, as specified 
in the provided specification. Each corner colour code, in RGB565 format, may be represented as
a hexadecimal or a decimal, and it is permitted that different arguments can be provided in 
different formats.

Once the validity of the command line arguments are checked, main() attempts to substitute 
any invalid corner colour codes provided with the other corner colour code on the same side 
of the screen, if available. If not then the program terminates due to insufficient information. 
As specified in the specification provided, bottom corner colours, if not provided, default to 
the (valid) top corner colours on their respective sides of the screen.

In scenarios where at this point we have four valid corner colour codes we construct four
ColourRGB565 objects - objects that encapsulate the encoded colour information of a pixel
in RGB565 format and make it available through accessors. The class also possesses a static 
method interpolate() which linearly interpolates between two specified ColourRGB565 objects
by a specified fraction.

At this point there a several possible scenarios regarding the relationship, if any, between the
four corner colours: (i) all identical, (ii) both top or both bottom two corner colours are identical, 
(iii) both left or both right two corner colours are identical, (iv) all other scenarios.

In order to generate the required colour ramp for each of these scenarios, a ColourRampGenerator
class has been created. This is an abstract base class to a hierarchy of derived classes, each devoted
to one of the four scenarios (i) to (iv): For (i) SingleColourRampGenerator - all colours in the ramp 
are identical, for (ii) IdenticalColsColourRampGenerator - all ramp columns are identical, (iii)
IdenticalRowsColorRampGenerator - all ramp rows are identical, (iv) GenericColourRampGenerator - the
generic case where 2D linear interpolation is performed to obtain the colour for each specified pixel
in the ramp. The static factory method ColourRampGenerator::create(), when supplied with, amongst others,
arguments specifying the four corner colour codes, will return a pointer to the subclass
appropriate for calculating the required colour ramp in the most efficient way.

ColourRampGenerator has a virtual method, get_row(), which is overriden by each of its subclasses,
which populates a supplied unsigned short[], pixels, with the RGB565 formatted colour codes
for each pixel along a specified row in the colour ramp, starting from a specified column (and
continuing up until the right hand side of the screen). 

A Display object, display, is instantiated and, if connects successfully to the device named in argv[1], is 
supplied with each row of pixel colour codes by making sequential calls to get_row() via the local 
ColourRampGenerator*, crg, for all rows specified by display.

Upon destruction of the Display object (i.e., when the program terminates) the contents of the
frame buffer, i.e., the colour ramp, is output to the screen in hexadecimal RGB565 format.

Special notes:
--------------
In Display.h, the #include directive for <cmemory> was changed to <memory> in order
to compile on my development platform.

Testing Strategy:
-----------------
A series of unit tests have been provided along with this application. They can be
enabled by setting CONDUCT_UNIT_TESTING to 1 in main.cpp.

The tests generate rows of pixels and populate a global frame buffer equal in size
to that defined in Display.cpp. The buffer is populated with the appropriate
output from get_row() from an appropriate ColourRampGenerator subclass.

The resulting buffer is compared with that expected for some common sense cases
using a local 2D array of equal size.

If all tests pass successfully then the following message is output:

				"All unit tests passed."
				
However, if one unit test should fail, then no more are attempted after that
and a test-specific message is output, e.g., "unit_test1 failed".

Possible Additions to testing strategy (not included):
------------------------------------------------------
-In addition to the tests provided here could be ones that utilise different
screen sizes.
-Regression (unit) tests, identical in structure to those provided, but for more complex, 
less obvious, cases could be added whilst development continues.
-Whilst difficult to test user input into main() through unit tests, one
could generate unit tests to check the conversion and validity functions
in Utilities.h and Utilities.cpp, which here were checked whilst debugging the
rest of the application.
