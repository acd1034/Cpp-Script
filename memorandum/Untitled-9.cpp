#include <bits/stdc++.h>
namespace ns {
  template <typename... Dummy>
  struct always_t : std::true_type {};
  template <typename... Dummy>
  struct never_t : std::false_type {};
  // usage: template<typename T, required<...> = nullptr>
  template <typename... Args>
  using required =
    std::enable_if_t<std::conjunction_v<Args...>, std::nullptr_t>;

  template <typename T, typename = void>
  struct has_value_type : std::false_type {};
  template <typename T>
  struct has_value_type<T, std::void_t<typename T::value_type>>
    : std::true_type {};
  // template<typename T>
  // inline constexpr bool has_value_type_v = has_value_type<T>::value;

  template <typename T, typename = void>
  struct has_pre_increment : std::false_type {};
  template <typename T>
  struct has_pre_increment<T, std::void_t<decltype(++std::declval<T>())>>
    : std::true_type {};
  // template<typename T>
  // inline constexpr bool has_pre_increment_v = has_pre_increment<T>::value;

  // typename T::value_type, decltype(++std::declval<T>()),
  // iterator_requirement<T>などは
  // 実体化に成功するか失敗するかのいずれかである「型」
  // has_value_type<T>, has_pre_increment<T>, always_t<T>などは
  // ::valueを持ちtrueかfalseを返す「真偽値」
  template <typename T>
  struct satisfy_iterator_requirement
    : std::conjunction<has_value_type<T>, has_pre_increment<T>> {};
  template <typename T>
  using reverse_iterator_requirement =
    required<has_value_type<T>,
             has_pre_increment<T>,
             always_t<decltype(--std::declval<T>())>>;

  template <typename T, required<satisfy_iterator_requirement<T>> = nullptr>
  void g(T&& t) {}
  struct not_having {};
  struct having {
    using value_type = void;
    void operator++();
    void operator--();
  };
} // namespace ns
int32_t main() {
  using namespace std;
  ns::g(ns::having());
}
