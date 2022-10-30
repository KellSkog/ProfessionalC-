#pragma once
#include <compare>

enum class COMMAND {
  NOP,
  TWC,
};
template <typename T>
std::strong_ordering threeWayComparison(T one, T other);
template <typename T>
std::strong_ordering threeWayComparisonHO(T one, T other)  // Header Only
{
  return one <=> other;
}