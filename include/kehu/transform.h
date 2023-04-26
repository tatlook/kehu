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

#if !defined(_KEHU_TRANSFORM_H)
#define _KEHU_TRANSFORM_H

#include "ast.h"

namespace kehu::trans
{

class transform_visitor : public ast::ast_visitor
{
        
public:
        virtual void visit(const ast::type_node &node) override;
        virtual void visit(const ast::variable_node &node) override;
        virtual void visit(const ast::char_literal_node &node) override;
        virtual void visit(const ast::string_literal_node &node) override;
        virtual void visit(const ast::integer_literal_node &node) override;
        virtual void visit(const ast::word_node &node) override;
        virtual void visit(const ast::tiled_block_node &node) override;
        virtual void visit(const ast::tiled_statement_node &node) override;
        virtual void visit(const ast::executable_statement_node &node) override;
        virtual void visit(const ast::variable_definition_node &node) override;
        virtual void visit(const ast::executable_block_node &node) override;
        virtual void visit(const ast::function_definition_node &node) override;
        virtual void visit(const ast::function_call_node &node) override;
        virtual void visit(const ast::definition_block_node &node) override;
        virtual void visit(const ast::compile_unit_node &node) override;
};

}

#endif // _KEHU_TRANSFORM_H
