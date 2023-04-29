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

void ir_build_visitor::visit(const ast::compile_unit_node &node)
{
        for (auto definition : node.get_statements()) {
                definition->accept(*this);
        }
}

} // namespace kehu::ir
