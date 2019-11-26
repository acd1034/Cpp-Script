#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <initializer_list>

namespace myns {
template<std::size_t M, std::size_t N>
class Matrix {
  public:
  using ths_t = Matrix<M, N>;
  using val_t = double;
  using size_t = std::size_t;
  const char* fmt_ = "%lf";
  const size_t size_ = M*N;
  val_t instance_[M*N] __attribute__((__aligned__));
  Matrix() : instance_() {
    memset(instance_, 0, sizeof instance_);
  }
  explicit Matrix(std::initializer_list<val_t> init) : instance_() {
    assert(init.size() == size_);
    auto i = init.begin();
    for(int j = 0; j < size_;) instance_[j++] = *(i++);
  }
  Matrix(const ths_t& m) : instance_() {
    memcpy(instance_, m.instance_, sizeof instance_);
  }
  ths_t& operator=(const ths_t& m) {
    memcpy(instance_, m.instance_, sizeof instance_);
    return *this;
  }
  val_t& operator[](const size_t i) {
    return instance_[i];
  }
  const val_t& operator[](const size_t i) const {
    return instance_[i];
  }
  val_t& operator()(const size_t i, const size_t j = 0) {
    return instance_[N*i+j];
  }
  const val_t& operator()(const size_t i, const size_t j = 0) const {
    return instance_[N*i+j];
  }
  void fill(val_t c) {
    for(int i = 0; i < size_;) instance_[i++] = c;
  }
};
template<std::size_t M>
using Vector = Matrix<M, 1>;
#define DEFINE_MATRIX_UNARY_OPERATOR(Op) \
template<std::size_t M, std::size_t N> \
inline Matrix<M, N> operator Op(const Matrix<M, N>& m) { \
  Matrix<M, N> ret; \
  for(int i = 0; i < m.size_; ++i) ret[i] = Op m[i]; \
  return ret; \
}
DEFINE_MATRIX_UNARY_OPERATOR(-)
#undef DEFINE_MATRIX_UNARY_OPERATOR
#define DEFINE_MATRIX_BINARY_OPERATOR(Op) \
template<std::size_t M, std::size_t N> \
inline Matrix<M, N> \
operator Op(const Matrix<M, N>& m1, const Matrix<M, N>& m2) { \
  Matrix<M, N> ret; \
  for(int i = 0; i < m1.size_; ++i) ret[i] = m1[i] Op m2[i]; \
  return ret; \
}
DEFINE_MATRIX_BINARY_OPERATOR(+)
DEFINE_MATRIX_BINARY_OPERATOR(-)
#undef DEFINE_MATRIX_BINARY_OPERATOR
#define DEFINE_MATRIX_LEFT_SCALAR_OPERATOR(Op) \
template<std::size_t M, std::size_t N> \
inline Matrix<M, N> \
operator Op( \
  const typename Matrix<M, N>::val_t c, \
  const Matrix<M, N>& m \
) { \
  Matrix<M, N> ret; \
  for(int i = 0; i < m.size_; ++i) ret[i] = c Op m[i]; \
  return ret; \
}
DEFINE_MATRIX_LEFT_SCALAR_OPERATOR(*)
#undef DEFINE_MATRIX_LEFT_SCALAR_OPERATOR
#define DEFINE_MATRIX_RIGHT_SCALAR_OPERATOR(Op) \
template<std::size_t M, std::size_t N> \
inline Matrix<M, N> \
operator Op( \
  const Matrix<M, N>& m, \
  const typename Matrix<M, N>::val_t c \
) { \
  Matrix<M, N> ret; \
  for(int i = 0; i < m.size_; ++i) ret[i] = m[i] Op c; \
  return ret; \
}
DEFINE_MATRIX_RIGHT_SCALAR_OPERATOR(*)
DEFINE_MATRIX_RIGHT_SCALAR_OPERATOR(/)
#undef DEFINE_MATRIX_RIGHT_SCALAR_OPERATOR
template<std::size_t L, std::size_t M, std::size_t N>
inline Matrix<L, N>
operator*(const Matrix<L, M>& m1, const Matrix<M, N>& m2) {
  Matrix<L, N> ret;
  int i, k, j;
  for(i = 0; i < L; ++i) {
    for(k = 0; k < N; ++k) {
      for(j = 0; j < M; ++j) ret(i, k) += m1(i, j) * m2(j, k);
    }
  }
  return ret;
}
template<std::size_t M>
inline typename Vector<M>::val_t
operator*(const Matrix<1, M>& m, const Vector<M>& v) {
  typename Vector<M>::val_t ret = 0;
  for(int i = 0; i < v.size_; ++i) ret += m[i] * v[i];
  return ret;
}
template<std::size_t M, std::size_t N>
inline Matrix<N, M> t(const Matrix<M, N>& m) {
  Matrix<N, M> ret;
  int i, j;
  for(i = 0; i < M; ++i) {
    for(j = 0; j < N; ++j) ret(j, i) = m(i, j);
  }
  return ret;
}
template<std::size_t M, std::size_t N>
inline typename Matrix<M, N>::val_t
norm(const Matrix<M, N>& m) {
  typename Matrix<M, N>::val_t ret = 0;
  for(int i = 0; i < m.size_; ++i) ret += m[i] * m[i];
  return sqrt(ret);
}
template<std::size_t M, std::size_t N>
void print(
  const Matrix<M, N>& m,
  const char* dlm = " ",
  const char* end = "]\n",
  const char* begin = "["
) {
  printf("%s", begin);
  for(int i = 0;;) {
    printf(m.fmt_, m[i++]);
    if(i%N == 0) {
      printf("%s", end);
      if(i == m.size_) break;
      else printf("%s", begin);
    } else {
      printf("%s", dlm);
    }
  }
}
void print(
  const typename Matrix<1, 1>::val_t c,
  const char* dlm = "",
  const char* end = "\n",
  const char* begin = ""
) {
  print(Matrix<1, 1>({c}), dlm, end, begin);
}
template<std::size_t M, std::size_t N, class... Tail>
void print(const Matrix<M, N>& m, Tail&&... tail) {
  print(m);
  printf("\n");
  print(std::forward<Tail>(tail)...);
}
template<class... Tail>
void print(const typename Matrix<1, 1>::val_t c, Tail&&... tail) {
  print(Matrix<1, 1>({c}), "", "\n", "");
  printf("\n");
  print(std::forward<Tail>(tail)...);
}
}