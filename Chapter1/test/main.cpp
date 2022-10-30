#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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