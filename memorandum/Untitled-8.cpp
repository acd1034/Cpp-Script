// 20190816 experiment
#include <iostream>
using namespace std;
namespace ns {
// forward int=>int&, int&=>int&, int&&=>int&&
template <typename T>
constexpr T &&forward(remove_reference_t<T> &t) noexcept {
  return static_cast<T &&>(t);
}
template <typename T>
constexpr T &&forward(remove_reference_t<T> &&t) noexcept {
  return static_cast<T &&>(t);
}
};  // namespace ns
// template <typename T>
// void f(int& t){
//   static_assert(std::is_same_v<decltype(t),int&>);
// }
template <typename T>
auto f(T &&t) -> T & {
  // f(int) => T,T&,T&&=int&
  // f(int&) => T,T&,T&&=int&
  // f(int&&) => T=int, T&=int&, T&&=int&&
  return {};
}
template <typename T>
auto g(T &&t) -> T && {
  return {};
}
int32_t main() {
  {  // templateの型推論規則
    static_assert(is_same_v<decay_t<int>, int>, "");
    static_assert(is_same_v<decay_t<int &>, int>, "");
    static_assert(is_same_v<decay_t<int &&>, int>, "");
    static_assert(is_same_v<decay_t<int *>, int *>, "");
    static_assert(is_same_v<decay_t<int const>, int>, "");
    static_assert(is_same_v<decay_t<int const &>, int>, "");
  }
  {  // forwarding reference
    int lval{};
    int &lvalref{lval};
    static_assert(is_same_v<decltype(f(lval)), int &>, "");
    static_assert(is_same_v<decltype(f(move(lval))), int &>, "");
    static_assert(is_same_v<decltype(g(lval)), int &>, "");
    static_assert(is_same_v<decltype(g(move(lval))), int &&>, "");
  }
  {  // rvalrefそのものはlvalue
    int &&rvalref{0};
    int &lvalref{rvalref};
  }
  // オーバーロード解決の優先順位？
}
