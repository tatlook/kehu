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

#include <kehu/dump.h>
#include <kehu/build_ir.h>
#include <llvm/IR/IRBuilder.h>

namespace kehu::ir
{

using llvm::IRBuilder;
using llvm::Value;
using llvm::LLVMContext;
using llvm::Module;

using namespace kehu::ast;

ir_build_visitor::ir_build_visitor()
        : context(), module("kehu-default-module", context), builder(context)
{}

void ir_build_visitor::visit(const tiled_statement_node &node)
{
        diagnostic::report("internal error: we cannot use tiled", node);
}

void ir_build_visitor::visit(const type_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const variable_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const char_literal_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const string_literal_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const integer_literal_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const word_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const ast::tiled_block_node &node)
{
        diagnostic::report("internal error: we cannot use tiled", node);
}

void ir_build_visitor::visit(const executable_statement_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const variable_definition_node &node)
{
        llvm::GlobalVariable var(builder.getDoubleTy(), true,
                        llvm::GlobalVariable::ExternalLinkage);
}

void ir_build_visitor::visit(const ast::executable_block_node &node)
{
        /// TODO: fill the stub
}

/**
 * @brief Get the function type object
 * 
 * Make the function type:  double(double,double) etc.
 */
static llvm::FunctionType *get_function_type(
                const ast::function_definition_node &fdef,
                IRBuilder<> &builder, LLVMContext &context, Module &module)
{
        int argc = 0;
        for (auto l : fdef.get_lex()) {
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
                const ast::function_definition_node &fdef)
{
        std::string name;
        for (auto l : fdef.get_lex()) {
                name += dump::dump(*l);
                name += " ";
        }
        return name;
}

void ir_build_visitor::visit(const function_definition_node &node)
{
        llvm::FunctionType *func_type =
                        get_function_type(node, builder, context, module);

        llvm::Function *func = llvm::Function::Create(func_type, 
                        llvm::Function::ExternalLinkage,
                        generate_function_name(node), module);

        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", func);
        builder.SetInsertPoint(entry);
        
        /// TODO: body

        builder.CreateRet(llvm::ConstantFP::get(context, llvm::APFloat(0.0f)));
}

void ir_build_visitor::visit(const function_call_node &node)
{
        /// TODO: fill the stub
}

void ir_build_visitor::visit(const ast::definition_block_node &node)
{
        for (auto definition : node.statements) {
                definition->accept(*this);
        }
}

void ir_build_visitor::visit(const ast::compile_unit_node &node)
{
        for (auto definition : node.statements) {
                definition->accept(*this);
        }
}

} // namespace kehu::ir
