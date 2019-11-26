#include <iostream>
#include <utility>
#include <cmath>
using namespace std;
using r2 = pair<double, double>;
using m2r = pair<r2, r2>;
using func = function<double(r2)>;
using jacobi = function<r2(r2)>;
using hess = function<m2r(r2)>;
void show(const r2& v) {
  printf("%.8lf %.8lf\n", v.first, v.second);
}
void show(const m2r& m) {
  printf("(%.8lf %.8lf)\n(%.8lf %.8lf)\n",
    m.first.first, m.first.second, m.second.first, m.second.second);
}
r2 operator-(const r2& v) {
  return make_pair(-v.first, -v.second);
}
r2 operator+(const r2& v1, const r2& v2) {
  return make_pair(v1.first + v2.first, v1.second + v2.second);
}
r2 operator-(const r2& v1, const r2& v2) {
  return make_pair(v1.first - v2.first, v1.second - v2.second);
}
r2 operator*(double c, const r2& v) {
  return make_pair(c*v.first, c*v.second);
}
double operator*(const r2& v1, const r2& v2) {
  return v1.first*v2.first + v1.second*v2.second;
}
m2r operator*(double c, const m2r& m) {
  return make_pair(make_pair(c*m.first.first, c*m.first.second),
    make_pair(c*m.second.first, c*m.second.second));
}
r2 operator*(const m2r& m, const r2& v) {
  return make_pair(m.first.first*v.first + m.first.second*v.second,
    m.second.first*v.first + m.second.second*v.second);
}
m2r operator+(const m2r& m1, const m2r& m2) {
  return make_pair(
    make_pair(
      m1.first.first + m2.first.first,
      m1.first.second + m2.first.second
    ),
    make_pair(
      m1.second.first + m2.second.first,
      m1.second.second + m2.second.second
    )
  );
}
m2r operator-(const m2r& m1, const m2r& m2) {
  return make_pair(
    make_pair(
      m1.first.first - m2.first.first,
      m1.first.second - m2.first.second
    ),
    make_pair(
      m1.second.first - m2.second.first,
      m1.second.second - m2.second.second
    )
  );
}
m2r operator*(const m2r& m1, const m2r& m2) {
  return make_pair(
    make_pair(
      m1.first.first*m2.first.first + m1.first.second*m2.second.first,
      m1.first.first*m2.first.second + m1.first.second*m2.second.second
    ),
    make_pair(
      m1.second.first*m2.first.first + m1.second.second*m2.second.first,
      m1.second.first*m2.first.second + m1.second.second*m2.second.second
    )
  );
}
double norm(const r2& v) {
  return sqrt(pow(v.first, 2) + pow(v.second, 2));
}
m2r mm(const r2& v1, const r2& v2) {
  return make_pair(
    make_pair(v1.first*v2.first, v1.first*v2.second),
    make_pair(v1.second*v2.first, v1.second*v2.second)
  );
}
m2r inverse(const m2r& m) {
  double c = m.first.first*m.second.second - m.first.second*m.second.first;
  m2r d = make_pair(make_pair(m.second.second, -m.first.second),
    make_pair(-m.second.first, m.first.first));
  return (1.0/c)*d;
}
double backtracking(const r2& x, const r2& d, const func& f, const jacobi& jf) {
  double a = 0.1;
  const double c = 0.0001;
  const double p = 0.1;
  while(f(x + a*d) > f(x) + c*a*jf(x)*d) {
    a = p*a;
  }
  return a;
}
r2 quasiNewton(const r2& x0, const func& f, const jacobi& jf, m2r& h) {
  r2 d = -(h*jf(x0));
  double a = backtracking(x0, d, f, jf);
  const r2 s = a*d;
  const r2 y = jf(x0+s) - jf(x0);
  const m2r e = make_pair(make_pair(1.0, 0.0), make_pair(0.0, 1.0));
  const double c = 1/(y*s); // ゼロ割が起こり得る
  h = (e - c*mm(s,y))*h*(e - c*mm(y,s)) + c*mm(s,s);
  return x0+s;
}
int main() {
  func f = [](const r2& x) -> double {
    return 100*pow(x.second - pow(x.first, 2), 2) + pow(1.0 - x.first, 2);
  };
  jacobi jf = [](const r2& x) -> r2 {
    return make_pair(
      -400*x.first*(x.second - pow(x.first, 2)) - 2*(1 - x.first),
      200*(x.second - pow(x.first, 2))
    );
  };
  hess hf = [](const r2& x) -> m2r {
    return make_pair(
      make_pair(
        1200*pow(x.first, 2) - 400*x.second + 2,
        -400*x.first
      ),
      make_pair(
        -400*x.first,
        200
      )
    );
  };
  r2 x = make_pair(-1.2, 1.0);
  m2r h = inverse(hf(x));
  /*
  for(int i = 0; i < 50; ++i) {
    x = quasiNewton(x, f, jf, h);
    show(x);
  }
  */
  r2 ans = make_pair(1.0, 1.0);
  int i = 0;
  while(norm(jf(x)) > 0.000001) {
    x = quasiNewton(x, f, jf, h);
    if(i%20 == 0) {
      printf("%d  %.10lf\n", i, norm(x - ans));
    }
    ++i;
  }
  
  return 0;
}