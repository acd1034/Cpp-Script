#include <functional>
#include "common.hpp"

namespace ns {
  // identity
  struct identity {
    template <typename T>
    constexpr T&& operator()(T&& t) const noexcept(noexcept(std::forward<T>(t))) {
      return std::forward<T>(t);
    }
  };

  // always_false_v for static_assert
  template <class>
  inline constexpr bool always_false_v = false;

  // overloaded
  // See https://en.cppreference.com/w/cpp/utility/variant/visit
  template <typename... Ts>
  struct overloaded : Ts... {
    using Ts::operator()...;
  };
  // explicit deduction guide (not needed as of C++20)
  template <typename... Ts>
  overloaded(Ts...) -> overloaded<Ts...>;

  // scope_exit
  template <typename Fn>
  struct scope_exit {
  private:
    Fn fn{};
    bool invoke = true;

  public:
    scope_exit() noexcept = default;
    explicit scope_exit(Fn fn) noexcept : fn(std::move(fn)) {}
    scope_exit(scope_exit&& other) noexcept
      : fn(std::move(other.fn)), invoke(std::exchange(other.invoke, false)) {}

    scope_exit(scope_exit const&) = delete;
    void operator=(scope_exit const&) = delete;
    void operator=(scope_exit&&) = delete;
    ~scope_exit() noexcept {
      if (invoke)
        std::invoke(fn);
    }
  };
} // namespace ns
