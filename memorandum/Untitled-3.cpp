#include "Untitled-4.cpp"
namespace std {
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    const char* dlm = "";
    for (const auto& x : v) os << std::exchange(dlm, ",") << x;
    return os;
  }
} // namespace std
namespace ns {
  // others
  namespace detail {
    template <typename R, typename T1>
    auto taken(R& r, T1 x1) {
      return make_range(begin(r), std::next(begin(r), x1));
    }
    template <typename R, typename T1>
    auto dropped(R& r, T1 x1) {
      return make_range(std::next(begin(r), x1), end(r));
    }
    template <typename R, typename T1>
    auto erase_ifed(R& r, T1 x1) -> decltype(r) {
      r.erase(remove_if(begin(r), end(r), x1), end(r));
      return r;
    }
  } // namespace detail
  PIPELINE_NOTE1(detail::taken, taken)
  PIPELINE_NOTE1(detail::dropped, dropped)
  PIPELINE_NOTE1(detail::erase_ifed, erase_ifed)
  // algorithm
  PIPELINE_NOTE_RNGRF1(std::for_each, for_eached)
  PIPELINE_NOTE_OPRNG1(std::copy, copied)
  PIPELINE_NOTE_RNGRF1(std::fill, filled)
  PIPELINE_NOTE_IPRNG1(std::transform, transformed)
  PIPELINE_NOTE_OPRNG2(std::transform, transformed)
  PIPELINE_NOTE_IORNG3(std::transform, transformed)
  // PIPELINE_NOTE_MKRNG1(std::remove_if,remove_ifed)
  // PIPELINE_NOTE_MKRNG0(std::unique,uniqued)
  // PIPELINE_NOTE_MKRNG1(std::unique,uniqued)
  // PIPELINE_NOTE_MKRNG1(std::partition,partitioned)
  PIPELINE_NOTE_MKRNG1(std::stable_partition, stable_partitioned)
  // PIPELINE_NOTE_RNGRF0(std::sort,sorted)
  // PIPELINE_NOTE_RNGRF1(std::sort,sorted)
  // numeric
  PIPELINE_NOTE_RNGRF1(std::iota, ioted)
  PIPELINE_NOTE_FRWRD1(std::accumulate, accumulated)
  PIPELINE_NOTE_FRWRD2(std::accumulate, accumulated)
  PIPELINE_NOTE_OPRNG1(std::adjacent_difference, adjacent_differenced)
  PIPELINE_NOTE_OPRNG2(std::adjacent_difference, adjacent_differenced)
  PIPELINE_NOTE_OPRNG1(std::partial_sum, partial_sumed)
  PIPELINE_NOTE_OPRNG2(std::partial_sum, partial_sumed)
} // namespace ns
int32_t main() {
  using std::cout;
  size_t n = 20;
  std::vector<size_t> u(n), v(n);
  cout << (ns::make_range(begin(u), std::prev(end(u))) | ns::ioted(1)
           | ns::transformed([](auto x) { return x * x; }))
       << std::endl;
}
