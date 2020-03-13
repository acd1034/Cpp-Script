#include <iostream>
template <class CharT, class Traits, class R>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  const char* dlm = "";
  for (const auto& x : r) os << std::exchange(dlm, " ") << x;
  return os;
}
int main() {
  using namespace std::literals;
  std::cout << "Hello world!"sv << std::endl;
}
