#pragma once

#include <ostream>

#include "Box.hpp"
#include "TypeAlias.h"
#include "Union.hpp"
namespace sysyf {
namespace ir {

struct VoidType {};

struct LabelType {};

struct IntType {
    unsigned width;
};

struct FloatType {};

using Type = Union<VoidType, LabelType, IntType, FloatType, Box<struct PointerType>, Box<struct ArrayType>,
                   Box<struct FunctionType>>;

struct PointerType {
    Type pointee;
};

struct ArrayType {
    unsigned length;
    Type element_type;
};

struct FunctionType {
    Type ret_type;
    Vec<Type> arg_types;
};

bool operator==(const VoidType &, const VoidType &);
bool operator==(const LabelType &, const LabelType &);
bool operator==(const IntType &a, const IntType &b);
bool operator==(const FloatType &, const FloatType &);
bool operator==(const PointerType &a, const PointerType &b);
bool operator==(const ArrayType &a, const ArrayType &b);
bool operator==(const FunctionType &a, const FunctionType &b);
bool operator!=(const VoidType &a, const VoidType &b);
bool operator!=(const LabelType &a, const LabelType &b);
bool operator!=(const IntType &a, const IntType &b);
bool operator!=(const FloatType &a, const FloatType &b);
bool operator!=(const PointerType &a, const PointerType &b);
bool operator!=(const ArrayType &a, const ArrayType &b);
bool operator!=(const FunctionType &a, const FunctionType &b);
std::ostream &operator<<(std::ostream &out, const VoidType &t);
std::ostream &operator<<(std::ostream &out, const LabelType &t);
std::ostream &operator<<(std::ostream &out, const IntType &t);
std::ostream &operator<<(std::ostream &out, const FloatType &t);
std::ostream &operator<<(std::ostream &out, const PointerType &t);
std::ostream &operator<<(std::ostream &out, const ArrayType &t);
std::ostream &operator<<(std::ostream &out, const FunctionType &t);
}  // namespace ir

}  // namespace sysyf
