#pragma once
#include <compare>
#include <optional>

enum class COMMAND {
  NOP,
  TWC,
  NODISCARD,
  NORETURN,
  DEPRECATED,
  OPTIONAL,
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