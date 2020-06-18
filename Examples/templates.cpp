#include <deque>
#include <array>
#include <iostream>
#include <string>
#include <vector>

template < template < class ... > class Container, class ... Args >
void any_container(Container<double, Args...>)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main()
{
  std::vector<double> vd;
  any_container(vd);

  std::deque<double> dd;
  any_container(dd);

  std::vector<std::string> vs;
// doesn't compile
//  any_container(vs);
}
