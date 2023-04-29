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

#if !defined(_KEHU_BUILD_IR_H)
#define _KEHU_BUILD_IR_H

#include "ast.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace kehu::ir
{

class ir_build_visitor : public ast::tiled_tree_visitor
{
        llvm::LLVMContext context;
        llvm::Module module;
        llvm::IRBuilder<> builder;
        std::string builded_ir;
public:
        ir_build_visitor();

        const std::string &get_ir()
        {
                if (builded_ir != "")
                        return builded_ir;
                llvm::raw_string_ostream out(builded_ir);
                out << module;
                out.flush();
                return builded_ir;
        }

        virtual void visit(const ast::type_node &node) override;
        virtual void visit(const ast::variable_node &node) override;
        virtual void visit(const ast::char_literal_node &node) override;
        virtual void visit(const ast::string_literal_node &node) override;
        virtual void visit(const ast::integer_literal_node &node) override;
        virtual void visit(const ast::word_node &node) override;
        virtual void visit(const ast::tiled_block_node &node) override;
        virtual void visit(const ast::tiled_statement_node &node) override;
        virtual void visit(const ast::compile_unit_node &node) override;
};

inline std::string build_ir(const ast::tiled_node &node)
{
        ir_build_visitor irbv;
        node.accept(irbv);
        return irbv.get_ir();
}

} // namespace kehu::ir

#endif // _KEHU_BUILD_IR_H
