// monte_carlo.cpp
// 与えられたゲームの分布関数を経験分布関数で、
// 平均を標本平均で、標準偏差を標本標準偏差で推定する
// pseudorandom number generator: Mersenne Twister
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a) {
  const char* dlm = "";
  for (const auto& x : a) os << std::exchange(dlm, ",") << x;
  return os;
}

class Game {
private:
  std::array<int, 52> a;
  std::mt19937 engine{std::random_device{}()};

public:
  Game() {
    std::iota(std::begin(a), std::end(a), 0);
    for (auto&& x : a) x /= 4;
  }
  template <typename Itr>
  bool has_pair(Itr first, Itr last) {
    for (auto i = first; i < last; ++i) {
      if (std::count(first, last, *i) > 1) return true;
    }
    return false;
  }
  int operator()() {
    std::shuffle(std::begin(a), std::end(a), engine);
    // std::cout << a << std::endl;
    std::size_t j = 1;
    for (auto i = std::begin(a); i <= std::end(a) - 5; i += 5) {
      if (has_pair(i, i + 5)) return j;
      ++j;
    }
    return 20;
  }
};

auto monte_carlo(std::size_t n) {
  std::array<int, 21> a;
  std::fill(std::begin(a), std::end(a), 0);
  Game game;
  for (; n > 0; --n) ++a[game()];
  return a;
}

int main() {
  using std::cout, std::endl;
  const std::size_t n = 1e8;
  auto a              = monte_carlo(n);
  cout << a << endl;

  double mu = 0, sigma = 0;
  {
    int j = 0;
    for (auto const& x : a) {
      mu += j * x;
      ++j;
    }
    mu /= n;
  }
  {
    int j = 0;
    for (auto const& x : a) {
      sigma += std::pow(j - mu, 2) * x;
      ++j;
    }
    sigma = std::sqrt(sigma / n);
  }
  cout << std::array{mu, sigma} << endl;
}
// result:
// 0,49291810,24822197,12586195,6422919,3294029,1703990,884991,465063,246141,129716,0,0,0,0,0,0,0,0,0,152949
// 2.05567,1.59046
