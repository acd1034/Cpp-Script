/// @file core.hpp
#pragma once
#include <cassert>          // assert
#include <cstddef>          // size_t, ptrdiff_t
#include <cstdint>          // int32_t
#include <initializer_list> // initializer_list
#include <iosfwd>
#include <tuple> // tuple
#include <type_traits>
#include <utility>      // move, forward, pair
#include <gsl/gsl_util> // final_action, narrow_cast, narrow, at
#include <gsl/span>

namespace ns {
  inline namespace os {
    template <class CharT, class Traits, class T, std::size_t Extent>
    auto& operator<<(std::basic_ostream<CharT, Traits>& os, gsl::span<T, Extent> s) {
      const char* dlm = "";
      for (const auto& x : s) {
        os << std::exchange(dlm, " ") << dlm << x;
      }
      return os;
    }
  } // namespace os
} // namespace ns
