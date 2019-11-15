#include <iostream>
#include <array>
namespace ns{
#define DEFINE_ITERATOR_COMPARE(ItrT)\
template<typename Array>\
bool operator>(ItrT<Array> const& x, ItrT<Array> const& y){ return y < x; }\
template<typename Array>\
bool operator<=(ItrT<Array> const& x, ItrT<Array> const& y){ return !(x > y); }\
template<typename Array>\
bool operator>=(ItrT<Array> const& x, ItrT<Array> const& y){ return !(x < y); }\
template<typename Array>\
bool operator!=(ItrT<Array> const& x, ItrT<Array> const& y){ return (x < y) || (x > y); }\
template<typename Array>\
bool operator==(ItrT<Array> const& x, ItrT<Array> const& y){ return !(x != y); }
#define DEFINE_ITERATOR_CREMENT(ItrT, Op)\
ItrT& operator Op(){ Op(i); return *this; }\
ItrT operator Op(int){\
  auto copy=*this; Op(*this); return copy;\
}

template<typename Array>
struct array_iterator{
  using container_t = Array;
  using reference = typename container_t::reference;
  using size_t = std::size_t;

  container_t& a;
  size_t i;
  array_iterator(container_t& a, size_t i): a(a), i(i) {}
  DEFINE_ITERATOR_CREMENT(array_iterator, ++)
  DEFINE_ITERATOR_CREMENT(array_iterator, --)
  reference operator*(){ return a[i]; }
}; // struct array_iterator
template<typename Array>
bool operator<(array_iterator<Array> const& x, array_iterator<Array> const& y){ return x.i<y.i; }
DEFINE_ITERATOR_COMPARE(array_iterator)

template<typename Array>
struct array_const_iterator{
  using container_t = Array const;
  using reference = typename container_t::const_reference;
  using size_t = std::size_t;

  container_t& a;
  size_t i;
  array_const_iterator(container_t& a, size_t i): a(a), i(i) {}
  array_const_iterator(typename container_t::iterator const& itr): a(itr.a), i(itr.i) {}
  DEFINE_ITERATOR_CREMENT(array_const_iterator, ++)
  DEFINE_ITERATOR_CREMENT(array_const_iterator, --)
  reference operator*() const { return a[i]; }
}; // struct array_const_iterator
template<typename Array>
bool operator<(array_const_iterator<Array> const& x, array_const_iterator<Array> const& y){ return x.i<y.i; }
DEFINE_ITERATOR_COMPARE(array_const_iterator)

template<typename T, std::size_t N>
struct array{
  using value_t = T;
  using reference = value_t&;
  using const_reference = value_t const&;
  using iterator = array_iterator<array>;
  using const_iterator = array_const_iterator<array>;
  using size_t = std::size_t;

  value_t instance[N];
  reference operator[](size_t i){ return instance[i]; }
  const_reference operator[](size_t i) const { return instance[i]; }
  reference at(size_t i){
    if(i>=size()) throw std::out_of_range("array: std::out_of_range");
    return instance[i];
  }
  const_reference at(size_t i) const {
    if(i>=size()) throw std::out_of_range("array: std::out_of_range");
    return instance[i];
  }
  size_t size() const { return N; }
  iterator begin(){ return iterator(*this, 0); }
  const_iterator begin() const { return const_iterator(*this, 0); }
  iterator end(){ return iterator(*this, N); }
  const_iterator end() const { return const_iterator(*this, N); }
  const_iterator cbegin() const { return const_iterator(*this, 0); }
  const_iterator cend() const { return const_iterator(*this, N); }
}; // struct array
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, array<T, N> const& xs){
  const char* dlm="";
  for(auto const& x:xs){ os<<std::exchange(dlm, " ")<<x; }
  return os;
}
} // namespace ns

int32_t main(){
  using std::cout, std::begin, std::end;
  {
    ns::array<int32_t,5> a={1,2,3,4,5};
    cout<<*++++++begin(a);
    // for(size_t i=0; i<6; ++i){
    //   try{ cout<<a.at(i); }
    //   catch(...){ cout<<e.what()<<'\n'; }
    // }
  }
}
