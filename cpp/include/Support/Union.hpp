#pragma once
#include <ostream>
#include <type_traits>
#include <variant>

#include "Box.hpp"

namespace sysyf {
namespace detail {

template <typename T, typename... Args>
constexpr bool is_unique_type_list() {
    if constexpr (sizeof...(Args) == 0)
        return true;
    else if constexpr ((std::is_same_v<T, Args> || ...))
        return false;
    else
        return is_unique_type_list<Args...>();
}
}  // namespace detail

template <typename... Args>
class Union : public std::variant<Args...> {
  public:
    using std::variant<Args...>::variant;
    using std::variant<Args...>::operator=;
    using std::variant<Args...>::emplace;
    using std::variant<Args...>::swap;
    using std::variant<Args...>::index;

    Union() = default;
    Union(const Union &) = default;
    Union(Union &&) = default;
    Union &operator=(const Union &) = default;
    Union &operator=(Union &&) = default;
    ~Union() = default;

    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(*this);
    }

    template <typename T>
    const T *as() const {
        return std::get_if<T>(this);
    }

    template <typename T>
    T *as() {
        return std::get_if<T>(this);
    }

    friend bool operator==(const Union &a, const Union &b) {
        return static_cast<const std::variant<Args...> &>(a) == static_cast<const std::variant<Args...> &>(b);
    }

    friend bool operator!=(const Union &a, const Union &b) { return not(a == b); }

    template <typename T, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Union, detail::remove_cvref_t<T>>>,
                                                 std::is_constructible<Union, detail::remove_cvref_t<T>>>>>
    friend bool operator==(const Union &a, const T &b) {
        return a.is<T>() && *(a.as<T>()) == b;
    }
    template <typename T, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Union, detail::remove_cvref_t<T>>>,
                                                 std::is_constructible<Union, detail::remove_cvref_t<T>>>>>
    friend bool operator!=(const Union &a, const T &b) {
        return not(a == b);
    }
    template <typename T, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Union, detail::remove_cvref_t<T>>>,
                                                 std::is_constructible<Union, detail::remove_cvref_t<T>>>>>
    friend bool operator==(const T &a, const Union &b) {
        return b == a;
    }
    template <typename T, typename = std::enable_if_t<
                              std::conjunction_v<std::negation<std::is_same<Union, detail::remove_cvref_t<T>>>,
                                                 std::is_constructible<Union, detail::remove_cvref_t<T>>>>>
    friend bool operator!=(const T &a, const Union &b) {
        return not(b == a);
    }

    friend std::ostream &operator<<(std::ostream &out, const Union &u) {
        return std::visit([&](const auto &v) -> std::ostream & { return out << v; }, u);
    }
};
}  // namespace sysyf
