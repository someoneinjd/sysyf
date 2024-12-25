#include "Type.h"

#include <cstddef>

namespace sysyf {
namespace ir {
bool operator==(const VoidType &, const VoidType &) { return true; }
bool operator==(const LabelType &, const LabelType &) { return true; }
bool operator==(const IntType &a, const IntType &b) { return a.width == b.width; }
bool operator==(const FloatType &, const FloatType &) { return true; }
bool operator==(const PointerType &a, const PointerType &b) { return a.pointee == b.pointee; }
bool operator==(const ArrayType &a, const ArrayType &b) {
    return a.length == b.length && a.element_type == b.element_type;
}
bool operator==(const FunctionType &a, const FunctionType &b) {
    return a.ret_type == b.ret_type && a.arg_types == b.arg_types;
}
bool operator!=(const VoidType &a, const VoidType &b) { return not(a == b); }
bool operator!=(const LabelType &a, const LabelType &b) { return not(a == b); }
bool operator!=(const IntType &a, const IntType &b) { return not(a == b); }
bool operator!=(const FloatType &a, const FloatType &b) { return not(a == b); }
bool operator!=(const PointerType &a, const PointerType &b) { return not(a == b); }
bool operator!=(const ArrayType &a, const ArrayType &b) { return not(a == b); }
bool operator!=(const FunctionType &a, const FunctionType &b) { return not(a == b); }
std::ostream &operator<<(std::ostream &out, const VoidType &) { return out << "void"; }
std::ostream &operator<<(std::ostream &out, const LabelType &) { return out << "label"; }
std::ostream &operator<<(std::ostream &out, const IntType &t) { return out << "i" << t.width; }
std::ostream &operator<<(std::ostream &out, const FloatType &) { return out << "float"; }
std::ostream &operator<<(std::ostream &out, const PointerType &t) { return out << t.pointee << "*"; }
std::ostream &operator<<(std::ostream &out, const ArrayType &t) {
    return out << "[" << t.length << " x " << t.element_type << "]";
}
std::ostream &operator<<(std::ostream &out, const FunctionType &t) {
    out << t.ret_type << " (";
    if (not t.arg_types.empty()) out << t.arg_types[0];
    for (std::size_t i = 1; i < t.arg_types.size(); i++) out << ", " << t.arg_types[i];
    return out;
}

}  // namespace ir
}  // namespace sysyf
