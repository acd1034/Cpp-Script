#include <bits/stdc++.h>
template <typename T>
inline constexpr bool is_range_v = true;
template <typename T, std::enable_if_t<is_range_v<T>, std::nullptr_t> = nullptr>
using iterator_t = decltype(std::begin(std::declval<T&>()));
template <typename T, std::enable_if_t<is_range_v<T>, std::nullptr_t> = nullptr>
using range_value_t = typename std::iterator_traits<iterator_t<T>>::value_type;
template <typename T, typename BinaryFunction>
class folded_tag {
  T t;
  BinaryFunction f;

public:
  folded_tag(T t, BinaryFunction f) noexcept : t(t), f(f) {}
  template <typename R,
            std::enable_if_t<is_range_v<R>, std::nullptr_t> = nullptr>
  auto operator()(const R& r) {
    std::common_type_t<T, range_value_t<R>> ret{t};
    for (const auto& x : r) ret = f(std::move(ret), x);
    return ret;
  }
  template <typename R,
            std::enable_if_t<!std::is_reference_v<R> && is_range_v<R>,
                             std::nullptr_t> = nullptr>
  auto operator()(R&& r) {
    std::common_type_t<T, range_value_t<R>> ret{t};
    for (auto&& x : r) ret = f(std::move(ret), std::move(x));
    return ret;
  }
  template <typename U>
  auto operator()(std::initializer_list<U> r) {
    std::common_type_t<T, U> ret{t};
    for (auto&& x : r) ret = f(std::move(ret), std::move(x));
    return ret;
  }
};
template <typename T, typename BinaryFunction>
folded_tag<T, BinaryFunction> folded(T&& t, BinaryFunction&& f) {
  return {std::forward<T>(t), std::forward<BinaryFunction>(f)};
}
template <typename R,
          typename T,
          typename BinaryFunction,
          std::enable_if_t<is_range_v<R>, std::nullptr_t> = nullptr>
auto operator|(const R& r, folded_tag<T, BinaryFunction> tag) {
  return tag(r);
}
template <typename R,
          typename T,
          typename BinaryFunction,
          std::enable_if_t<!std::is_reference_v<R> && is_range_v<R>,
                           std::nullptr_t> = nullptr>
auto operator|(R&& r, folded_tag<T, BinaryFunction> tag) {
  return tag(std::move(r));
}
template <typename U, typename T, typename BinaryFunction>
auto operator|(std::initializer_list<U> r, folded_tag<T, BinaryFunction> tag) {
  return tag(std::move(r));
}
template <typename T>
void operator|(const T& t, std::ostream& os) {
  os << t << std::endl;
}
int main() {
  using std::cout;
  std::array{1, 2, 3, 4, 5} | folded(0, [](auto x, auto y) { return x + y; })
    | cout;
}
