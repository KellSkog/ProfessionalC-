// export module employee;
// export struct Employee {
//   char firstInitial;
//   char lastInitial;
//   int employeeNumber;
//   int salary;
// };
#include "crashCourse.hpp"

template <>
std::strong_ordering threeWayComparison(int one, int other) {
  return one <=> other;  // C++20!
}