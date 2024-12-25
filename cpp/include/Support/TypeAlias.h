#pragma once
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <vector>

namespace sysyf {

template <typename T>
using RefPtr = T*;

template <typename T>
using Vec = std::vector<T>;

template <typename K, typename V, typename Compare = std::less<K>>
using Map = std::map<K, V, Compare>;

template <typename T>
using List = std::list<T>;

template <typename T>
using Opt = std::optional<T>;

}  // namespace sysyf
