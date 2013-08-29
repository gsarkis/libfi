# LibFi - A fixed-point arithmetic library.

## What is LibFi?

LibFi is a binary fixed-point arithmetic library for C++, focusing on flexibility and correctness. It is intended to be used for modeling hardware systems. LibFi is template-based and is a header-only library.

Unlike most other C++ fixed-point libraries, the word length in Fi does not have to be a power of two, and the overflow behavior and rounding mode are customizable.

This is a header-only library so you include `./fi/Fixed.hpp`, and any applicable overflow handlers and rounding modes from `./fi/overflow` and `./fi/rounding`.

Here is an example of multiplying 8-bit signed fixed-point numbers with 4 fractional bits and wrap-around overflow handling:
```cpp
#include "fi/Fixed.hpp"
#include "fi/overflow/Wrap.hpp"

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

### Quick Reference
The `Fi::Fixed<TOTAL_WIDTH, FRACTION_WIDTH, SIGNEDNESS, OVERFLOW, ROUNDING>` datatype accepts five parameters: 

| Parameter | Description | Required |
|:------------|:------------|:------------|
| `TOTAL_WIDTH` | Total number of bits in binary representation, including the sign for signed types. | Yes |
| `FRACTION_WIDTH`  | Number of fractional bits. | Yes |
| `SIGNEDNESS`  | `Fi::SIGNED` for signed values; `Fi::UNSIGNED` for unsigned values. | Yes |
| `OVERFLOW`    | Behavior when a number overflows the range representable using the selected quantization parameters. See below for valid options. | No (Default: `Fi::Throw`) |
| `ROUNDING`    | Behavior when a number is not representable using the selected quantization parameters. See below for valid options. | No (Default: `Fi::Fix`) |

#### Overflow

| Mode | Description |
|:------------|:------------|
| `Fi::Classic` | Round to nearest representable value. Ties are rounded away from zero. |
| `Fi::Ceil`    | Round towards positive infinity. |
| `Fi::Floor`   | Round towards negative infinity. |
| `Fi::Fix`     | Round towards zero. |

#### Rounding

| Mode | Description |
|:------------|:------------|
| `Fi::Saturate`  | Saturate value to maximum or minimum value allowed by selected quantization parameters. |
| `Fi::Wrap`      | Wrap the value around when overflow occurs. |
| `Fi::Throw`     | When overflow occurs, throw a `Fi::PositiveOverflow` or a `Fi::NegativeOverflow` exception, depending on the direction of the overflow. |
| `Fi::Undefined` | The behavior of overflow is undefined. Use when execution speed is more important than results. |
 
## Tests
Nightly test build results are available [on the following page](http://my.cdash.org/index.php?project=LibFi).

### Supported Platforms
Tests are run on the following platforms:
* 64-bit Linux using GCC.
* 64-bit Linux using Clang.

The master branch always contains code which passes all the tests on the supported platforms.

## External References
* [MATLAB Fixed-Point Designer Toolbox](http://www.mathworks.com/help/fixedpoint/ref/_f46184.html)
* [C++ Binary Fixed-Point Arithmetic Library Proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3352.html)

## Changelog
* 2013-07-02 v1.0: First public release of LibFi.
