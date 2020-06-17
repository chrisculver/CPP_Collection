#ifndef STRING_UTILITIES_H
#define STRING_UTILITIES_H

#include <sstream>
#include <vector>

template<typename Out> void split(const std::string &s, char delim, Out result)
{
  std::stringstream ss(s);
  std::string item;
  while(getline(ss, item, delim))
  {
    *(result++) = item;
  }
}


std::vector<std::string> split(const std::string &s, char delim)
{
  std::vector<std::string> res;
  split(s, delim, back_inserter(res));
  return res;
}


#endif
