#pragma once

#include <cstddef>
#include <cstdint>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>

#include "Type.h"
#include "TypeAlias.h"
#include "Value.h"

namespace sysyf {
namespace ir {
class Module;
class Constant : public Value {
  protected:
    Constant(RefPtr<Module> p, Type t, std::string name)
        : Value(std::move(t), TypeID::Constant, std::move(name)), parent_{p} {}

  public:
    RefPtr<Module> parent() const { return parent_; }
    virtual ~Constant() = default;
    static bool classof(const Value *v) { return v->type_id() == TypeID::Constant; }

  private:
    RefPtr<Module> parent_;
};

class ConstantInt : public Constant {
    ConstantInt(RefPtr<Module> p, int value) : Constant(p, IntType{32}, std::to_string(value)), value_{value} {}

  public:
    int value() const { return value_; }
    static RefPtr<ConstantInt> new_(RefPtr<Module> p, int value);
    static bool classof(const Value *v) { return v->type_id() == TypeID::Constant && v->type().is<IntType>(); }

  private:
    int value_;
};

inline static std::string get_binary_float_str(float val) {
    double i = val;
    std::stringstream s{};
    s << std::hex << "0x" << *(int64_t *)(&i);
    return s.str();
}

class ConstantFP : public Constant {
    ConstantFP(RefPtr<Module> p, float value) : Constant(p, FloatType{}, get_binary_float_str(value)), value_{value} {}

  public:
    float value() const { return value_; }
    static RefPtr<ConstantFP> new_(RefPtr<Module> p, float value);
    static bool classof(const Value *v) { return v->type_id() == TypeID::Constant && v->type().is<FloatType>(); }

  private:
    float value_;
};

class ConstantArray : public Constant {
    ConstantArray(RefPtr<Module> p, Vec<RefPtr<Constant>> value)
        : Constant(p, ArrayType{static_cast<unsigned>(value.size()), value[0]->type()}, "null"),
          value_{std::move(value)} {}

  public:
    const auto &value() const { return value_; }
    static RefPtr<ConstantArray> new_(RefPtr<Module> p, Vec<RefPtr<Constant>> value);
    static bool classof(const Value *v) { return v->type_id() == TypeID::Constant && v->type().is<ArrayType>(); }

  private:
    Vec<RefPtr<Constant>> value_;
};

inline std::ostream &operator<<(std::ostream &out, const Constant &const_) {
    switch (const_.type().index()) {
        case 2:
        case 3: return out << const_.name();
        case 5: {
            const auto &array = static_cast<const ConstantArray &>(const_).value();
            out << "[";
            if (not array.empty()) out << array[0]->type() << " " << *array[0];
            for (std::size_t i = 1; i < array.size(); i++) out << ", " << array[0]->type() << " " << *array[i];
            return out << "]";
        }
        default: return out;
    }
}

}  // namespace ir
}  // namespace sysyf
