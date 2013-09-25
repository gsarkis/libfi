#include "fi/Fixed.hpp"
#include "fi/overflow/Wrap.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

  Fi::Fixed<8, 4, Fi::SIGNED> a("3.14");
  Fi::Fixed<8, 4, Fi::SIGNED> b("1.14");

  std::cout << a*b << std::endl;

  return 0;

}
