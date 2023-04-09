/* 
 * Kehu - a toe language
 * Copyright (C) 2023 Zhen You Zhe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kehu/build_ir.h>
#include <llvm/IR/IRBuilder.h>

namespace kehu::ir
{

using llvm::IRBuilder;
using llvm::Value;
using llvm::LLVMContext;
using llvm::Module;

static Value *build_raw_number_ir(
                std::shared_ptr<const ast::raw_integer_node> node,
                IRBuilder<> &builder, LLVMContext &context)
{
        llvm::ConstantFP *number = llvm::ConstantFP::get(context,
                llvm::APFloat(static_cast<float>(node->value)));
        return number;
}

static llvm::GlobalValue *build_variable_definition_ir(
                std::shared_ptr<const ast::definition_node> node,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        llvm::GlobalVariable *var = nullptr;
        return var;
}

/**
 * @brief Get the function type object
 * 
 * Make the function type:  double(double,double) etc.
 */
static llvm::FunctionType *get_function_type(
                std::shared_ptr<const ast::function_definition_node> fdef,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        int argc = 0;
        for (auto l : fdef->lex) {
                if (l->is_variable()) {
                        ++argc;
                }
        }
        std::vector<llvm::Type*> arg_types(argc,
                        llvm::Type::getDoubleTy(context));
        llvm::Type::getVoidTy(context);
        llvm::FunctionType *func_type = llvm::FunctionType::get(
                        llvm::Type::getDoubleTy(context), arg_types, false);
        return func_type;
}

static std::string generate_function_name(
                std::shared_ptr<const ast::function_definition_node> fdef)
{
        std::string name;
        for (auto l : fdef->lex) {
                name += l->generate_kehu_code();
                name += " ";
        }
        return name;
}

static llvm::GlobalValue *build_function_definition_ir(
                std::shared_ptr<const ast::definition_node> node,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        if ( ! node->is_function_definition())
                return build_variable_definition_ir(node, builder, context, module);
        auto fdef = std::static_pointer_cast
                        <const ast::function_definition_node>(node);

        llvm::FunctionType *func_type =
                        get_function_type(fdef, builder, context, module);

        llvm::Function *func = llvm::Function::Create(func_type, 
                        llvm::Function::ExternalLinkage,
                        generate_function_name(fdef), module);
        return func;
}

static llvm::GlobalValue *build_definition_ir(
                std::shared_ptr<const ast::definition_node> node,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        return build_function_definition_ir(node, builder, context, module);
}

static void build_compile_unit_ir(
                std::shared_ptr<const ast::compile_unit_node> node,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        for (auto definition : node->statements) {
                build_definition_ir(definition, builder, context, module);
        }
}

std::shared_ptr<std::string> build_ir(
                std::shared_ptr<const ast::compile_unit_node> node)
{
        LLVMContext context;
        Module module("kehu-default-module", context);
        IRBuilder<> builder(context);

        build_compile_unit_ir(node, builder, context, module);

        auto ir = std::make_shared<std::string>();
        llvm::raw_string_ostream out(*ir);
        out << module;
        out.flush();

        return ir;
}

} // namespace kehu::ir
