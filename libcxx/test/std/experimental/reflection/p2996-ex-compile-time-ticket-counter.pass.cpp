//===----------------------------------------------------------------------===//
//
// Copyright 2024 Bloomberg Finance L.P.
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03 || c++11 || c++14 || c++17 || c++20
// ADDITIONAL_COMPILE_FLAGS: -freflection

// <experimental/reflection>
//
// [reflection]
//
// RUN: %{build}
// RUN: %{exec} %t.exe > %t.stdout

#include <experimental/meta>

#include <print>


template<int N> struct Helper;

class TU_Ticket {
public:
  static consteval int next() {
    int k = 0;

    // Search for the next incomplete 'Helper<k>'.
    std::meta::info r;
    while (is_complete_type(r = substitute(^^Helper,
                                             { std::meta::reflect_value(k) })))
      ++k;

    // Define 'Helper<k>' and return its index.
    define_aggregate(r, {});
    return k;
  }
};

constexpr auto v1 = TU_Ticket::next();
constexpr auto v2 = TU_Ticket::next();
constexpr auto v3 = TU_Ticket::next();

int main() {
  // RUN: grep "0, 1, 2" %t.stdout
  std::println("{}, {}, {}", v1, v2, v3);
}
