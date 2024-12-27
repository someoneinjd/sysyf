#pragma once
#include <memory>
#include <ostream>

#include "Constant.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ir {
class Module {
  public:
    Module() = default;
    RefPtr<Constant> add_constant(int value) {
        auto [iter, success] = int_constants_.insert({value, nullptr});
        if (success) iter->second = std::unique_ptr<ConstantInt>{new ConstantInt{this, value}};
        return iter->second.get();
    }
    RefPtr<Constant> add_constant(float value) {
        auto [iter, success] = fp_constants_.insert({value, nullptr});
        if (success) iter->second = std::unique_ptr<ConstantFP>{new ConstantFP{this, value}};
        return iter->second.get();
    }
    RefPtr<Constant> add_constant(Vec<RefPtr<Constant>> value) {
        auto const_ = std::unique_ptr<Constant>{new ConstantArray{this, std::move(value)}};
        constants_.push_back(std::move(const_));
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
    Map<int, std::unique_ptr<ConstantInt>> int_constants_;  // cache for int constants
    Map<float, std::unique_ptr<ConstantFP>> fp_constants_;  // cache for float constants
    Vec<std::unique_ptr<Constant>> constants_;
    Vec<std::unique_ptr<GlobalVariable>> global_vars_;
    Vec<std::unique_ptr<Function>> functions_;
};

}  // namespace ir
}  // namespace sysyf
