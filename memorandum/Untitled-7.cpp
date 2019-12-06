#include <iostream>
#include <list>
#include <vector>
namespace ns {
  template <typename Func>
  struct scope_exit {
  private:
    Func f;

  public:
    explicit scope_exit(Func const& f) noexcept : f(f) {}
    explicit scope_exit(Func&& f) noexcept : f(std::move(f)) {}
    scope_exit(scope_exit const&) = delete;
    scope_exit(scope_exit&&)      = delete;
    void operator=(scope_exit const&) = delete;
    void operator=(scope_exit&&) = delete;
    ~scope_exit() { f(); }
  };
  template <typename Func>
  auto make_scope_exit(Func const& f) {
    return scope_exit<Func>(f);
  }
  template <typename Func>
  auto make_scope_exit(Func&& f) {
    return scope_exit<Func>(std::move(f));
  }

#define DEFINE_ITERATOR_COMPARE(ItrT)                                          \
  template <typename Vector>                                                   \
  bool operator>(ItrT<Vector> const& x, ItrT<Vector> const& y) {               \
    return y < x;                                                              \
  }                                                                            \
  template <typename Vector>                                                   \
  bool operator<=(ItrT<Vector> const& x, ItrT<Vector> const& y) {              \
    return !(x > y);                                                           \
  }                                                                            \
  template <typename Vector>                                                   \
  bool operator>=(ItrT<Vector> const& x, ItrT<Vector> const& y) {              \
    return !(x < y);                                                           \
  }                                                                            \
  template <typename Vector>                                                   \
  bool operator!=(ItrT<Vector> const& x, ItrT<Vector> const& y) {              \
    return (x < y) || (x > y);                                                 \
  }                                                                            \
  template <typename Vector>                                                   \
  bool operator==(ItrT<Vector> const& x, ItrT<Vector> const& y) {              \
    return !(x != y);                                                          \
  }
  template <typename Vector>
  struct vector_iterator {
    using container_type = Vector;
    using reference      = typename container_type::reference;
    using pointer        = typename container_type::pointer;
    using size_type      = typename container_type::size_type;

    pointer ptr;
    explicit vector_iterator(pointer ptr) : ptr(ptr) {}
    reference operator*() { return *ptr; }
    vector_iterator& operator++() {
      ++ptr;
      return *this;
    }
    vector_iterator operator++(int) {
      vector_iterator copy = *this;
      ++*this;
      return copy;
    }
    reference operator[](size_type i) { return ptr[i]; }
  }; // struct vector_iterator
  template <typename Vector>
  bool operator<(vector_iterator<Vector> const& x,
                 vector_iterator<Vector> const& y) {
    return x.ptr < y.ptr;
  }
  DEFINE_ITERATOR_COMPARE(vector_iterator)

  template <typename Vector>
  struct vector_const_iterator {
    using container_type = Vector const;
    using reference      = typename container_type::const_reference;
    using pointer        = typename container_type::const_pointer;
    using size_type      = typename container_type::size_type;

    pointer ptr;
    explicit vector_const_iterator(pointer ptr) : ptr(ptr) {}
    vector_const_iterator(vector_iterator<Vector> itr) : ptr(itr.ptr) {}
    reference operator*() const { return *ptr; }
    vector_const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    vector_const_iterator operator++(int) {
      vector_const_iterator copy = *this;
      ++*this;
      return copy;
    }
    reference operator[](size_type i) const { return ptr[i]; }
  }; // struct vector_const_iterator
  template <typename Vector>
  bool operator<(vector_const_iterator<Vector> const& x,
                 vector_const_iterator<Vector> const& y) {
    return x.ptr < y.ptr;
  }
  DEFINE_ITERATOR_COMPARE(vector_const_iterator)
#undef DEFINE_ITERATOR_COMPARE

  template <typename T, typename Allocator = std::allocator<T>>
  struct vector {
    using value_type             = T;
    using allocator_type         = Allocator;
    using reference              = value_type&;
    using const_reference        = value_type const&;
    using pointer                = value_type*;
    using const_pointer          = value_type const*;
    using iterator               = vector_iterator<vector>;
    using const_iterator         = vector_const_iterator<vector>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;

  private:
    pointer first;
    pointer last;
    pointer reserved_last;
    allocator_type alloc;
    using traits = std::allocator_traits<allocator_type>;
    pointer allocate(size_type n) { return traits::allocate(alloc, n); }
    void deallocate() { traits::deallocate(alloc, first, capacity()); }
    void construct(pointer ptr) { traits::construct(alloc, ptr); }
    void construct(pointer ptr, const_reference value) {
      traits::construct(alloc, ptr, value);
    }
    void construct(pointer ptr, value_type&& value) {
      traits::construct(alloc, ptr, std::move(value));
    }
    void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
    void destroy_until(reverse_iterator rend) {
      for (auto i = rbegin(); i != rend; ++i, --last) {
        destroy(std::addressof(*i));
      }
    }

  public:
    explicit vector(allocator_type const& alloc = allocator_type()) noexcept
      : first(nullptr), last(nullptr), reserved_last(nullptr), alloc(alloc) {}
    vector(size_type n, allocator_type const& alloc = allocator_type())
      : vector(alloc) {
      resize(n);
    }
    vector(size_type n,
           const_reference value,
           allocator_type const& alloc = allocator_type())
      : vector(alloc) {}
    ~vector() {
      clear();
      deallocate();
    }

    iterator begin() noexcept { return iterator{first}; }
    const_iterator begin() const noexcept { return const_iterator{first}; }
    iterator end() noexcept { return iterator{last}; }
    const_iterator end() const noexcept { return const_iterator{last}; }
    const_iterator cbegin() const noexcept { return const_iterator{first}; }
    const_iterator cend() const noexcept { return const_iterator{last}; }
    iterator rbegin() noexcept { return reverse_iterator{last}; }
    const_iterator rbegin() const noexcept {
      return const_reverse_iterator{last};
    }
    iterator rend() noexcept { return reverse_iterator{first}; }
    const_iterator rend() const noexcept {
      return const_reverse_iterator{first};
    }
    const_iterator crbegin() const noexcept {
      return const_reverse_iterator{last};
    }
    const_iterator crend() const noexcept {
      return const_reverse_iterator{first};
    }

    reference operator[](size_type i) { return first[i]; }
    const_reference operator[](size_type i) const { return first[i]; }
    reference at(size_type i) {
      if (i >= size()) throw std::out_of_range("ns::vector: std::out_of_range");
      return first[i];
    }
    const_reference at(size_type i) const {
      if (i >= size()) throw std::out_of_range("ns::vector: std::out_of_range");
      return first[i];
    }

    size_type size() const noexcept { return last - first; }
    bool empty() const noexcept { return begin() == end(); }
    size_type capacity() const noexcept { return reserved_last - first; }
    void clear() noexcept { destroy_until(rend()); }
    void reserve(size_type n) {
      if (n <= capacity()) return;
    }
    void resize() {}
  }; // struct vector
} // namespace ns

int32_t main() {
  std::list<int> l{1, 2};
  std::rbegin(l).operator[](1); // compile error!
  std::vector<int> v{1, 2};
  std::rbegin(v).operator[](1);
}
// int object{};
// int* pointer = &object;
// *pointer = 0;// 書き込み
// int read = *pointer;// 読み込み
// int* pointer2 = pointer;
