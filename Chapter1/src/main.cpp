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
      case NOP:
        break;
      case TWC: {
        std::strong_ordering result = std::strong_ordering::equal;
        if (argc == 4)
          result = threeWayComparison(atoi(argv[2]), atoi(argv[3]));
        else
          result = threeWayComparison(1, 1);

        std::cout << "Comparison result: " << get_ordering(result) << "\n";
        break;
      }
    }
  } else
    std::cout << "I'm alive, alive I say!\n";
}