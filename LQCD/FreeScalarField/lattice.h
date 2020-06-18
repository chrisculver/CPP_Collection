#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <type_traits>

template<typename T> concept Decimal_Number = std::is_floating_point<T>::value;





template< template < class ... > class Container, class ... Args>
class ScalarField
{
  public:
    ScalarField(){};
  private:
    Container<Args...> field;
};


template< Decimal_Number P >
class ScalarFieldV
{
  public:
    ScalarFieldV(){};
  private:
    std::vector<P> field;
};


#endif
