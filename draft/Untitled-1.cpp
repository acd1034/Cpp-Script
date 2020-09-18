#include <cstddef> // size_t, ptrdiff_t
#include <cstdint> // int32_t
#include <utility> // initializer_list, move, forward, pair

#include <iostream>
#include <string_view>

template <class CharT, class Traits, class R>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  std::string_view dlm{""};
  for (const auto& x : r) os << std::exchange(dlm, " ") << x;
  return os;
}

int main() {
  using namespace std::literals;
  std::cout << "Hello world!"sv << std::endl;
}
