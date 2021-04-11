/// @file math.hpp
#pragma once
#include <ccomplex>
#include <cmath>

namespace ns::math {
  template <typename T>
  inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> eps_v = 1e-6;

  inline constexpr double eps = eps_v<double>;

  template <class T>
  struct approx {
  private:
    const T val_;
    const double margin_;

  public:
    constexpr explicit approx(const T& val, double margin = eps) noexcept
      : val_(val), margin_(margin) {}
    constexpr explicit approx(T&& val, double margin = eps) noexcept
      : val_(std::move(val)), margin_(margin) {}

    template <class U>
    friend constexpr bool operator==(const U& x, const approx& y) noexcept {
      // Performs equivalent check of std::fabs(x - y.val_) <= margin_
      // But without the subtraction to allow for INFINITY in comparison
      return (x + y.margin_ >= y.val_) && (y.val_ + y.margin_ >= x);
    }
    template <class U>
    friend constexpr bool operator<(const U& x, const approx& y) noexcept {
      return !(x == y) && (x < y.val_);
    }
    // boilerplate
    template <class U>
    constexpr friend bool operator!=(const U& x, const approx& y) noexcept(noexcept(x == y)) {
      return !(x == y);
    }
    template <class U>
    constexpr friend bool operator>(const U& x, const approx& y) noexcept(noexcept(y < x)) {
      return y < x;
    }
    template <class U>
    constexpr friend bool operator<=(const U& x, const approx& y) noexcept(noexcept(y < x)) {
      return !(y < x);
    }
    template <class U>
    constexpr friend bool operator>=(const U& x, const approx& y) noexcept(noexcept(x < y)) {
      return !(x < y);
    }
  }; // approx

  /// @cond
  template <typename T>
  using enable_if_floating = std::enable_if_t<std::is_floating_point_v<T>, T>;
  /// @endcond

  // clang-format off
  /// e
  template <typename T> inline constexpr enable_if_floating<T> e_v          = 2.718281828459045235360287471352662498L;
  /// log_2 e
  template <typename T> inline constexpr enable_if_floating<T> log2e_v      = 1.442695040888963407359924681001892137L;
  /// log_10 e
  template <typename T> inline constexpr enable_if_floating<T> log10e_v     = 0.434294481903251827651128918916605082L;
  /// log_e 2
  template <typename T> inline constexpr enable_if_floating<T> ln2_v        = 0.693147180559945309417232121458176568L;
  /// log_e 10
  template <typename T> inline constexpr enable_if_floating<T> ln10_v       = 2.302585092994045684017991454684364208L;
  /// pi
  template <typename T> inline constexpr enable_if_floating<T> pi_v         = 3.141592653589793238462643383279502884L;
  /// tau
  template <typename T> inline constexpr enable_if_floating<T> tau_v        = 6.283185307179586476925286766559005768L;
  /// sqrt(2)
  template <typename T> inline constexpr enable_if_floating<T> sqrt2_v      = 1.414213562373095048801688724209698079L;
  /// sqrt(3)
  template <typename T> inline constexpr enable_if_floating<T> sqrt3_v      = 1.732050807568877293527446341505872367L;
  /// sqrt(5)
  template <typename T> inline constexpr enable_if_floating<T> sqrt5_v      = 2.236067977499789696409173668731276235L;
  /// The Euler-Mascheroni constant
  template <typename T> inline constexpr enable_if_floating<T> egamma_v     = 0.577215664901532860606512090082402431L;
  /// Exponential of the Euler-Mascheroni constant
  template <typename T> inline constexpr enable_if_floating<T> exp_egamma_v = 1.781072417990197985236504103107179549L;
  // clang-format on

  // specialization
  inline constexpr double e          = e_v<double>;
  inline constexpr double log2e      = log2e_v<double>;
  inline constexpr double log10e     = log10e_v<double>;
  inline constexpr double ln2        = ln2_v<double>;
  inline constexpr double ln10       = ln10_v<double>;
  inline constexpr double pi         = pi_v<double>;
  inline constexpr double tau        = tau_v<double>;
  inline constexpr double sqrt2      = sqrt2_v<double>;
  inline constexpr double sqrt3      = sqrt3_v<double>;
  inline constexpr double sqrt5      = sqrt5_v<double>;
  inline constexpr double egamma     = egamma_v<double>;
  inline constexpr double exp_egamma = exp_egamma_v<double>;

  /// log natural
  template <class T>
  decltype(auto) ln(T&& x) noexcept(noexcept(std::log(std::forward<T>(x)))) {
    return std::log(std::forward<T>(x));
  }
} // namespace ns::math
