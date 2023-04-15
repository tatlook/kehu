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

std::string tiled_statement_node::generate_kehu_code() const
{
        std::string code;
        for (const auto &l : this->lex) {
                code += l->generate_kehu_code();
                code += ' ';
        }
        code += '.';
        return code;
}

std::string type_node::generate_kehu_code() const
{
        return name;
}

std::string variable_node::generate_kehu_code() const
{
        return name;
}

std::string char_literal_node::generate_kehu_code() const
{
        return std::string("'") + get_value() + '\'';
}

std::string string_literal_node::generate_kehu_code() const
{
        return '"' + get_value() + '"';
}

std::string integer_literal_node::generate_kehu_code() const
{
        return std::to_string(get_value());
}

std::string word_node::generate_kehu_code() const
{
        return word;
}

template <typename T>
std::string block_node<T>::generate_kehu_code() const
{
        std::string code;
        code += "{\n";
        for (const auto &st : statements) {
                code += st->generate_kehu_code();
                code += '\n';
        }
        code += "}";
        return code;
}

std::string executable_statement_node::generate_kehu_code() const
{
        return expression->generate_kehu_code() + ".";
}

std::string variable_definition_node::generate_kehu_code() const
{
        std::string code;
        code += "define variable";
        code += '\n';
        code += variable->generate_kehu_code();
        code += '.';
        return code;
}

std::string function_definition_node::generate_kehu_code() const
{
        std::string code;
        code += "define function";
        code += '\n';
        for (const auto &l : this->lex) {
                code += l->generate_kehu_code();
                code += ' ';
        }
        code += '\n';
        code += block->generate_kehu_code();
        code += '.';
        return code;
}

std::string function_call_node::generate_kehu_code() const
{
        std::string code;
        for (auto l : function) {
                code += l->generate_kehu_code();
                code += " ";
        }
        return code;
}

} // namespace kehu::ast
