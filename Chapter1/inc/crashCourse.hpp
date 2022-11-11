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