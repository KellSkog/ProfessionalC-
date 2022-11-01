#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>

#include "crashCourse.hpp"
#include "doctest.h"

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