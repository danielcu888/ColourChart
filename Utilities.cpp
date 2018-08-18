#include "Utilities.h"
#include <string>
#include <cmath>

namespace utilities
{

// returns true if specified string is
// formatted as an unsigned short in
// decimal format, false otherwise.
bool valid_ushort(const std::string& s)
{
	if(s.length() > 5 || s.empty())
		return false;

	unsigned int ret = 0; // int will suffice since max int has > 5 digits
	for(unsigned int i = 0; i < s.length(); ++i)
		{
		ret *= 10;
		const char c = s[i];
		if(!(c >= '0' && c <= '9')) // must be a digit
			return false;
		else
			ret += (c - '0');
		}
	return ret <= 0xffff; // check if unsigned value is in range of ushort
}

// returns an unsigned short from the specified
// string. (string should be tested with valid_ushort()
// before passing to this function.)
unsigned short str_to_ushort(const std::string& s)
{
	unsigned short ret = 0;
	for(unsigned int i = 0; i < s.length(); ++i)
		{
		ret *= 10;
		ret += s[i] - '0';
		}
	return ret;
}

// returns true if specified string is
// formatted as a 16bit hexadecimal
// with leading "0x", false otherwise.
bool valid_16bit_hex(const std::string& s)
{
	if(s.length() > 6 || s.length() < 3)
		return false;
	if(s[0] != '0' || s[1] != 'x')
		return false;

	for(unsigned int i = 0; i < s.length()-2; ++i)
	{
		const char c = s[i+2];
		if(!((c >= '0' && c <= '9') ||
		   (c >= 'a' && c <= 'f') ||
		   (c >= 'A' && c <= 'F')))
			return false;
	}
	return true;
}

// returns an unsigned short from the specified
// string. (string should be tested with valid_16bit_hex()
// before passing to this function.)
unsigned short hex_to_ushort(const std::string& s)
{
	unsigned short ret = 0;
	for(unsigned int i = 0; i < s.length()-2; ++i)
	{
		ret <<= 4;
		const char c = s[i+2];
		unsigned short tmp = 0;
		if(c >= '0' && c <= '9')
			tmp = c - '0';
		else
			tmp = tolower(c) - 'a' + 10; // hence if c = A or a tmp = 10
		ret += tmp;
	}
	return ret;
}

//returns the nearest short to the
//specified float.
short round(float f)
{
	return static_cast<short>(floor(f+0.5));
}


} // ! namespace utilities
