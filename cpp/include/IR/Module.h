#pragma once
#include <memory>
#include <ostream>

#include "Constant.h"
#include "Function.h"
#include "GlobalVariable.h"

namespace sysyf {
namespace ir {
class Module {
  public:
    Module() = default;
    RefPtr<Constant> add_constant(std::unique_ptr<Constant> &&c) {
        constants_.push_back(std::move(c));
        return constants_.back().get();
    }
    RefPtr<GlobalVariable> add_global_var(std::unique_ptr<GlobalVariable> &&v) {
        global_vars_.push_back(std::move(v));
        return global_vars_.back().get();
    }
    RefPtr<Function> add_function(std::unique_ptr<Function> &&f) {
        functions_.push_back(std::move(f));
        return functions_.back().get();
    }

    friend std::ostream &operator<<(std::ostream &out, const Module &mod) {
        for (const auto &var : mod.global_vars_) out << *var << "\n";
        for (const auto &func : mod.functions_) out << *func << "\n";
        return out;
    }

  private:
    Vec<std::unique_ptr<Constant>> constants_;
    Vec<std::unique_ptr<GlobalVariable>> global_vars_;
    Vec<std::unique_ptr<Function>> functions_;
};

}  // namespace ir
}  // namespace sysyf
