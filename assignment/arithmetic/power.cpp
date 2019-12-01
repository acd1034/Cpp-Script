#include <Eigen/Core>
#include <iostream>

int main() {
  Eigen::Matrix3d m;
  // m << 10, 0, 0, //
  //   0, 4, -1,    //
  //   0, 1, -1;
  m << 1, 0, 0, //
    0, 0, -1,   //
    0, -2, 0;
  Eigen::Vector3d v;
  v << 1, 1, 1;
  std::size_t i   = 0;
  double eigenval = v.transpose() * m * v;
  std::cout << i << "\t" << v.transpose() << "\t" << eigenval << std::endl;
  while (i < 50) {
    ++i;
    v        = (m * v).normalized();
    eigenval = v.transpose() * m * v;
    std::cout << i << "\t" << v.transpose() << "\t" << eigenval << "\n";
  }
}
