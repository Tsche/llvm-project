//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___TYPE_TRAITS_POINTS_TO_H
#define _LIBCPP___TYPE_TRAITS_POINTS_TO_H

#include <__config>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

#if _LIBCPP_STD_VER >= 26
inline consteval bool points_to_local(const void * ptr) noexcept {
  return __consteval_points_to_local(ptr);
}

inline consteval bool points_to_global(const void * ptr) noexcept {
  return __consteval_points_to_global(ptr);
}

inline consteval bool points_to_type_info(const void * ptr) noexcept {
  return __consteval_points_to_type_info(ptr);
}

inline consteval bool points_to_dynamic_allocation(const void * ptr) noexcept {
  return __consteval_points_to_dynamic_allocation(ptr);
}

inline consteval bool points_to_constexpr(const void * ptr) noexcept {
  return __consteval_points_to_constexpr(ptr);
}

inline consteval bool points_to_past_end(const void * ptr) noexcept {
  return __consteval_points_to_past_end(ptr);
}
#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___TYPE_TRAITS_IS_CONSTANT_EVALUATED_H
