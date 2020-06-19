#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <type_traits>

template<typename T> concept Decimal_Number = std::is_floating_point<T>::value;




///While this is cool, it doesn't work for std::array, I don't think it works 
///for c style arrays either.
template< template < typename... Args> class Container, Decimal_Number... Types>
class ScalarField
{
  public:
    ScalarField(){};
  private:
    Container<Types...> field;
};




#endif
