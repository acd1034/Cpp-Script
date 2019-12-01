#include <Eigen/Core>
#include <iostream>

int main() {
  // double const c      = 2;
  double const c      = 20;
  std::size_t const N = 100;
  Eigen::MatrixXd m(N, N);
  {
    Eigen::MatrixXd m1 = Eigen::MatrixXd::Zero(N, N), m2 = Eigen::MatrixXd::Zero(N, N);
    m1.bottomLeftCorner(N - 1, N - 1).setIdentity();
    m2.topRightCorner(N - 1, N - 1).setIdentity();
    m = c * Eigen::MatrixXd::Identity(N, N) - m1 - m2;
  }
  Eigen::VectorXd b(N), x(N);
  for (std::size_t i = 0; i < N; ++i) b(i) = 1;
  for (std::size_t i = 0; i < N; ++i) x(i) = i;
  Eigen::VectorXd r = b - m * x, p = r;
  std::size_t const end = 1000;
  auto const eps        = 1e-6;
  for (std::size_t i = 0; i < end; ++i) {
    {
      Eigen::VectorXd q = m * p;
      double c          = p.dot(q);
      double d          = r.dot(p) / c;
      x += d * p;
      r -= d * q;
      p = r - r.dot(q) / c * p;
    }
    std::cout << i << "\t" << r.norm() << "\n";
    if (r.norm() < eps) break;
  }
  std::cout << x << std::endl;
  return 0;
}
