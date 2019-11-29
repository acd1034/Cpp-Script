#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
using namespace std;
using r2     = pair<double, double>;
using func   = function<double(r2)>;
using jacobi = function<r2(r2)>;

r2 operator-(const r2& v) { return make_pair(-v.first, -v.second); }
r2 operator+(const r2& v1, const r2& v2) {
  return make_pair(v1.first + v2.first, v1.second + v2.second);
}
r2 operator-(const r2& v1, const r2& v2) {
  return make_pair(v1.first - v2.first, v1.second - v2.second);
}
r2 operator*(double c, const r2& v) { return make_pair(c * v.first, c * v.second); }
double operator*(const r2& v1, const r2& v2) { return v1.first * v2.first + v1.second * v2.second; }
double norm(const r2& v) { return sqrt(pow(v.first, 2) + pow(v.second, 2)); }
double backtracking(const r2& x, const r2& d, const func& f, const jacobi& jf) {
  double a       = 0.1;
  const double c = 0.0001;
  const double p = 0.1;
  while (f(x + a * d) > f(x) + c * a * jf(x) * d) { a = p * a; }
  return a;
}
r2 gradDescent(const r2& x, const func& f, const jacobi& jf) {
  r2 d     = -jf(x);
  double a = backtracking(x, d, f, jf);
  return x + a * d;
}
int main() {
  func f = [](const r2& x) -> double {
    return 100 * pow(x.second - pow(x.first, 2), 2) + pow(1.0 - x.first, 2);
  };
  jacobi jf = [](const r2& x) -> r2 {
    return make_pair(-400 * x.first * (x.second - pow(x.first, 2)) - 2 * (1 - x.first),
                     200 * (x.second - pow(x.first, 2)));
  };
  r2 x = make_pair(1.2, 1.2);
  // r2 x   = make_pair(-1.2, 1.0);
  r2 ans = make_pair(1.0, 1.0);
  int i  = 0;
  std::cout << setprecision(10) << std::endl;
  while (norm(jf(x)) > 1e-10) {
    x = gradDescent(x, f, jf);
    // if (i % 20 == 0)
    std::cout << i << "," << x.first << "," << x.second << "," << norm(x - ans) << std::endl;
    ++i;
  }
  return 0;
}
