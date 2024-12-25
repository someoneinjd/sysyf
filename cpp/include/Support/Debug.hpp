#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string_view>

#include "TypeAlias.h"

namespace sysyf {

namespace detail {

class FormatArgBase {
  public:
    FormatArgBase() = default;
    FormatArgBase(const FormatArgBase &) = delete;
    FormatArgBase(FormatArgBase &&) = default;
    FormatArgBase &operator=(const FormatArgBase &) = delete;
    FormatArgBase &operator=(FormatArgBase &&) = default;
    virtual void format(std::ostream &out) const = 0;
    virtual ~FormatArgBase(){};
};

template <typename T>
class FormatArg : public FormatArgBase {
  public:
    FormatArg(const T &arg) : arg{arg} {}
    void format(std::ostream &out) const final { out << arg; }

  private:
    const T &arg;
};

template <typename... FormatArgs>
std::string format(std::string_view format_str, const FormatArgs &...args) {
    std::string result;
    result.reserve(format_str.size());
    std::stringstream out{result};
    std::array<const FormatArgBase *, sizeof...(args)> items{{&args...}};

    std::size_t pos = 0;
    std::size_t item_idx = 0;
    while (pos < format_str.size()) {
        auto next_left_brace = format_str.find_first_of('{', pos);
        auto next_right_brace = format_str.find_first_of('}', pos);
        if (next_right_brace < next_left_brace) {
            if (format_str[next_right_brace + 1] == '}') {
                out << format_str.substr(pos, next_right_brace - pos);
                out << '}';
                pos = next_right_brace + 2;
                if (pos >= format_str.size()) break;
            } else {
                throw std::runtime_error("Unmatched right brace");
            }
        }
        if (next_left_brace == std::string_view::npos) {
            out << format_str.substr(pos);
            break;
        }
        out << format_str.substr(pos, next_left_brace - pos);
        switch (format_str[next_left_brace + 1]) {
            case '{': {
                out << '{';
                pos = next_left_brace + 2;
                break;
            }
            case '}': {
                if (item_idx >= items.size()) throw std::runtime_error("Insufficient number of format args");
                items[item_idx++]->format(out);
                pos = next_left_brace + 2;
                break;
            }
            default: {
                throw std::runtime_error("Unmatched left brace");
                break;
            }
        }
    }
}

template <typename... Args>
void raw_print(std::ostream &stdout, std::string_view format_str, const Args &...args) {
    stdout << format(format_str, FormatArg(args)...);
}
}  // namespace detail

template <typename... Args>
void print(std::string_view format_str, const Args &...args) {
    raw_print(std::cout, format_str, args...);
}

template <typename... Args>
void println(std::string_view format_str, const Args &...args) {
    raw_print(std::cout, format_str, args...);
    std::cout << "\n";
}

class debug {
  public:
    debug(int verbosity, const char *file_name = __builtin_FILE(), const char *function_name = __builtin_FUNCTION(),
          const int line_number = __builtin_LINE())
        : logging{verbosity <= debug_level()},
          file_name{file_name},
          function_name{function_name},
          line_number{line_number} {}
    template <typename... Args>
    void operator()(std::string_view format_str, const Args &...args) const {
        if (logging) {
            raw_print(std::cerr, format_str, args...);
            std::cerr << std::endl;
        }
    }

  private:
    const bool logging;
    const char *file_name;
    const char *function_name;
    const int line_number;
    static int debug_level() {
        const static int cached_debug_level = [] {
            const auto *env = std::getenv("DEBUG");
            return env == nullptr ? 0 : std::atoi(env);
        }();
        return cached_debug_level;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vec<T> &val) {
    if (val.empty()) return out << "[]";
    out << "[" << val[0];
    for (std::size_t i = 1; i < val.size(); i++) out << ", " << val[i];
    return out << "]";
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const List<T> &val) {
    if (val.empty()) return out << "[]";
    out << "[" << *val.begin();
    for (auto i = std::next(val.begin()); i != val.end(); i++) out << ", " << *i;
    return out << "]";
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &out, const Map<K, V> &map) {
    if (map.empty()) return out << "{}";
    auto begin = map.begin();
    out << "{" << begin->first << ": " << begin->second;
    for (begin++; begin != map.end(); begin++) out << ", " << begin->first << ": " << begin->second;
    return out << "}";
}
}  // namespace sysyf
