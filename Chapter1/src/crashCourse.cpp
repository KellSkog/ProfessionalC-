// export module employee;
// export struct Employee {
//   char firstInitial;
//   char lastInitial;
//   int employeeNumber;
//   int salary;
// };
#include "crashCourse.hpp"

#include <cstdlib>
// #include <format> // No format in GCC 12.2
#include <iomanip>  // https://en.cppreference.com/w/cpp/io/manip/setw
#include <ios>      // https://en.cppreference.com/w/cpp/io/manip
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

AirlineTicket::AirlineTicket() {}
AirlineTicket::~AirlineTicket() {}
double AirlineTicket::calculatePriceInDollars() { return 0.0; }
std::string AirlineTicket::getPassengerName() const { return m_passengerName; }
void AirlineTicket::setPassengerName(const std::string& name) { m_passengerName = name; }
int AirlineTicket::getNumberOfMiles() const { return m_numberOfMiles; }
void AirlineTicket::setNumberOfMiles(const int miles) { m_numberOfMiles = miles; }
bool AirlineTicket::hasEliteSuperRewardsStatus() const { return m_hasEliteSuperRewardsStatus; }
void AirlineTicket::setHasEliteSuperRewardsStatus(const bool status) { m_hasEliteSuperRewardsStatus = status; }
std::optional<int> AirlineTicket::getFfrequentFlyerNumber() const {
  if (m_frequentFlyer) {
    return m_frequentFlyer;
  } else {
    return std::nullopt;
  }
}
std::string_view extractExtension(std::string_view filename) { return filename.substr(filename.rfind('.')); }

void twoStrings() {
  std::string s1, s2;
  std::cout << "entr two strings:\n";
  getline(std::cin, s1);
  getline(std::cin, s2);
  if (is_lt(s1 <=> s2)) {
    std::cout << s1 << "\n";
    std::cout << s2 << "\n";
  } else {
    std::cout << s2 << "\n";
    std::cout << s1 << "\n";
  }
}

/* Return a new modified string
 * Copy everything up to needle, add replacement, repeat
 * copy remainder from after last needle*/
std::string haystack(std::string& haystack, const std::string& needle, const std::string& replacement) {
  auto start = 0;
  std::string output{};
  auto pos = haystack.find(needle);
  while (pos != std::string::npos) {
    output += haystack.substr(start, pos - start) + replacement;
    start = pos + needle.length();
    pos = haystack.find(needle, start);
  }
  if (pos == std::string::npos) {
    output += haystack.substr(start);
  }
  return output;
}

/* Exercise 2-3: */
std::string haystack(std::string_view haystack, const std::string_view needle, const std::string_view replacement) {
  auto start = 0;
  std::string output{};
  auto pos = haystack.find(needle);
  while (pos != std::string::npos) {
    output += haystack.substr(start, pos - start);
    output += replacement;
    start = pos + needle.length();
    pos = haystack.find(needle, start);
  }
  if (pos == std::string::npos) {
    output += haystack.substr(start);
  }
  return output;
}

/* Exercise 2-4: */
template <>
void readNumbers(std::vector<double>& numbers) {
  double num;
  std::cout << "Enter floats, each number followed by ENTER\n";
  std::cin >> num;
  while (num != 0.0) {
    numbers.push_back(num);
    std::cin >> num;
  }
}
constexpr size_t columnWidth = 18;
constexpr size_t NumberLength = 12;
struct ColWidths {
  std::string_view title;
  const size_t TitleWidth = (columnWidth / 2) + (title.length() / 2);
  const size_t TitleTailWidth = (columnWidth - title.length()) / 2;
  const size_t NumberWidth = (columnWidth / 2) + (NumberLength / 2);
  const size_t NumberTailWidth = (columnWidth - NumberLength) / 2;
};
ColWidths col1{.title{"Fixed length"}};
ColWidths col2{.title{"Scientific"}};

template <>
/* Output right adjusted text in fields of width heading.length + margin */
void presentNumbers(const std::vector<double>& numbers) {
  std::cout << "|" << std::setw(col1.TitleWidth) << col1.title << std::setw(col1.TitleTailWidth) << "|";
  std::cout << std::setw(col2.TitleWidth) << col2.title << std::setw(col2.TitleTailWidth) << "|"
            << "\n";
  for (const auto& num : numbers) {
    std::cout << "|" << std::setw(col1.NumberWidth) << std::fixed << num;
    std::cout << std::setw(col1.NumberTailWidth) << "|";
    std::cout << std::setw(col2.NumberWidth) << std::scientific << num;
    std::cout << std::setw(col2.NumberTailWidth) << "|"
              << "\n";
  }
}
// (const char [9])"Format 1"
// (const char [12])"5678.000000"
// (const char [13])"5.678000e+03"
// (const char [20])"      Format 1     "
// auto x = "      Format 1     ";