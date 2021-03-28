#include <cstdint>
#include <type_traits>
#include <utility>

struct MyInteger {
private:
  // member object

public:
  // ctor
  constexpr MyInteger() noexcept                 = default;
  constexpr MyInteger(const MyInteger&) noexcept = default;
  constexpr MyInteger(MyInteger&&) noexcept      = default;
  // assignment
  constexpr MyInteger& operator=(const MyInteger&) noexcept = default;
  constexpr MyInteger& operator=(MyInteger&&) noexcept = default;
  // arithmetic
  constexpr MyInteger operator-() && {
    /* implementation */
    return std::move(*this);
  }
  constexpr MyInteger inverse() && {
    /* implementation */
    return std::move(*this);
  }
  constexpr MyInteger& operator+=(MyInteger&& other) {
    /* implementation */
    return *this;
  }
  constexpr MyInteger& operator*=(MyInteger&& other) {
    /* implementation */
    return *this;
  }
  constexpr MyInteger& operator%=(MyInteger&& other) {
    /* implementation */
    return *this;
  }
  // compare
  friend constexpr bool operator==(const MyInteger& x, const MyInteger& y) noexcept {
    return /* implementation */;
  }
  friend constexpr bool operator<(const MyInteger& x, const MyInteger& y) noexcept {
    return /* implementation */;
  }

  // boilerplate - arithmetic
  constexpr MyInteger operator+() const& noexcept { return *this; }
  constexpr MyInteger operator+() && noexcept { return std::move(*this); }

#define MYINTEGER_DEFINE_PLUS(target_binary_op, source_assignment)                                 \
  constexpr MyInteger& source_assignment(const MyInteger& other) {                                 \
    MyInteger tmp{other};                                                                          \
    return this->source_assignment(std::move(tmp));                                                \
  }                                                                                                \
  friend constexpr MyInteger target_binary_op(const MyInteger& x, const MyInteger& y) {            \
    MyInteger tmp{x};                                                                              \
    tmp.source_assignment(y);                                                                      \
    return tmp;                                                                                    \
  }                                                                                                \
  friend constexpr MyInteger target_binary_op(MyInteger&& x, const MyInteger& y) {                 \
    x.source_assignment(y);                                                                        \
    return std::move(x);                                                                           \
  }                                                                                                \
  friend constexpr MyInteger target_binary_op(const MyInteger& x, MyInteger&& y) {                 \
    MyInteger tmp{x};                                                                              \
    tmp.source_assignment(std::move(y));                                                           \
    return tmp;                                                                                    \
  }                                                                                                \
  friend constexpr MyInteger target_binary_op(MyInteger&& x, MyInteger&& y) {                      \
    x.source_assignment(std::move(y));                                                             \
    return std::move(x);                                                                           \
  }

#define MYINTEGER_DEFINE_MINUS(target_assignment, target_binary_op, source_unary_op,               \
                               source_assignment)                                                  \
  constexpr MyInteger source_unary_op() const& {                                                   \
    MyInteger tmp{*this};                                                                          \
    return std::move(tmp).source_unary_op();                                                       \
  }                                                                                                \
  constexpr MyInteger& target_assignment(MyInteger&& other) {                                      \
    this->source_assignment(std::move(other).source_unary_op());                                   \
    return *this;                                                                                  \
  }                                                                                                \
  MYINTEGER_DEFINE_PLUS(target_binary_op, target_assignment)

  MYINTEGER_DEFINE_PLUS(operator+, operator+=)
  MYINTEGER_DEFINE_PLUS(operator*, operator*=)
  MYINTEGER_DEFINE_PLUS(operator%, operator%=)
  MYINTEGER_DEFINE_MINUS(operator-=, operator-, operator-, operator+=)
  MYINTEGER_DEFINE_MINUS(operator/=, operator/, inverse, operator*=)

#undef MYINTEGER_DEFINE_MINUS
#undef MYINTEGER_DEFINE_PLUS

  // boilerplate - compare
  friend constexpr bool operator!=(const MyInteger& x,
                                   const MyInteger& y) noexcept(noexcept(x == y)) {
    return !(x == y);
  }
  friend constexpr bool operator>(const MyInteger& x,
                                  const MyInteger& y) noexcept(noexcept(y < x)) {
    return y < x;
  }
  friend constexpr bool operator<=(const MyInteger& x,
                                   const MyInteger& y) noexcept(noexcept(y < x)) {
    return !(y < x);
  }
  friend constexpr bool operator>=(const MyInteger& x,
                                   const MyInteger& y) noexcept(noexcept(x < y)) {
    return !(x < y);
  }
}; // MyInteger
