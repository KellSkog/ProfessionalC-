// export module employee;
// export struct Employee {
//   char firstInitial;
//   char lastInitial;
//   int employeeNumber;
//   int salary;
// };
#include "crashCourse.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>  // pair

// Using uniform initialization
std::array twoInts = {1, 2};                      // std::array<int, 2UL> twoInts
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

std::optional<int> getValue(bool isValid) {
  if (isValid)
    return 42;
  else
    return std::nullopt;
}

StructBindStruct getStructBindStruct() { return StructBindStruct{666, 1.5F}; }
StructBindArray getStructBindArray() { return StructBindArray{3, 14}; }
StructBindPair getStructBindPair() { return StructBindPair{3, 0.14}; }

int takesValue([[maybe_unused]] int i) { return 666; }
int takesValue([[maybe_unused]] int* i) { return -666; }

#define IgnoreUnusedButSetParameter \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wunused-but-set-parameter\"")
#define RestoreUnusedButSetParameter _Pragma("GCC diagnostic pop")

IgnoreUnusedButSetParameter;
void separateOddsAndEvens(const int arr[], size_t size, int** odds, size_t* numOdds, int** evens, size_t* numEvens) {
  // Count the number of odds and evens.
  *numOdds = *numEvens = 0;
  for (size_t i = 0; i < size; ++i) {
    if (arr[i] % 2 == 0) {
      ++(*numEvens);
    } else {
      ++(*numOdds);
    }
  }

  *evens = new int[*numEvens];
  *odds = new int[*numOdds];
  int evenIndex = 0;
  int oddIndex = 0;
  for (size_t i = 0; i < size; ++i) {
    if (arr[i] % 2 == 0) {
      (*evens)[evenIndex++] = arr[i];
      // Not the same as *evens[evenIndex++] = arr[i];
    } else {
      (*odds)[oddIndex++] = arr[i];
    }
  }
}
RestoreUnusedButSetParameter;

void betterSeparateOddsAndEvens(const int arr[], const size_t& arrSize, size_t& numEvens, size_t& numOdds, int*& odds,
                                int*& evens)
// size_t* numEvens) {}
{
  numOdds = numEvens = 0;
  for (size_t i = 0; i < arrSize; ++i) {
    if (arr[i] % 2 == 0) {
      ++(numEvens);
    } else {
      ++(numOdds);
    }
  }
  odds = new int[numOdds];
  evens = new int[numEvens];
  int evenIndex = 0;
  int oddIndex = 0;
  for (size_t i = 0; i < arrSize; ++i) {
    if (arr[i] % 2 == 0) {
      evens[evenIndex++] = arr[i];
      // Not the same as *evens[evenIndex++] = arr[i];
    } else {
      odds[oddIndex++] = arr[i];
    }
  }
}

void evenBetterSeparateOddsAndEvens(const std::vector<int>& arr, std::vector<int>& odds, std::vector<int>& evens) {
  for (auto i : arr) {
    if (i % 2 == 0) {
      evens.push_back(i);
    } else {
      odds.push_back(i);
    }
  }
}

/* Statements of the form return object; trigger return value optimization (RVO)
 * if object is a local variable, a parameter to the function, or a temporary value.
 * Furthermore, if object is a local variable, named
 * return value optimization (NRVO) can kick in. */
OddsAndEvens bestSeparateOddsAndEvens(const NumVector& arr) {
  OddsAndEvens result{};
  for (auto i : arr) {
    if (i % 2 == 0) {
      result.evens.push_back(i);
    } else {
      result.odds.push_back(i);
    }
  }
  // return result; // Which form is best? Same?
  return OddsAndEvens{.odds = result.odds, .evens = result.evens};
}