#include <Eigen/Core>
#include <iomanip>
#include <iostream>

int main() {
  // double const c      = 2;
  double const c      = 20;
  std::size_t const N = 10;
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
  Eigen::VectorXd y(N), r(N);
  double const w        = 1.9;
  std::size_t const end = 50;
  auto const eps        = 1e-6;
  std::cout << std::setprecision(7);
  for (std::size_t i = 0; i < end; ++i) {
    {
      r = Eigen::VectorXd::Zero(N);
      for (std::size_t i = 0; i < N; ++i) {
        y = Eigen::VectorXd::Zero(N);
        for (std::size_t j = 0; j < i; ++j) y(i) -= m(i, j) * r(j);
        for (std::size_t j = i; j < N; ++j) y(i) -= m(i, j) * x(j);
        r(i) = (1 - w) * x(i) + w * (y(i) + b(i)) / m(i, i);
      }
      x = r;
    }
    double d = (m * x - b).norm();
    std::cout << i << "\t" << d << "\n";
    if (d < eps) break;
  }
  std::cout << x << std::endl;
  return 0;
}
