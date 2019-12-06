#include <bits/stdc++.h>
namespace ns {
  template <typename Itr>
  struct range : std::pair<Itr, Itr> {
    using base = std::pair<Itr, Itr>;
    range();
    range(const range&) = default;
    range(range&&)      = default;
    range(const Itr& first_, const Itr& second_) : base(first_, second_) {}
    auto begin() const { return base::first; }
    auto end() const { return base::second; }
    auto size() const { return std::distance(base::first, base::second); }
    auto empty() const { return base::first == base::second; }
  };
  template <typename R>
  auto make_range(R&& r) {
    return range<decltype(begin(std::forward<R>(r)))>(begin(std::forward<R>(r)),
                                                      end(std::forward<R>(r)));
  }
  template <typename Itr>
  auto make_range(Itr first, Itr last) {
    return range<Itr>(first, last);
  }
  template <typename Itr>
  std::ostream& operator<<(std::ostream& os, const range<Itr>& r) {
    const char* dlm = "";
    for (const auto& x : r) os << std::exchange(dlm, ",") << x;
    return os;
  }

#define XCONCAT(x1, x2) x1##x2
#define CONCAT(x1, x2) XCONCAT(x1, x2)
#define PIPELINE_NOTE0(source, target)                                         \
  namespace detail {                                                           \
    class CONCAT(target, _tag0) {                                              \
    public:                                                                    \
      CONCAT(target, _tag0)() {}                                               \
      template <typename R>                                                    \
      auto operator()(R&& r) const -> decltype(source(std::forward<R>(r))) {   \
        return source(std::forward<R>(r));                                     \
      }                                                                        \
      template <typename R>                                                    \
      auto operator()(const R& r) const -> decltype(source(r)) {               \
        return source(r);                                                      \
      }                                                                        \
    };                                                                         \
    template <typename R>                                                      \
    auto operator|(R&& r, const CONCAT(target, _tag0) & tag)                   \
      -> decltype(tag(std::forward<R>(r))) {                                   \
      return tag(std::forward<R>(r));                                          \
    }                                                                          \
    template <typename R>                                                      \
    auto operator|(const R& r, const CONCAT(target, _tag0) & tag)              \
      -> decltype(tag(r)) {                                                    \
      return tag(r);                                                           \
    }                                                                          \
  }                                                                            \
  auto target() { return detail::CONCAT(target, _tag0)(); }

#define PIPELINE_NOTE1(source, target)                                         \
  namespace detail {                                                           \
    template <typename T1>                                                     \
    class CONCAT(target, _tag1) {                                              \
      T1 x1;                                                                   \
                                                                               \
    public:                                                                    \
      CONCAT(target, _tag1)(const T1& x1_) : x1(x1_) {}                        \
      template <typename R>                                                    \
      auto operator()(R&& r) const                                             \
        -> decltype(source(std::forward<R>(r), x1)) {                          \
        return source(std::forward<R>(r), x1);                                 \
      }                                                                        \
      template <typename R>                                                    \
      auto operator()(const R& r) const -> decltype(source(r, x1)) {           \
        return source(r, x1);                                                  \
      }                                                                        \
    };                                                                         \
    template <typename R, typename T1>                                         \
    auto operator|(R&& r, const CONCAT(target, _tag1) < T1 > &tag)             \
      -> decltype(tag(std::forward<R>(r))) {                                   \
      return tag(std::forward<R>(r));                                          \
    }                                                                          \
    template <typename R, typename T1>                                         \
    auto operator|(const R& r, const CONCAT(target, _tag1) < T1 > &tag)        \
      -> decltype(tag(r)) {                                                    \
      return tag(r);                                                           \
    }                                                                          \
  }                                                                            \
  template <typename T1>                                                       \
  auto target(const T1& x1) {                                                  \
    return detail::CONCAT(target, _tag1)<T1>(x1);                              \
  }

#define PIPELINE_NOTE2(source, target)                                         \
  namespace detail {                                                           \
    template <typename T1, typename T2>                                        \
    class CONCAT(target, _tag2) {                                              \
      T1 x1;                                                                   \
      T2 x2;                                                                   \
                                                                               \
    public:                                                                    \
      CONCAT(target, _tag2)                                                    \
      (const T1& x1_, const T2& x2_) : x1(x1_), x2(x2_) {}                     \
      template <typename R>                                                    \
      auto operator()(R&& r) const                                             \
        -> decltype(source(std::forward<R>(r), x1, x2)) {                      \
        return source(std::forward<R>(r), x1, x2);                             \
      }                                                                        \
      template <typename R>                                                    \
      auto operator()(const R& r) const -> decltype(source(r, x1, x2)) {       \
        return source(r, x1, x2);                                              \
      }                                                                        \
    };                                                                         \
    template <typename R, typename T1, typename T2>                            \
    auto operator|(R&& r, const CONCAT(target, _tag2) < T1, T2 > &tag)         \
      -> decltype(tag(std::forward<R>(r))) {                                   \
      return tag(std::forward<R>(r));                                          \
    }                                                                          \
    template <typename R, typename T1, typename T2>                            \
    auto operator|(const R& r, const CONCAT(target, _tag2) < T1, T2 > &tag)    \
      -> decltype(tag(r)) {                                                    \
      return tag(r);                                                           \
    }                                                                          \
  }                                                                            \
  template <typename T1, typename T2>                                          \
  auto target(const T1& x1, const T2& x2) {                                    \
    return detail::CONCAT(target, _tag2)<T1, T2>(x1, x2);                      \
  }

#define PIPELINE_NOTE3(source, target)                                         \
  namespace detail {                                                           \
    template <typename T1, typename T2, typename T3>                           \
    class CONCAT(target, _tag3) {                                              \
      T1 x1;                                                                   \
      T2 x2;                                                                   \
      T3 x3;                                                                   \
                                                                               \
    public:                                                                    \
      CONCAT(target, _tag3)                                                    \
      (const T1& x1_, const T2& x2_, const T3& x3_)                            \
        : x1(x1_), x2(x2_), x3(x3_) {}                                         \
      template <typename R>                                                    \
      auto operator()(R&& r) const                                             \
        -> decltype(source(std::forward<R>(r), x1, x2, x3)) {                  \
        return source(std::forward<R>(r), x1, x2, x3);                         \
      }                                                                        \
      template <typename R>                                                    \
      auto operator()(const R& r) const -> decltype(source(r, x1, x2, x3)) {   \
        return source(r, x1, x2, x3);                                          \
      }                                                                        \
    };                                                                         \
    template <typename R, typename T1, typename T2, typename T3>               \
    auto operator|(R&& r, const CONCAT(target, _tag3) < T1, T2, T3 > &tag)     \
      -> decltype(tag(std::forward<R>(r))) {                                   \
      return tag(std::forward<R>(r));                                          \
    }                                                                          \
    template <typename R, typename T1, typename T2, typename T3>               \
    auto                                                                       \
    operator|(const R& r, const CONCAT(target, _tag3) < T1, T2, T3 > &tag)     \
      -> decltype(tag(r)) {                                                    \
      return tag(r);                                                           \
    }                                                                          \
  }                                                                            \
  template <typename T1, typename T2, typename T3>                             \
  auto target(const T1& x1, const T2& x2, const T3& x3) {                      \
    return detail::CONCAT(target, _tag3)<T1, T2, T3>(x1, x2, x3);              \
  }

#define PIPELINE_NOTE_RNGRF0(source, target)                                   \
  namespace detail {                                                           \
    template <typename R>                                                      \
    auto target(R& r) -> decltype(r) {                                         \
      source(begin(r), end(r));                                                \
      return r;                                                                \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE0(detail::target, target)
#define PIPELINE_NOTE_RNGRF1(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename T1>                                         \
    auto target(R& r, T1 x1) -> decltype(r) {                                  \
      source(begin(r), end(r), x1);                                            \
      return r;                                                                \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE1(detail::target, target)
#define PIPELINE_NOTE_FRWRD1(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename T1>                                         \
    auto target(R& r, T1 x1) {                                                 \
      return source(begin(r), end(r), x1);                                     \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE1(detail::target, target)
#define PIPELINE_NOTE_FRWRD2(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename T1, typename T2>                            \
    auto target(R& r, T1 x1, T2 x2) {                                          \
      return source(begin(r), end(r), x1, x2);                                 \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE2(detail::target, target)
#define PIPELINE_NOTE_MKRNG0(source, target)                                   \
  namespace detail {                                                           \
    template <typename R>                                                      \
    auto target(R& r) {                                                        \
      return make_range(begin(r), source(begin(r), end(r)));                   \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE0(detail::target, target)
#define PIPELINE_NOTE_MKRNG1(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename T1>                                         \
    auto target(R& r, T1 x1) {                                                 \
      return make_range(begin(r), source(begin(r), end(r), x1));               \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE1(detail::target, target)
#define PIPELINE_NOTE_IPRNG1(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename T1>                                         \
    auto target(R& r, T1 x1) -> decltype(r) {                                  \
      source(begin(r), end(r), begin(r), x1);                                  \
      return r;                                                                \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE1(detail::target, target)
#define PIPELINE_NOTE_OPRNG1(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename O>                                          \
    auto target(R& r, O& out) -> decltype(out) {                               \
      source(begin(r), end(r), begin(out));                                    \
      return out;                                                              \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE1(detail::target, target)
#define PIPELINE_NOTE_OPRNG2(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename O, typename T1>                             \
    auto target(R& r, O& out, T1 x1) -> decltype(out) {                        \
      source(begin(r), end(r), begin(out), x1);                                \
      return out;                                                              \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE2(detail::target, target)
#define PIPELINE_NOTE_IORNG3(source, target)                                   \
  namespace detail {                                                           \
    template <typename R, typename I, typename O, typename T1>                 \
    auto target(R& r, I& in, O& out, T1 x1) -> decltype(out) {                 \
      source(begin(r), end(r), begin(in), begin(out), x1);                     \
      return out;                                                              \
    }                                                                          \
  }                                                                            \
  PIPELINE_NOTE3(detail::target, target)
} // namespace ns
