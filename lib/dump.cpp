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
#include <kehu/ast.h>

namespace kehu::dump
{

using namespace ast;

void dumper::visit(const tiled_statement_node &node)
{
        for (const auto &l : node.get_lex()) {
                l->accept(*this);
                code += ' ';
        }
        code += '.';
}

void dumper::visit(const type_node &node)
{
        code += node.get_name();
}

void dumper::visit(const variable_node &node)
{
        code += node.get_name();
}

void dumper::visit(const char_literal_node &node)
{
        code += '\'' + node.get_value() + '\'';
}

void dumper::visit(const string_literal_node &node)
{
        code += '"' + node.get_value() + '"';
}

void dumper::visit(const integer_literal_node &node)
{
        code += std::to_string(node.get_value());
}

void dumper::visit(const word_node &node)
{
        code += node.get_name();
}

template <typename T>
static std::string visit_block(const block_node<T> &node, dumper &du)
{
        std::string code;
        code += "{\n";
        for (const auto &st : node.statements) {
                st->accept(du);
                code += '\n';
        }
        code += "}";
        return code;
}
        
void dumper::visit(const ast::tiled_block_node &node)
{
        code += visit_block(node, *this);
}

void dumper::visit(const executable_statement_node &node)
{
        node.get_expression()->accept(*this);
        code += ".";
}

void dumper::visit(const variable_definition_node &node)
{
        code += "define variable\n";
        node.get_type()->accept(*this);
        node.get_variable()->accept(*this);
        code += '.';
}

void dumper::visit(const ast::executable_block_node &node)
{
        code += visit_block(node, *this);
}

void dumper::visit(const function_definition_node &node)
{
        code += "define function\n";
        for (const auto &l : node.get_lex()) {
                l->accept(*this);
                code += ' ';
        }
        code += '\n';
        node.get_block()->accept(*this);
        code += '.';
}

void dumper::visit(const function_call_node &node)
{
        for (auto l : node.get_function()) {
                l->accept(*this);
                code += " ";
        }
}

void dumper::visit(const ast::definition_block_node &node)
{
        code += visit_block(node, *this);
}

void dumper::visit(const ast::compile_unit_node &node)
{
        for (const auto &st : node.statements) {
                st->accept(*this);
                code += '\n';
        }
}

} // namespace kehu::ast
