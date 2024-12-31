#pragma once
#include <iterator>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::unique_ptr<T> &ptr) {
    if (ptr) return out << *ptr;
    return out << "(nullptr)";
}

namespace sysyf {

[[noreturn]] inline void unreachable() {
#if defined(_MSC_VER) && !defined(__clang__)  // MSVC
    __assume(false);
#else  // GCC, Clang
    __builtin_unreachable();
#endif
}

template <typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T>
constexpr bool false_v = false;

template <typename T>
struct is_vec : std::false_type {};
template <typename T>
struct is_vec<std::vector<T>> : std::true_type {};

template <typename T, typename... Args>
constexpr bool is_unique_type_list() {
    if constexpr (sizeof...(Args) == 0)
        return true;
    else if constexpr ((std::is_same_v<T, Args> || ...))
        return false;
    else
        return is_unique_type_list<Args...>();
}

template <typename T>
std::string join(std::string_view delimiter, const T &sequence) {
    if (sequence.empty()) return "";
    std::stringstream buf{};
    buf << *sequence.begin();
    for (auto iter = std::next(sequence.begin()); iter != sequence.end(); iter = std::next(iter))
        buf << delimiter << *iter;
    return buf.str();
}

template <typename T, typename F>
std::string join(std::string_view delimiter, const T &sequence, F &&func) {
    if (sequence.empty()) return "";
    std::stringstream buf{};
    buf << *sequence.begin();
    for (auto iter = std::next(sequence.begin()); iter != sequence.end(); iter = std::next(iter))
        buf << delimiter << func(*iter);
    return buf.str();
}
}  // namespace sysyf
