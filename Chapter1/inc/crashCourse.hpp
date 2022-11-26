/* Page 100(50):
 * WARNING Pointers are introduced here because you will encounter them,
 * specially in legacy code bases. In new code, however, such raw/naked
 * pointers are allowed only if there is no ownership involved.
 * Otherwise, you should use one of the smart pointers
 * NOTE Avoid using malloc() and free() from C. Instead, use new and delete,
 * or new[] and delete[].
 * Page 123(73):
 * WARNING Always keep in mind that auto strips away reference and const qualifiers
 * and thus creates a copy! If you do not want a copy, use auto& or const auto&.*/
#pragma once
#include <array>
#include <compare>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

enum class COMMAND {
  NOP,
  TWC,
  NODISCARD,
  NORETURN,
  DEPRECATED,
  OPTIONAL,
  STRUCT_BIND,
  PTR,
  TWO_STRINGS,
  NUMBERS,
};
template <typename T>
std::strong_ordering threeWayComparison(T one, T other);
template <typename T>
std::strong_ordering threeWayComparisonHO(T one, T other)  // Header Only
{
  return one <=> other;
}
[[nodiscard("It's very important")]] int func();

/*[[noreturn]]*/ void forceProgramTermination();  // No error!?

[[deprecated("Unsafe method, please use funcB")]] void funcA();
void funcB();

std::optional<int> getValue(bool isValid);

/* Structured bindings allow you to declare multiple variables that are initialized
 * with elements from, for example, an array, struct, or pair.*/
struct StructBindStruct {
  int A = 666;
  float b;
};
// std::array<int, 2> StructBindArray;
using StructBindArray = std::array<int, 2>;

using StructBindPair = std::pair<int, double>;

StructBindStruct getStructBindStruct();
StructBindArray getStructBindArray();
StructBindPair getStructBindPair();

struct ArrayOnHeap {
  using AnArray = std::array<int, 10>;
  ArrayOnHeap() { aNumber = new AnArray; }
  ~ArrayOnHeap() { delete aNumber; }
  AnArray* aNumber;
};
int takesValue(int i);
int takesValue(int* i);

/**The function doesn’t know how many numbers in the source array will be even or odd, so it
 * should dynamically allocate the memory for the destination arrays after examining the source array. It
 * should also return the sizes of the two new arrays.
 * @return  Altogether, there are four items to return: pointers to the two new arrays and the sizes of the two new
 * arrays.*/
void separateOddsAndEvens(const int arr[], size_t size, int** odds, size_t* numOdds, int** evens, size_t* numEvens);

void betterSeparateOddsAndEvens(const int arr[], const size_t& arrSize, size_t& numEvens, size_t& numOdds, int*& odds,
                                int*& evens);

void evenBetterSeparateOddsAndEvens(const std::vector<int>& arr, std::vector<int>& odds, std::vector<int>& evens);
using NumVector = std::vector<int>;
struct OddsAndEvens {
  NumVector odds;
  NumVector evens;
};
OddsAndEvens bestSeparateOddsAndEvens(const NumVector& arr);

/*Exercise 1-5:
 * Now that you know about const and references, and what they are used for,
 * modify the AirlineTicket class from earlier in this chapter to use references wherever pos-
 * sible and to be so-called const correct. */
class AirlineTicket {
 public:
  AirlineTicket();
  ~AirlineTicket();
  double calculatePriceInDollars();
  std::string getPassengerName() const;
  void setPassengerName(const std::string& name);
  int getNumberOfMiles() const;
  void setNumberOfMiles(const int miles);  // Nothing gained by referense
  bool hasEliteSuperRewardsStatus() const;
  void setHasEliteSuperRewardsStatus(const bool status);  // Nothing gained by referense
  std::optional<int> getFfrequentFlyerNumber() const;
  void setFfrequentFlyerNumber(const int frqFlyerNum) { m_frequentFlyer = frqFlyerNum; }

 private:
  std::string m_passengerName;
  int m_numberOfMiles;
  bool m_hasEliteSuperRewardsStatus;
  int m_frequentFlyer = 0;  // optional frequent-flyer number
};

/*Exercise 1-6:
 * Modify the AirlineTicket class from Exercise 1-5 to include an optional
 * frequent-flyer number. What is the best way to represent this optional data member? Add a
 * setter and a getter to set and retrieve the frequent-flyer number. Modify the main() function
 * to test your implementation. */

/* Inline namespace */
namespace top {
inline namespace middle {
inline namespace bottom {
using namespace std::literals::string_literals;
}
}  // namespace middle
}  // namespace top

/* Not inlined */
namespace Top {
namespace Bottom {
using namespace std::literals::string_literals;
}
}  // namespace Top
std::string_view extractExtension(std::string_view filename);

/* Exercise 2-1: Write a program that asks the user for two strings and then prints them out
 * in alphabetical order, using the three-way comparison operator.*/
void twoStrings();

/*Exercise 2-2: Write a program that asks the user for a source string (= haystack), a string
 * to find (= needle) in the source string, and a replacement string. Write a function with
 * three parameters—the haystack, needle, and replacement string—that returns a copy of the haystack
 * with all needles replaced with the replacement string. Use only std::string, no string_view. */
std::string haystack(std::string& haystack, const std::string& needle, const std::string& replacement);

/* Exercise 2-3:
 * Modify the program from Exercise 2-2 and use std::string_view on as many places as possible */
std::string haystack(std::string_view haystack, const std::string_view needle, const std::string_view replacement);

/* Exercise 2-4:
 * Write a program that asks the user to enter an unknown number of floatingpoint numbers and stores all
 * numbers in a vector. Each number should be typed followed by Enter.
 * Stop asking for more numbers when the user inputs the number 0.
 * Format all numbers in a table with a couple of columns where each column formats a number
 * in a different way. Each row in the table corresponds to one of the inputted numbers.*/
template <typename T>
void readNumbers(std::vector<T>& numbers);
template <typename T>
void presentNumbers(const std::vector<T>& numbers);