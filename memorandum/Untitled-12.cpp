#include <iostream>
#include <iterator>
#include <type_traits>
namespace ns {
// is_detected
namespace detail {
template <class AlwaysVoid, template <class...> class Op, class... Args>
struct is_detected_impl : std::false_type {};
template <template <class...> class Op, class... Args>
struct is_detected_impl<std::void_t<Op<Args...>>, Op, Args...> : std::true_type {};
} // namespace detail
template <template <class...> class Op, class... Args>
using is_detected = detail::is_detected_impl<void, Op, Args...>;
// range adl未対応、detected_tを使えばいける
namespace detail {
template <class T>
using std_begin_t = decltype(std::begin(std::declval<T>()));
template <class T>
using std_end_t = decltype(std::end(std::declval<T>()));
} // namespace detail
template <class T>
inline constexpr bool is_range_v =
  std::conjunction_v<is_detected<detail::std_begin_t, T&>, is_detected<detail::std_end_t, T&>>;
template <class R, std::enable_if_t<is_range_v<R>, std::nullptr_t> = nullptr>
using range_value_t = decltype(*std::begin(std::declval<R&>()));
} // namespace ns
template <class CharT,
          class Traits,
          class R,
          std::enable_if_t<ns::is_range_v<R> && !ns::is_range_v<ns::range_value_t<R>>,
                           std::nullptr_t> = nullptr>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  const char* dlm = "";
  for (const auto& x : r) os << std::exchange(dlm, " ") << x;
  return os;
}
template <class CharT,
          class Traits,
          class R,
          std::enable_if_t<ns::is_range_v<R> && ns::is_range_v<ns::range_value_t<R>>,
                           std::nullptr_t> = nullptr>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  const char* dlm = "";
  for (const auto& x : r) os << std::exchange(dlm, "\n") << x;
  return os;
}
template <class T, class CharT, class Traits>
void operator|(const T& t, std::basic_ostream<CharT, Traits>& os) {
  os << t << std::endl;
}

#include <list>
int main() {
  using std::cout, std::list;
  list{1, 2, 3, 4, 5, 6} | cout;
  list<list<int>>{{1, 2}, {3, 4}, {5, 6}} | cout;
  list<list<list<int>>>{{{1}, {2}}, {{3}, {4}}, {{5}, {6}}} | cout;
}
