#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <initializer_list>
#include <iostream>
#include <string>

#include "crashCourse.hpp"
#include "doctest.h"

#define IgnoreMissingFieldInitializers \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wmissing-field-initializers\"")
#define RestoreMissingFieldInitializers _Pragma("GCC diagnostic pop")

TEST_CASE("ThreeWayComparison") {
  SUBCASE("1 eq 1") { CHECK(threeWayComparison(1, 1) == std::strong_ordering::equal); }
  SUBCASE("1 less 2") { CHECK(threeWayComparison(1, 2) == std::strong_ordering::less); }
  SUBCASE("2 greater 1") { CHECK(threeWayComparison(2, 1) == std::strong_ordering::greater); }
}
TEST_CASE("ThreeWayComparison-HeaderOnly") {
  SUBCASE("1 eq 1") { CHECK(threeWayComparisonHO(1, 1) == std::strong_ordering::equal); }
  SUBCASE("1 less 2") { CHECK(threeWayComparisonHO(1, 2) == std::strong_ordering::less); }
  SUBCASE("2 greater 1") { CHECK(threeWayComparisonHO(2, 1) == std::strong_ordering::greater); }
}
TEST_CASE("std::pair") {
  std::pair twoThings{3.14F, "Pi"};
  SUBCASE("first") { CHECK(twoThings.first == 3.14F); }
  SUBCASE("second") { CHECK(twoThings.second == "Pi"); }
  twoThings.first = 2 * twoThings.first;
  SUBCASE("firstMutate") { CHECK(twoThings.first == 6.28F); }
}
TEST_CASE("std::optional") {
  SUBCASE("first") {
    CHECK(getValue(true) == 42);
    SUBCASE("second") { CHECK(getValue(false) == std::nullopt); }
    SUBCASE("tird") { CHECK_FALSE(getValue(false).has_value()); }
    SUBCASE("forth") { CHECK_EQ(getValue(false).value_or(666), 666); }
  }
}
TEST_CASE("Structured bindings") {
  SUBCASE("struct") {
    auto [a, b] = getStructBindStruct();
    CHECK_EQ(a, 666);
    CHECK_EQ(b, 1.5F);
  }
  SUBCASE("array") {
    auto [a, b] = getStructBindArray();
    CHECK_EQ(a, 3);
    CHECK_EQ(b, 14);
  }
  SUBCASE("pair") {
    auto [a, b] = getStructBindPair();
    CHECK_EQ(a, 3);
    CHECK_EQ(b, 0.14);
  }
}
TEST_CASE("initializer list") {
  SUBCASE("array") {
    int sum = 0;
    for (std::array arr{1, 2, 3, 4}; int i : arr) {
      sum += i;
    }
    CHECK_EQ(sum, 10);
  }
  SUBCASE("designated initializer") {
    // StructBindStruct str{.b=3.14F, .A=42}; identifier "b" out-of-order initializers are nonstandard in C++
    StructBindStruct str{.A = 42, .b = 3.14F};
    CHECK_EQ(str.A, 42);
    CHECK_EQ(str.b, 3.14F);
    // IgnoreMissingFieldInitializers;
    // With default values, all initializers are present!
    StructBindStruct str2{
        .b = 1.5F};  // warning: missing initializer for member ‘StructBindStruct::A’ [-Wmissing-field-initializers]
    // RestoreMissingFieldInitializers;
    CHECK_EQ(str2.A, 666);
    CHECK_EQ(str2.b, 1.5F);
  }
}
TEST_CASE("takesValue") {
  // more than one instance of overloaded function "takesValue" matches the argument list:C/C++(308)
  SUBCASE("value") { CHECK_EQ(takesValue(0), 666); }  // 0 != NULL
  SUBCASE("pointer") { CHECK_EQ(takesValue(nullptr), -666); }
}
TEST_CASE("constness") {
  SUBCASE("ptr to const") {
    int a = 1;
    int b = 2;
    const int *ptrToConst = &a;
    ptrToConst = &b;
    CHECK_EQ(*ptrToConst, b);
  }
  SUBCASE("const ptr") {
    int a = 1;
    int b = 2;
    int *const constPtr = &a;
    *constPtr = b;
    CHECK_EQ(*constPtr, b);
    CHECK_EQ(a, b);
  }
  SUBCASE("const ptr const") {
    int a = 1;
    const int *const constPtr = &a;
    // Can not change neither constPtr nor *constPtr
    CHECK_EQ(*constPtr, a);
    CHECK_EQ(constPtr, &a);
  }
}
void changePtr(int *z, int **zzz) {
  *zzz = new int[1];
  *zzz[0] = *z;
}
TEST_CASE("separateOddsAndEvens") {
  // Create an array of ints on heap
  // assign the value of the array to the new array pointed to by the ** received
  constexpr int arrSize = 9;
  SUBCASE("changePtr") {
    int b{42};
    int d{666};
    int *c{&b};
    int **a = &c;
    changePtr(&d, a);
    CHECK_NE(a, nullptr);
    CHECK_EQ(*a[0], d);
  }
  SUBCASE("to the point") {
    int a;
    int *ab = &a;
    CHECK_EQ(*ab, a);
    int *aa[]{ab};  // ab == &a
    int **aaa = aa;
    CHECK_EQ(*aaa[0], *ab);
    CHECK_EQ(**aaa, *ab);
    CHECK_EQ(**aaa, a);
    int *b = aaa[0];
    CHECK_EQ(*b, a);
  }

  SUBCASE("the real McCoy") {
    int oddsAndEven[arrSize]{1, 15, 37, 22, 47, 28, 72, 64, 99};
    size_t numEven, numOdd;
    int *odds{nullptr};
    int *evens{nullptr};

    separateOddsAndEvens(oddsAndEven, arrSize, &odds, &numOdd, &evens, &numEven);

    CHECK_EQ(numEven, 4);
    CHECK_EQ(numOdd, 5);
    int evenFacit[]{22, 28, 72, 64};
    for (size_t i = 0; i < numEven; ++i) {
      CHECK_EQ(evens[i], evenFacit[i]);
    }
    int oddFacit[]{1, 15, 37, 47, 99};
    for (size_t i = 0; i < numEven; ++i) {
      CHECK_EQ(odds[i], oddFacit[i]);
    }

    delete[] odds;
    odds = nullptr;
    delete[] evens;
    evens = nullptr;
  }
}
TEST_CASE("betterSeparateOddsAndEvens") {
  constexpr size_t arrSize = 9;
  SUBCASE("changePtr") {
    int oddsAndEven[]{1, 15, 37, 22, 47, 28, 72, 64, 99};
    size_t numEven, numOdd;
    int *odds{nullptr};
    int *evens{nullptr};

    betterSeparateOddsAndEvens(oddsAndEven, arrSize, numEven, numOdd, odds, evens);
    CHECK_EQ(numEven, 4);
    CHECK_EQ(numOdd, 5);
    int evenFacit[]{22, 28, 72, 64};
    for (size_t i = 0; i < numEven; ++i) {
      CHECK_EQ(evens[i], evenFacit[i]);
    }
    int oddFacit[]{1, 15, 37, 47, 99};
    for (size_t i = 0; i < numEven; ++i) {
      CHECK_EQ(odds[i], oddFacit[i]);
    }
  }
}
TEST_CASE("bestSeparateOddsAndEvens") {
  std::vector<int> vecUnSplit{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  SUBCASE("sub") {
    std::vector<int> odds, evens;
    evenBetterSeparateOddsAndEvens(vecUnSplit, odds, evens);
    for (auto num : odds) {
      CHECK_NE(num % 2, 0);
    }
    for (auto num : evens) {
      CHECK_EQ(num % 2, 0);
    }
  }
}
TEST_CASE("AirlineTicket") {
  SUBCASE("create") { AirlineTicket ticket{}; }
  SUBCASE("set name") {
    AirlineTicket ticket{};
    std::string name = "Fritiof Nilsson Piraten";
    ticket.setPassengerName(name);
    CHECK_EQ(ticket.getPassengerName(), name);
  }
  SUBCASE("frequentFlyer") {
    AirlineTicket ticket{};
    auto num = ticket.getFfrequentFlyerNumber();
    CHECK_EQ(num, std::nullopt);
    ticket.setFfrequentFlyerNumber(42);
    CHECK_EQ(ticket.getFfrequentFlyerNumber(), 42);
  }
}
TEST_CASE("Strings") {
  // Syntax: R"d-char-sequence(r-char-sequence)d-char-sequence"
  SUBCASE("raw string") {
    std::string hello{R"(Hello "World"!)"};
    CHECK_EQ(hello, "Hello \"World\"!");
    const char *hello2{R"delimiter(Hello "(World)"!)delimiter"};
    CHECK_EQ(hello2, "Hello \"(World)\"!");
  }
  SUBCASE("string concat") {
    std::string a{"12"};
    std::string b{"34"};
    CHECK_EQ(a + b, "1234");
    a += b;
    CHECK_EQ(a, "1234");
  }
  SUBCASE("string compare") {
    std::string a{"12"};
    std::string b{"34"};
    CHECK_LT(a.compare(b), 0);
    CHECK_GT(b.compare(a), 0);

    CHECK(is_lt(a <=> b));  // C++20 spaceship!!!
    CHECK(is_gt(b <=> a));
  }
  SUBCASE("Operations on strings") {
    [[maybe_unused]] auto charPtr{"text"};                                  // const char *charPtr
    [[maybe_unused]] const auto charPtr2{"text2"};                          // const char *const charPtr2
    std::string testString{"The quick brown fox jumps over the lazy dog"};  // (const char [44])
    CHECK_EQ(testString.substr(4, 5), "quick");
    CHECK_EQ(testString.find("brown"), 10);
    CHECK_EQ(testString.find("eager"),
             std::string::npos);  // static const std::size_t std::string::npos = 18446744073709551615UL
    testString.replace(testString.find("brown"), 5, "eager");
    CHECK_EQ(testString.find("eager"), 10);
    CHECK(testString.starts_with("The"));
    CHECK(testString.ends_with("dog"));
    // std::sort(testString.begin(), testString.end());
    // std::cout << testString << "\n";
  }
}
TEST_CASE("Inline namespace") {
  SUBCASE("top") {
    using namespace top;
    [[maybe_unused]] auto text{"Hello"s};
  }
  SUBCASE("middle") {
    using namespace top::middle;
    [[maybe_unused]] auto text{"Hello"s};
  }
  SUBCASE("bottom") {
    using namespace top::middle::bottom;
    [[maybe_unused]] auto text{"Hello"s};
  }
  SUBCASE("ekzakt") {
    using namespace std::literals::string_literals;
    [[maybe_unused]] auto text{"Hello"s};
  }
  SUBCASE("fail") {
    using namespace Top;
    // auto text{"Hello"s}; Without inline, names does not propagate up
  }
}
#include <charconv>
TEST_CASE("Numeric Conversions") {
  SUBCASE("toString") { CHECK_EQ(std::to_string(3.14), "3.140000"); }
  SUBCASE("stoi") { CHECK_EQ(std::stoi("101010", 0, 2), 42); }
  SUBCASE("stol") { CHECK_EQ(std::stol("42"), 42L); }
  SUBCASE("stoul") { CHECK_EQ(std::stoul("42"), 42UL); }
  SUBCASE("stoll") { CHECK_EQ(std::stoll("42"), 42LL); }
  SUBCASE("stoull") { CHECK_EQ(std::stoull("42"), 42ULL); }
  SUBCASE("stof") { CHECK_EQ(std::stof("3.14"), 3.14F); }
  SUBCASE("stod") { CHECK_EQ(std::stod("3.14"), 3.14); }
  SUBCASE("stold") { CHECK_EQ(std::stold("3.14"), 3.14L); }
  SUBCASE("perfect round-tripping") {
    constexpr size_t BufferSize{50};
    double value1{0.314};
    std::string out(BufferSize, ' ');  // A string of BufferSize space characters.
    auto [ptr1, error1]{std::to_chars(out.data(), out.data() + out.size(), value1)};
    CHECK_EQ(error1, std::errc{});  // std::errc has no enumeration for 0!
    std::cout << "std::errc{}" << static_cast<int>(std::errc{}) << "\n";
    double value2;
    auto [ptr2, error2]{std::from_chars(out.data(), out.data() + out.size(), value2)};
    CHECK_EQ(error2, std::errc{});
    CHECK_EQ(value1, value2);
  }
}

TEST_CASE("string_view") {
  /* C++17 introduced the std::string_view class, which is an instantiation of the
   * std::basic_string_view class template, and defined in <string_view>.
   * A string_view is basically a drop-in replacement for const string& but without the overhead.*/
  SUBCASE("sub") {
    std::string filename{R"(c:\temp\my file.ext)"};
    CHECK_EQ(extractExtension(filename), ".ext");  // filename is never copied!!
    const char *cString{R"(c:\temp\my file.ext)"};
    CHECK_EQ(extractExtension(cString), ".ext");  // Constructs from any form of string
  };
}
TEST_CASE("Exercise 2-2") {
  std::string testString{"The quick brown fox jumps over the lazy dog"};  // (const char [44])
  std::string replacement{"blue"};
  std::string needle{"brown"};

  SUBCASE("blue") {
    std::string result{haystack(testString, needle, replacement)};
    CHECK_EQ(result, "The quick blue fox jumps over the lazy dog");
  }
  SUBCASE("repeated") {
    std::string testString2{"The quick brown fox brown over the brown dog"};
    std::string result{haystack(testString2, needle, replacement)};
    CHECK_EQ(result, "The quick blue fox blue over the blue dog");
  }
  SUBCASE("first and last") {
    std::string testString2{"brown quick brown fox brown over the dog which is brown"};
    std::string result{haystack(testString2, needle, replacement)};
    CHECK_EQ(result, "blue quick blue fox blue over the dog which is blue");
  }
}
TEST_CASE("Exercise 2-3") {
  std::string_view replacement{"blue"};
  std::string_view needle{"brown"};
  SUBCASE("blue") {
    std::string_view testString{"The quick brown fox brown over the brown dog"};
    std::string result{haystack(testString, needle, replacement)};
    CHECK_EQ(result, "The quick blue fox blue over the blue dog");
  }
  SUBCASE("repeated") {
    std::string_view testString{"The quick brown fox brown over the brown dog"};
    std::string result{haystack(testString, needle, replacement)};
    CHECK_EQ(result, "The quick blue fox blue over the blue dog");
  }
  SUBCASE("first and last") {
    std::string_view testString{"brown quick brown fox brown over the dog which is brown"};
    std::string result{haystack(testString, needle, replacement)};
    CHECK_EQ(result, "blue quick blue fox blue over the dog which is blue");
  }
}
TEST_CASE("case") {
  SUBCASE("sub") {}
}
