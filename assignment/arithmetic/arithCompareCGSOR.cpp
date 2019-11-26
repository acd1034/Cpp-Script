#include "matrix.h"
#include <chrono>
#include <random>
using namespace std;
using namespace myns;

template<size_t M>
Vector<M> cgMethod(
  const Vector<M>& v,
  const Matrix<M, M>& m,
  Vector<M>& rem,
  Vector<M>& p) {
    using val_t = typename Vector<M>::val_t;
    const Vector<M> mp = m*p;
    const val_t tpmp = t(p)*mp;
    const val_t c = t(rem)*p/tpmp;
    const Vector<M> ret = v + c*p;
    rem = rem - c*mp;
    p = rem - t(rem)*mp/tpmp*p;
    return ret;
}
template<size_t M>
Vector<M> sorMethod(
  const Vector<M>& x,
  const Matrix<M, M>& a,
  const Vector<M>& b,
  const double w
) {
  int i, j;
  Vector<M> y;
  Vector<M> ret(y);
  for(i = 0; i < x.size_; ++i) {
    y.fill(0);
    for(j = 0; j < i; ++j) y(i) -= a(i, j)*ret(j);
    for(++j; j < y.size_; ++j) y(i) -= a(i, j)*x(j);
    ret(i) = (1 - w)*x(i) + w*(y(i) + b(i))/a(i, i);
  }
  return ret;
}

int main() {
  const double c = 2;
  #define N 1001
  Matrix<N, N> a;
  Vector<N> b;
  Vector<N> x(b);
  for(int i = 0; i < a.size_; ++i) {
    if(i%(N+1) == 0) a[i] = c;
    else if(i%(N+1) == 1) a[i] = -1;
    else if(i%(N+1) == N) a[i] = -1;
  }
  for(int i = 0; i < b.size_; ++i) b[i] = i - N/2;
  
  const int lim = 500;
  const double eps = 0.000001;
  printf("cg\n");
  Vector<N> y = x;
  Vector<N> r = b - a*y;
  Vector<N> p = r;
  printf("%d,", 0); print(norm(r));
  auto start = chrono::system_clock::now();
  /*for(int i = 1; i < lim; ++i) {
    y = cgMethod(y, a, r, p);
    printf("%d,", i);
    print(norm(r));
    if(norm(r) < eps) break;
  }*/
  auto end = chrono::system_clock::now();
  double msec = chrono::duration<double, milli>(end - start).count();
  printf("%lfmsec\n", msec);
  print(y, "", " ", "");

  printf("\nsor\n");
  const double w = 1.5;
  Vector<N>::val_t d = norm(a*x - b);
  printf("%d,", 0); print(d);
  start = chrono::system_clock::now();
  for(int i = 1; i < lim; ++i) {
    x = sorMethod(x, a, b, w);
    d = norm(a*x - b);
    printf("%d,", i); print(d);
    if(d < eps) break;
  }
  end = chrono::system_clock::now();
  msec = chrono::duration<double, milli>(end - start).count();
  printf("%lfmsec\n", msec);
  print(x, "", " ", "");
  return 0;
}
