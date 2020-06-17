#include "timer.h"

#include <iostream>

using namespace std;

int main()
{
  Timer t1, t2;

  std::cout << "Time elapsed: " << t1.elapsed() << " s\n";

  for(int i=0; i<100000; ++i)
    double x=0;

  std::cout << "Time elapsed: " << t2.elapsed() << " s\n";
}
