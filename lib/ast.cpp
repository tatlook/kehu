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

#include <kehu/ast.h>

namespace kehu::ast
{

void tiled_statement_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void type_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void variable_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void char_literal_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void string_literal_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void integer_literal_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void word_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void tiled_block_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void executable_statement_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void variable_definition_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void executable_block_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void function_definition_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void function_call_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

void definition_block_node::accept(ast_visitor &visitor) const
{
        visitor.visit(*this);
}

} // namespace kehu::ast
