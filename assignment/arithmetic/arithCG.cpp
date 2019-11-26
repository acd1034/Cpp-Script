#include "matrix.cpp"
#include <random>
using namespace std;
using namespace myns;

template<size_t M>
Vector<M> conjugateGradientMethod(
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
  Vector<N> r = b - a*x;
  Vector<N> p = r;
  const int end = 1000;
  const double eps = 0.000001;
  for(int i = 0; i < end; ++i) {
    x = conjugateGradientMethod(x, a, r, p);
    printf("%d ", i);
    print(norm(r));
    if(norm(r) < eps) break;
  }
  print(x, a*x, b);
  return 0;
}
