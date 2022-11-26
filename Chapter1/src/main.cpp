/* Regardin modules: https://blog.feabhas.com/2021/08/c20-modules-with-gcc11/
 * A complete module can be defined in a single source file.
 * I will use .cpp for regular C++ source files and .cxx for module files.
 * This is nothing more than a personal preference.
 */
#include <iostream>
#include <string>

#include "crashCourse.hpp"

std::string get_ordering(std::strong_ordering &result) {
  const std::string Outcome[3] = {"Equal", "Less than", "Greater than"};
  if (result == std::strong_ordering::equal)
    return Outcome[0];
  else if (result == std::strong_ordering::less)
    return Outcome[1];
  else if (result == std::strong_ordering::greater)
    return Outcome[2];
  return "";
}

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    switch (COMMAND cmd = static_cast<COMMAND>(atoi(argv[1])); cmd) {
      using enum COMMAND;
      [[unlikely]] case NOP : break;
      [[likely]] case TWC : {
        std::strong_ordering result = std::strong_ordering::equal;
        if (argc == 4)
          result = threeWayComparison(atoi(argv[2]), atoi(argv[3]));
        else
          result = threeWayComparison(1, 1);

        std::cout << "Comparison result: " << get_ordering(result) << "\n";
      }
      break;
      case NODISCARD: {
        /* error: ignoring return value of ‘int func()’, declared with attribute
         * ‘nodiscard’: ‘I'm very important’ [-Werror=unused-result]*/
        // func();
        [[maybe_unused]] auto mol = func();
        std::cout << "It's very important:\n";
      } break;
      case NORETURN:
        forceProgramTermination();
        break;
      case DEPRECATED:
#if 0 
        funcA();  // error: ‘void funcA()’ is deprecated: Unsafe method, please use xyz
               // [-Werror=deprecated-declarations]
#endif
        funcB();
        break;
      case OPTIONAL:
        std::cout << getValue(false).value_or(-42) << "\n";
        break;
      case STRUCT_BIND: {
        auto [a, b] = getStructBindArray();  // int &&a, int &&b
        a *= 2;
        b += 8.5F;
        auto [c, d] = getStructBindArray();  // Unchanged
        std::cout << " a is now: " << c << " b is now: " << d << "\n";
        /* It is also possible to create a set of references-to-non-const or
         * references-to-const using the struc-tured bindings syntax,
         by using auto& or const auto& instead of auto. */
      } break;
      case PTR: {
#if 0
        int a{111};
        std::cout << &a << "\n";
        int *b[]{&a};
        int **c = b;
        std::cout << &b << ", " << *b << "\n";
        std::cout << &c << ", " << c << ", Sz: " << *c << "\n";
#endif
        /* Page 124(74):*/
        // int a{42, 42}; error: scalar object ‘a’ requires one element in initializer
        // int a = {42, 42}; error: scalar object ‘a’ requires one element in initializer
        int a = {42};
        int **aa = new int *[4];
        *aa = &a;
        std::cout << &aa << ", " << aa << ", " << *aa << ", " << **aa << "\n";
        int **bb = aa;
        std::cout << &bb << ", " << bb << ", " << *bb << ", " << **bb << "\n";
        delete[] aa;
      } break;
      case TWO_STRINGS:
        twoStrings();
        break;
      case NUMBERS:
        std::vector<double> numbers;
        readNumbers(numbers);
        presentNumbers(numbers);
        break;
    }
  } else
    std::cout << __func__ << " am alive, alive " << __func__ << " say !\n ";

  return 0;
}