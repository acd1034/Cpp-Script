#include <bits/stdc++.h>
// constructorのadlはこうやるらしい
template <typename It>
struct X {
  It i;
  template <class R>
  X(R&& r)
    : i([&]() {
        using std::begin;
        return begin(r);
      }()) {}
};
struct base {
  virtual void say() { std::cout << "base\n"; }
  void introduce() { say(); }
};
struct derived : base {
  void say() override { std::cout << "derived\n"; }
};
template <typename T, std::enable_if_t<std::is_rvalue_reference_v<T&&>, std::nullptr_t> = nullptr>
void f(T&& t) {
  std::cout << "T&&\n";
}
template <typename T>
void f(T const& t) {
  std::cout << "T const&\n";
}

int main() {
  f(1);
  auto a = 1;
  f(a);
}
