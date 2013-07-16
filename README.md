# LibFi - A fixed-point arithmetic library.

## What is LibFi?

LibFi is a binary fixed-point arithmetic library for C++, focusing on flexibility and correctness. It is intended to be used for modeling hardware systems. LibFi is template-based and is a header-only library.

Unlike most other C++ fixed-point libraries, the word length in Fi does not have to be a power of two, and the overflow behavior and rounding mode are customizable.

This is a header-only library so you include `./fi/Fixed.hpp`, and any applicable overflow handlers and rounding modes from `./fi/overflow` and `./fi/rounding`.

Here is an example of multiplying 8-bit signed fixed-point numbers with 4 fractional bits and wrap-around overflow handling:
```cpp
#include "fi/Fixed.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

  Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> a("3.14");
  Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> b("13.14");

  std::cout << a*b << std::endl;

  return 0;

}
```

## Documentation
LibFi is documented using Doxygen. To build the documentation, you need [Doxygen](http://www.doxygen.org). In the library's root directory, run `doxygen`. The documentation will be available in `doc/html/index.html`.

## Changelog
* 2013-07-02 v1.0: First public release of LibFi.
