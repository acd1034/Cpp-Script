#include "matrix.h"
using namespace std;
using namespace myns;

template<size_t M>
Vector<M> powerMethod(const Vector<M>& v, const Matrix<M, M>& m) {
  Vector<M> u = m*v;
  return u/norm(u);
}

int main() {
  // 1:5 2:0
  const double c = 0;
  const Matrix<3,3> a({
    1,0,0,
    0,c,-1,
    0,3,0,
  });
  Vector<3> v({1,1,1});
  const int end = 50;
  for(int i = 0; i < end; ++i) {
    v = powerMethod(v, a);
    printf("%d,", i+1);
    print(t(v)*a*v, "", ",", "");
    print(v, "", ",", "");
    printf("\n");
  }
  return 0;
}
