#include "Function.h"

#include "Module.h"

namespace sysyf {
namespace ir {
RefPtr<Function> Function::new_(RefPtr<Module> p, FunctionType t, std::string func_name) {
    auto func = std::unique_ptr<Function>{new Function{p, std::move(t), std::move(func_name)}};
    return p->add_function(std::move(func));
}
}  // namespace ir
}  // namespace sysyf
