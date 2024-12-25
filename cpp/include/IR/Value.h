#pragma once
#include "Type.h"

namespace sysyf {
namespace ir {
class Value {
  public:
    enum class TypeID : unsigned char { Value, Constant, GlobalVariable, Function, Argument, BasicBlock, Instruction };

  protected:
    Value() : type_{}, id_{TypeID::Value}, name_{} {}
    Value(Type t, TypeID id, std::string name) : type_{std::move(t)}, id_{id}, name_{std::move(name)} {}

  public:
    TypeID type_id() const { return id_; }

    template <typename T>
    bool is() const {
        return T::classof(this);
    }

    template <typename T>
    T *as() {
        return is<T>() ? static_cast<T *>(this) : nullptr;
    }

    template <typename T>
    const T *as() const {
        return is<T>() ? static_cast<const T *>(this) : nullptr;
    }

    const Type &type() const { return type_; }
    const std::string &name() const { return name_; }

    static bool classof(const Value *a) { return a->type_id() == TypeID::Value; }

  private:
    Type type_;
    const TypeID id_;
    std::string name_;
};

}  // namespace ir
}  // namespace sysyf
