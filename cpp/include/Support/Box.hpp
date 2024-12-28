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
    Box() : impl_{new T()} {};
    template <typename U, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Box, detail::remove_cvref_t<U>>>,
                                                 std::is_constructible<T, detail::remove_cvref_t<U>>>>>
    Box(U &&obj) : impl_{new T(std::forward<U>(obj))} {}

    Box(const Box &other) : Box{*other.impl_} {}
    Box(Box &&other) : Box{std::move(*other.impl_)} {}
    Box &operator=(const Box &other) {
        *impl_ = *other.impl_;
        return *this;
    }
    Box &operator=(Box &&other) {
        *impl_ = std::move(*other.impl_);
        return *this;
    }

    ~Box() = default;

    T &operator*() & { return *impl_; }
    const T &operator*() const & { return *impl_; }
    T &&operator*() && { return std::move(*impl_); }
    const T &&operator*() const && { return std::move(*impl_); }

    T *operator->() { return impl_.get(); }
    const T *operator->() const { return impl_.get(); }

    T *get() { return impl_.get(); }
    const T *get() const { return impl_.get(); }

    friend bool operator==(const Box &a, const Box &b) { return *a.impl_ == *b.impl_; }

    friend bool operator!=(const Box &a, const Box &b) { return *a.impl_ != *b.impl_; }

    friend std::ostream &operator<<(std::ostream &out, const Box &a) { return out << *a; }

  private:
    std::unique_ptr<T> impl_;
};
}  // namespace sysyf
