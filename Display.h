#ifndef DISPLAY_HXX_
#define DISPLAY_HXX_

class Display
{
public:
	Display();
	~Display();
	bool connect(const char *display_name);
	void get_size(int &width, int &height);
	void draw_raster(int x, int y,
              const unsigned short *pixels, int width);
};

#endif
