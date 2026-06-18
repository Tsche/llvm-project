// RUN: %clang_cc1 -fsyntax-only -verify -std=c++17 %s

// Test that flag_enum values are properly printed in diagnostic messages

enum class __attribute__((flag_enum)) FlagEnum {
  EMPTY = 0,
  FLAG_A = 1,
  FLAG_B = -2,
  FLAG_C = 0,
  FLAG_D = 0
};

enum __attribute__((flag_enum)) UnscopedFlagEnum {
  EMPTY = 0,
  FLAG_A = 1,
  FLAG_B = -2,
  FLAG_C = 0,
  FLAG_D = 0
};

constexpr FlagEnum operator|(FlagEnum r, FlagEnum l) {
  return (FlagEnum)((unsigned)(r) | (unsigned)(l));
}

template<auto E> struct FlagTemplate {
  using type = decltype(E);
  static_assert(E == (type)0, "");
};

FlagTemplate<FlagEnum::FLAG_A> test1;

constexpr FlagEnum foo = FlagEnum::FLAG_A;
static_assert(foo == FlagEnum(0), "");

// FlagTemplate<(FlagEnum)(FLAG_A | FLAG_B)> test2;
// FlagTemplate<(FlagEnum)(FLAG_A | FLAG_C)> test3;
FlagTemplate<(FlagEnum)(FlagEnum::FLAG_A | FlagEnum::FLAG_B | FlagEnum::FLAG_C)> test4;
FlagTemplate<(UnscopedFlagEnum)(FLAG_A | FLAG_B | FLAG_C)> test5;

// int arr[FlagEnum::FLAG_A] = {};
// int (&arr2)[FlagEnum::FLAG_B] = arr;