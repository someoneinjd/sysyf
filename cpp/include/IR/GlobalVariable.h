#pragma once
#include <ostream>

#include "Constant.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Value.h"

namespace sysyf {
namespace ir {
class Module;
class GlobalVariable : public Value {
    GlobalVariable(RefPtr<Module> p, Type t, std::string name, bool is_const = false, RefPtr<Constant> c = nullptr)
        : Value(PointerType{std::move(t)}, TypeID::GlobalVariable, std::move(name)),
          parent_{p},
          init_{c},
          is_const_{is_const} {}

  public:
    RefPtr<Module> parent() const { return parent_; }
    RefPtr<Constant> initializer() const { return init_; }
    static bool classof(const Value *v) { return v->type_id() == TypeID::GlobalVariable; }
    static RefPtr<GlobalVariable> new_(RefPtr<Module> p, Type t, std::string name, bool is_const = false, RefPtr<Constant> c = nullptr);
    friend std::ostream &operator<<(std::ostream &out, const GlobalVariable &global_var) {
        out << "@" << global_var.name() << " = " << (global_var.is_const_ ? "constant " : "global ") << global_var.type().as<PointerType>()->pointee << " ";
        if (global_var.initializer())
            out << *global_var.initializer();
        else
            out << " zeroinitializer";
        return out;
    }

  private:
    RefPtr<Module> parent_;
    RefPtr<Constant> init_;
    bool is_const_;
};
}  // namespace ir
}  // namespace sysyf
