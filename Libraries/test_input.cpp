#include "input.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  if(argc==1)
  {
    cerr << "ERROR: Not enough arguments! Second argument should be a filename" << endl;
    cerr << "Exiting..." << endl;
    return 9;
  }

  Input data;

  try
  {
    data.load( string(argv[1]) );
  }
  catch(char &ex)
  {
    cerr << "ERROR: Couldn't find input file \"" << string(argv[1]) << "\"" << endl;
    cerr << "Exiting..." << endl;
    return 1;
  }

  int nx, nt;
  std::string output_filename;
  try
  { 
    data.load_into(nx, string("nx"));
    data.load_into(nt, string("nt"));
    data.load_into(output_filename, string("output_filename"));
  }
  catch(std::string &ex)
  {
    cerr << "ERROR: Missing mandatory input for " << ex << endl;
    cerr << "Exiting..." << endl;
    return 1;
  }

  cout << "Loaded nx = " << nx << endl;
  cout << "Loaded nt = " << nt << endl;
  cout << "Loaded output_filename = " << output_filename << endl;

  data.close();

}
