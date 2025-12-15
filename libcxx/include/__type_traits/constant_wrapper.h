//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___TYPE_TRAITS_CONSTANT_WRAPPER_H
#define _LIBCPP___TYPE_TRAITS_CONSTANT_WRAPPER_H

#include <__config>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

#if _LIBCPP_STD_VER >= 26

template <class _Tp>
struct __cw_fixed_value {
  using type = _Tp;
  _Tp __data;
  constexpr __cw_fixed_value(type __v) noexcept : __data(__v) {}
};

template <class _Tp, size_t _Extent>
struct __cw_fixed_value<_Tp[_Extent]> {
  using type = _Tp[_Extent];
  _Tp __data[_Extent];

  constexpr __cw_fixed_value(_Tp (&__arr)[_Extent]) noexcept : __cw_fixed_value(__arr, make_index_sequence<_Extent>()) {}

private:
  template <size_t... _Idx>
  constexpr __cw_fixed_value(_Tp (&__arr)[_Extent], index_sequence<_Idx...>) noexcept : __data{__arr[_Idx]...} {}
};

template <class _Tp, size_t _Extent>
__cw_fixed_value(_Tp (&)[_Extent]) -> __cw_fixed_value<_Tp[_Extent]>;

template <__cw_fixed_value _Val, class = typename decltype(_Val)::type>
struct constant_wrapper;

template <class _Tp>
concept __constexpr_param = requires { typename constant_wrapper<_Tp::value>; };

struct __cw_operators {
  // unary operators
  template <__constexpr_param _Tp>
  friend constexpr auto operator+(_Tp) noexcept -> constant_wrapper<(+_Tp::value)> {
    return {};
  }

  template <__constexpr_param _Tp>
  friend constexpr auto operator-(_Tp) noexcept -> constant_wrapper<(-_Tp::value)> {
    return {};
  }

  template <__constexpr_param _Tp>
  friend constexpr auto operator~(_Tp) noexcept -> constant_wrapper<(~_Tp::value)> {
    return {};
  }

  template <__constexpr_param _Tp>
  friend constexpr auto operator!(_Tp) noexcept -> constant_wrapper<(!_Tp::value)> {
    return {};
  }

  template <__constexpr_param _Tp>
  friend constexpr auto operator&(_Tp) noexcept -> constant_wrapper<(&_Tp::value)> {
    return {};
  }

  template <__constexpr_param _Tp>
  friend constexpr auto operator*(_Tp) noexcept -> constant_wrapper<(*_Tp::value)> {
    return {};
  }

  // binary operators

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator+(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value + _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator-(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value - _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator*(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value * _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator/(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value / _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator%(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value % _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator<<(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value << _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator>>(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value >> _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator&(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value & _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator|(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value | _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator^(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value ^ _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
    requires(!is_constructible_v<bool, decltype(_Lhs::value)> || !is_constructible_v<bool, decltype(_Rhs::value)>)
  friend constexpr auto operator&&(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value && _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
    requires(!is_constructible_v<bool, decltype(_Lhs::value)> || !is_constructible_v<bool, decltype(_Rhs::value)>)
  friend constexpr auto operator||(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value || _Rhs::value)> {
    return {};
  }

  // comparisons
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator<=>(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value <=> _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator<(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value < _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator<=(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value <= _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator==(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value == _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator!=(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value != _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator>(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value > _Rhs::value)> {
    return {};
  }
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator>=(_Lhs, _Rhs) noexcept -> constant_wrapper<(_Lhs::value >= _Rhs::value)> {
    return {};
  }

  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator,(_Lhs, _Rhs) noexcept = delete;
  template <__constexpr_param _Lhs, __constexpr_param _Rhs>
  friend constexpr auto operator->*(_Lhs, _Rhs) noexcept -> constant_wrapper<_Lhs::value->*(_Rhs::value)> {
    return {};
  }

  // call and index
  template <__constexpr_param _Tp, __constexpr_param... _Args>
  constexpr auto operator()(this _Tp, _Args...) noexcept
    requires requires { constant_wrapper<_Tp::value(_Args::value...)>(); }
  {
    return constant_wrapper<_Tp::value(_Args::value...)>{};
  }
  template <__constexpr_param _Tp, __constexpr_param... _Args>
  constexpr auto operator[](this _Tp, _Args...) noexcept -> constant_wrapper<(_Tp::value[_Args::value...])> {
    return {};
  }

  // pseudo-mutators
  template <__constexpr_param _Tp>
  constexpr auto operator++(this _Tp) noexcept
    requires requires(_Tp::value_type __x) { ++__x; }
  {
    return constant_wrapper<[] {
      auto __c = _Tp::value;
      return ++__c;
    }()>{};
  }
  template <__constexpr_param _Tp>
  constexpr auto operator++(this _Tp, int) noexcept
    requires requires(_Tp::value_type __x) { __x++; }
  {
    return constant_wrapper<[] {
      auto __c = _Tp::value;
      return __c++;
    }()>{};
  }
  template <__constexpr_param _Tp>
  constexpr auto operator--(this _Tp) noexcept
    requires requires(_Tp::value_type __x) { --__x; }
  {
    return constant_wrapper<[] {
      auto __c = _Tp::value;
      return --__c;
    }()>{};
  }
  template <__constexpr_param _Tp>
  constexpr auto operator--(this _Tp, int) noexcept
    requires requires(_Tp::value_type __x) { __x--; }
  {
    return constant_wrapper<[] {
      auto __c = _Tp::value;
      return __c--;
    }()>{};
  }

  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator+=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x += _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v += _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator-=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x -= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v -= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator*=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x *= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v *= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator/=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x /= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v /= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator%=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x %= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v %= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator&=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x &= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v &= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator|=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x |= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v |= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator^=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x ^= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v ^= _Rhs::value;
    }()>{};
  }

  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator<<=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x <<= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v <<= _Rhs::value;
    }()>{};
  }
  template <__constexpr_param _Tp, __constexpr_param _Rhs>
  constexpr auto operator>>=(this _Tp, _Rhs) noexcept
    requires requires(_Tp::value_type __x) { __x >>= _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v = _Tp::value;
      return __v >>= _Rhs::value;
    }()>{};
  }
};

template <__cw_fixed_value _Val, class>
struct constant_wrapper : __cw_operators {
  static constexpr const auto& value = _Val.data;
  using type                         = constant_wrapper;
  using value_type                   = typename decltype(_Val)::type;

  template <__constexpr_param _Rhs>
  constexpr auto operator=(_Rhs) const noexcept
    requires requires(value_type __x) { __x = _Rhs::value; }
  {
    return constant_wrapper<[] {
      auto __v   = value;
      return __v = _Rhs::value;
    }()>{};
  }

  constexpr operator decltype(auto)() const noexcept { return value; }
};

template <__cw_fixed_value _Val>
constexpr auto cw = constant_wrapper<_Val>{};

#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___TYPE_TRAITS_CONSTANT_WRAPPER_H
