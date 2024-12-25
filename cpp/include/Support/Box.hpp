#pragma once
#include <memory>
#include <ostream>
#include <type_traits>

namespace sysyf {

namespace detail {
template <typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

}  // namespace detail

// A simplified implementation of `std::indirect` in C++ 26
// basically a copyable `std::unique_ptr` with value semantics
template <typename T>
class Box {
  public:
    Box() : _impl{new T()} {};
    template <typename U, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Box, detail::remove_cvref_t<U>>>,
                                                 std::is_constructible<T, detail::remove_cvref_t<U>>>>>
    Box(U &&obj) : _impl{new T(std::forward<U>(obj))} {}

    Box(const Box &other) : Box{*other._impl} {}
    Box(Box &&other) : Box{std::move(*other._impl)} {}
    Box &operator=(const Box &other) {
        *_impl = *other._impl;
        return *this;
    }
    Box &operator=(Box &&other) {
        *_impl = std::move(*other._impl);
        return *this;
    }

    ~Box() = default;

    T &operator*() & { return *_impl; }
    const T &operator*() const & { return *_impl; }
    T &&operator*() && { return std::move(*_impl); }
    const T &&operator*() const && { return std::move(*_impl); }

    T *operator->() { return _impl.get(); }
    const T *operator->() const { return _impl.get(); }

    T *get() { return _impl.get(); }
    const T *get() const { return _impl.get(); }

    friend bool operator==(const Box &a, const Box &b) { return *a._impl == *b._impl; }

    friend bool operator!=(const Box &a, const Box &b) { return *a._impl != *b._impl; }

    friend std::ostream &operator<<(std::ostream &out, const Box &a) { return out << *a; }

  private:
    std::unique_ptr<T> _impl;
};
}  // namespace sysyf
