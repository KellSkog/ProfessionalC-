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
}
TEST_CASE("case") {
  SUBCASE("sub") {}
}