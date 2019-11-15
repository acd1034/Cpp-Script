#include <bits/stdc++.h>
using namespace std;
class fractional {
  public:
  int num;
  int denom;
  private:
  int new_num(int num, int denom=1) const {
    return num*denom/gcd(num,denom)/abs(denom);
  }
  int new_denom(int num, int denom=1) const {
    return abs(denom)/gcd(num,denom);
  }
  public:
  fractional(int num, int denom=1)
  : num(new_num(num, denom)), denom(new_denom(num, denom)) {
    cout<<"structed ";
  }
  fractional(const fractional& other)
  : num(new_num(other.num, other.denom)), denom(new_denom(other.num, other.denom)) {
    cout<<"copied ";
  }
  fractional(fractional&& other)
  : num(new_num(other.num, other.denom)), denom(new_denom(other.num, other.denom)) {
    cout<<"moved ";
    other.denom = 0; // debug
  }
  auto& operator=(const fractional& other) & {
    num = new_num(other.num, other.denom);
    denom = new_denom(other.num, other.denom);
    return *this;
  }
  auto& operator=(fractional&& other) & {
    num = new_num(other.num, other.denom);
    denom = new_denom(other.num, other.denom);
    return *this;
  }
  auto operator-() const& {
    return fractional(-num,denom);
  }
  auto operator-() && {
    auto result = move(*this);
    result.num = -result.num;
    return result;
  }
  // operator+=もlvalue reference qualifer版とrvalue reference qualifer版をかく
  auto& operator+=(const fractional& other) & {
    num = new_num(num*other.denom + other.num*denom, denom*other.denom);
    denom = new_denom(num*other.denom + other.num*denom, denom*other.denom);
    return *this;
  }
  auto operator+=(const fractional& other) && {
    auto result = move(*this);
    result.num = new_num(result.num*other.denom + other.num*result.denom, result.denom*other.denom);
    result.denom = new_denom(result.num*other.denom + other.num*result.denom, result.denom*other.denom);
    return result;
  }
  void print() const {
    cout << "(" << num << "," << denom << ") ";
  }
};
auto operator+(const fractional& left, const fractional& right) {
  return fractional(left) += right;
}
auto operator+(fractional&& left, const fractional& right) {
  auto result = move(left);
  result += right;
  return result;
}
auto operator+(const fractional& left, fractional&& right) {
  auto result = move(right);
  result += left; // 加法が可換の時のみ
  return result;
}
// overload解決のため必要
auto operator+(fractional&& x, fractional&& y) {
  return move(x) + y;
}
void print(const fractional& x) {
  x.print();
}

auto g(fractional&& x) {
  fractional y = move(x);
  return y;
}
auto f(fractional&& x) {
  fractional y = move(x);
  return g(move(y));
}
int main(){
  fractional a = f(fractional(1,2));
}

// iterator example
// auto output_all = []( auto first, auto last, auto output_iter ){
//   for ( auto iter = first ; iter != last ; ++iter, ++output_iter ){
//     *output_iter = *iter ;
//   }
// } ;
// int main(){
//   vector<int> v = {1,2,3,4,5} ;
//   output_all(
//     begin(v),
//     end(v),
//     ostream_iterator<int>(cout)
//   ) ;
//   // vector<int> source = {1,2,3,4,5} ;
//   // vector<int> destination(5) ;
//   // output_all( begin(source), end(source), begin( destination ) ) ;
// }