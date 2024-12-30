#pragma once
#include <ostream>
#include <type_traits>
#include <variant>

#include "Box.hpp"
#include "Utils.hpp"

namespace sysyf {

template <typename... Args>
class Union {
  public:
    Union() = default;
    Union(const Union &) = default;
    Union(Union &&) = default;
    Union &operator=(const Union &) = default;
    Union &operator=(Union &&) = default;
    ~Union() = default;

    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<std::variant<Args...>, T>>>>
    Union(T &&arg) : impl_(std::forward<T>(arg)) {}

    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<std::variant<Args...>, T>>>>
    Union &operator=(T &&arg) {
        impl_ = std::forward<T>(arg);
        return *this;
    }

    std::size_t index() const { return impl_.index(); }

    template <typename T>
    bool is() const {
        if constexpr ((std::is_same_v<T, Args> || ...)) {
            return std::holds_alternative<T>(impl_);
        } else if constexpr ((std::is_same_v<Box<T>, Args> || ...)) {
            return std::holds_alternative<Box<T>>(impl_);
        } else {
            static_assert(false_v<T>, "Invalid Type");
        }
    }

    template <typename T>
    const T *as() const {
        if constexpr ((std::is_same_v<T, Args> || ...)) {
            return std::get_if<T>(&impl_);
        } else if constexpr ((std::is_same_v<Box<T>, Args> || ...)) {
            const auto *ptr = std::get_if<Box<T>>(&impl_);
            if (ptr) return ptr->get();
            return nullptr;
        } else {
            static_assert(false_v<T>, "Invalid Type");
        }
    }

    template <typename T>
    T *as() {
        if constexpr ((std::is_same_v<T, Args> || ...)) {
            return std::get_if<T>(&impl_);
        } else if constexpr ((std::is_same_v<Box<T>, Args> || ...)) {
            auto *ptr = std::get_if<Box<T>>(&impl_);
            if (ptr) return ptr->get();
            return nullptr;
        } else {
            static_assert(false_v<T>, "Invalid Type");
        }
    }

    friend bool operator==(const Union &a, const Union &b) { return a.impl_ == b.impl_; }

    friend bool operator!=(const Union &a, const Union &b) { return not(a == b); }

    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<Union, remove_cvref_t<T>>>>>
    friend bool operator==(const Union &a, const T &b) {
        return a.is<T>() && *(a.as<T>()) == b;
    }
    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<Union, remove_cvref_t<T>>>>>
    friend bool operator!=(const Union &a, const T &b) {
        return not(a == b);
    }
    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<Union, remove_cvref_t<T>>>>>
    friend bool operator==(const T &a, const Union &b) {
        return b == a;
    }

    template <typename T,
              typename = std::enable_if_t<std::conjunction_v<std::negation<std::is_same<Union, remove_cvref_t<T>>>,
                                                             std::is_constructible<Union, remove_cvref_t<T>>>>>
    friend bool operator!=(const T &a, const Union &b) {
        return not(b == a);
    }

    friend std::ostream &operator<<(std::ostream &out, const Union &u) {
        return std::visit([&](const auto &v) -> std::ostream & { return out << v; }, u.impl_);
    }

  private:
    std::variant<Args...> impl_;
};
}  // namespace sysyf
