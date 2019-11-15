#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <map>
#include <queue>
#include <stack>
#include <vector>
namespace ns{
template<typename Array>
class array_iterator{
  public:
  // usingする？
  Array& a;
  std::size_t i;
  array_iterator(Array& a, std::size_t i)
    :a(a), i(i){}
  // 自分自身を変更するならメンバ、しないならグローバル？（違う！）
  typename Array::reference operator[](std::size_t n) const {
    return *(*this + n);
  }
  typename Array::reference operator*(){
    return a[i];
  }
  array_iterator& operator++(){
    ++i;
    return *this;
  }
  array_iterator operator++(int){
    array_iterator before = *this;
    ++*this;
    return before;
  }
  // operator--
  // operator--(int)
  array_iterator& operator+=(std::size_t n){
    i+=n;
    return *this;
  }
  // operator-=
};
template<typename Array>
array_iterator<Array> operator+(const array_iterator<Array>& left, std::size_t right){
  return array_iterator<Array>(left) += right;
}
template<typename Array>
bool operator<(const array_iterator<Array>& left, const array_iterator<Array>& right){
  return left.i < right.i;
}
template<typename Array>
bool operator>(const array_iterator<Array>& left, const array_iterator<Array>& right){
  return right.i < left.i;
}
// operator<=
// operator>=
template<typename Array>
bool operator==(const array_iterator<Array>& left, const array_iterator<Array>& right){
  return !(left != right);
}
template<typename Array>
bool operator!=(const array_iterator<Array>& left, const array_iterator<Array>& right){
  return left < right || left > right;
}
template<typename Array>
class array_const_iterator{
  public:
  // usingする？
  const Array& a;
  std::size_t i;
  array_const_iterator(const Array& a, std::size_t i)
    :a(a), i(i){}
  // array_iteratorからの変換コンストラクター
  array_const_iterator(const array_iterator<Array>& itr)
    :a(itr.a), i(itr.i){}
  // 自分自身を変更するならメンバ、しないならグローバル？（違う！）
  typename Array::const_reference operator[](std::size_t n) const {
    return *(*this + n);
  }
  typename Array::const_reference operator*() const {
    return a[i];
  }
  array_const_iterator& operator++(){
    ++i;
    return *this;
  }
  array_const_iterator operator++(int){
    array_const_iterator before = *this;
    ++*this;
    return before;
  }
  // operator--
  // operator--(int)
  array_const_iterator& operator+=(std::size_t n){
    i+=n;
    return *this;
  }
  // operator-=
};
template<typename Array>
array_const_iterator<Array> operator+(const array_const_iterator<Array>& left, std::size_t right){
  return array_const_iterator<Array>(left) += right;
}
template<typename Array>
bool operator<(const array_const_iterator<Array>& left, const array_const_iterator<Array>& right){
  return left.i < right.i;
}
template<typename Array>
bool operator>(const array_const_iterator<Array>& left, const array_const_iterator<Array>& right){
  return right < left;
}
// operator<=
// operator>=
template<typename Array>
bool operator==(const array_const_iterator<Array>& left, const array_const_iterator<Array>& right){
  return !(left != right);
}
template<typename Array>
bool operator!=(const array_const_iterator<Array>& left, const array_const_iterator<Array>& right){
  return left < right || left > right;
}
template<typename T, std::size_t N>
class array{
  public:
  using self = array; // クラステンプレート内でarrayはarray<T, N>と同じ
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  value_type storage[N];
  // referenceでなくautoでもいいんじゃない（適当）
  reference operator[](size_type i){
    return storage[i];
  }
  const_reference operator[](size_type i) const {
    return storage[i];
  }
  size_type size() const {
    return N;
  }
  // iterator
  // TODO:この実装がbestか？
  using iterator = array_iterator<self>;
  using const_iterator = array_const_iterator<self>;
  iterator begin(){
    return iterator(*this, 0);
  }
  iterator end(){
    return iterator(*this, N);
  }
  const_iterator begin() const {
    return const_iterator(*this, 0);
  }
  const_iterator end() const {
    return const_iterator(*this, N);
  }
  const_iterator cbegin() const {
    return const_iterator(*this, 0);
  }
  const_iterator cend() const {
    return const_iterator(*this, N);
  }
};
}

int main(){
  using namespace std;
  ns::array<int,3> a;
  a[0]=1;a[1]=2;a[2]=3;
  cout<<*(cbegin(a)+2)<<"\n"s;
  cout<<cbegin(a)[2]<<"\n"s;

  // ns::array<int,3> a;
  // ns::array<int,3> b;
  // ns::array<int,4> c;
  // cout<<(begin(a)==begin(b)); // falseになった
  // cout<<(begin(a)==begin(c)); // Compile Error!
}