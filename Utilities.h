#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

namespace utilities
{

  bool valid_16bit_hex(const std::string& s);
  unsigned short hex_to_ushort(const std::string& s);
  short round(float f);
  bool valid_ushort(const std::string& s);
  unsigned short str_to_ushort(const std::string& s);

} // ! namespace utilities

#endif
