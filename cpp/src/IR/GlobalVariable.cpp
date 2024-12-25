#include "GlobalVariable.h"

#include <memory>

#include "Module.h"
namespace sysyf {
namespace ir {
RefPtr<GlobalVariable> GlobalVariable::new_(RefPtr<Module> p, Type t, std::string name, bool is_const,
                                            RefPtr<Constant> c) {
    auto global_var =
        std::unique_ptr<GlobalVariable>{new GlobalVariable{p, std::move(t), std::move(name), is_const, c}};
    return p->add_global_var(std::move(global_var));
}

}  // namespace ir
}  // namespace sysyf
