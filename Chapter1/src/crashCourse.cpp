// export module employee;
// export struct Employee {
//   char firstInitial;
//   char lastInitial;
//   int employeeNumber;
//   int salary;
// };
#include "crashCourse.hpp"

#include <array>
#include <cstdlib>
#include <string>
#include <utility>  // pair
#include <vector>

std::array twoInts{1, 2};                         // std::array<int, 2UL> twoInts
std::vector threeInts{3, 14, 15};                 // std::vector<int, std::allocator<int>> twoInts
std::pair twoThings{3.14F, "Pi"};                 // td::pair<float, const char *> twoThings
std::pair otherThings{3.14F, std::string{"Pi"}};  // std::pair<float, std::string> twoThings

template <>
std::strong_ordering threeWayComparison(int one, int other) {
  return one <=> other;  // C++20!
}
[[nodiscard("I'm very important")]] int func() { return 42; }

void forceProgramTermination() {
  std::exit(1);  // Defined in <cstdlib>
}

void funcA() {}
void funcB() {}