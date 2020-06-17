#ifndef FILE_UTILITIES_H
#define FILE_UTILITIES_H

#include <string>
#include <fstream>

bool file_exists(std::string filename)
{
  std::ifstream file(filename.c_str());
  return file.good();
}

#endif
