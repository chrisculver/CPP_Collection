#ifndef INPUT_H
#define INPUT_H

#include "string_utilities.h"
#include "file_utilities.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <charconv> 
#include <iostream>

template <class T> concept Integral = std::is_integral<T>::value;

class Input
{
  public:
    Input(){};
    
    void load(std::string filename)
    {
      if( !file_exists(filename) )
      {
        throw 'f';
      }   
      std::ifstream input(filename);
      std::string line;
      while( getline(input, line) )
      {
        auto data = split(line, ' ');
        name_value[ data[0] ] = data[1];
      } 
    }


    template<typename T> 
    void load_into( T &value, std::string name) requires Integral<T>
    {
      if( name_value.count(name) == 0 )
        throw name;
      std::string_view tmp{ name_value[name] };
      std::from_chars(tmp.data(), tmp.data()+tmp.size(), value);
      name_value.erase(name);
    }

    void load_into( std::string &value, std::string name)
    {
      if( name_value.count(name) == 0 )
        throw name;
      value = name_value[name];
      name_value.erase(name);
    }

  void close()
  {
    if(name_value.size() > 0)
    {
      std::cerr << "WARNING: Extra input found.  Will not be used in program." << std::endl;
      for(auto &e : name_value)
      {
        std::cerr << "   " << e.first << " " << e.second << std::endl;
      }
    }
  }

  private:
    std::map<std::string, std::string> name_value;
};

#endif
