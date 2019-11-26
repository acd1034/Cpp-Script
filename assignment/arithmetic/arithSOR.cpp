#include "matrix.cpp"
#include <random>
using namespace std;
using namespace myns;

template<size_t M>
Vector<M> sorMethod(
  const Vector<M>& x,
  const Matrix<M, M>& a,
  const Vector<M>& b,
  const double w
) {
  int i, j;
  Vector<M> y(0);
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
  const double c = 20;
  #define N 100
  Matrix<N, N> a(0);
  Vector<N> b(0);
  Vector<N> x(b);
  for(int i = 0; i < a.size_; ++i) {
    if(i%(N+1) == 0) a[i] = c;
    else if(i%(N+1) == 1) a[i] = -1;
    else if(i%(N+1) == N) a[i] = -1;
  }
  random_device rdev;
  mt19937 engine(rdev());
  std::uniform_real_distribution<> dist(-N*N, N*N);
  for(int i = 0; i < b.size_;) b[i++] = dist(engine);
  for(int i = 0; i < x.size_;) x[i++] = dist(engine);
  const int end = 1000;
  const double eps = 0.000001;
  const double w = 1.1;
  Vector<5>::val_t d;
  for(int i = 0; i < end; ++i) {
    x = sorMethod(x, a, b, w);
    d = norm(a*x - b);
    printf("%d ", i);
    print(d);
    if(d < eps) break;
  }
  print(x, a*x, b);
  return 0;
}