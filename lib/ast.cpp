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

std::string primeval_statement_node::generate_kehu_code() const
{
        std::string code;
        for (const auto &l : this->lex) {
                if (std::holds_alternative<std::string>(l)) {
                        code += std::get<std::string>(l);
                } else if (std::holds_alternative<std::unique_ptr<value_node>>(l)) {
                        code += std::get<std::unique_ptr<value_node>>(l)
                                        ->generate_kehu_code();
                } else {
                        throw std::logic_error(" ");
                }
                code += ' ';
        }
        code += '.';
        return code;
}

std::string variable_reference_node::generate_kehu_code() const
{
        return name;
}

std::string function_call_node::generate_kehu_code() const
{
        return std::string(); // FIXME
}

std::string word_node::generate_kehu_code() const
{
        return word;
}

std::string expression_statement_node::generate_kehu_code() const
{
        std::string code;
        code += expression->generate_kehu_code();
        code += '.';
        return code;
}

std::string block_node::generate_kehu_code() const
{
        std::string code;
        code += "@{\n";
        for (const auto &st : statements) {
                code += st->generate_kehu_code();
                code += '\n';
        }
        code += "@}";
        return code;
}

std::string function_definition_node::generate_kehu_code() const
{
        return std::string();
}

std::string file_node::generate_kehu_code() const
{
        std::string code;
        for (const auto &st : global_definitions) {
                code += st->generate_kehu_code();
                code += '\n';
        }
        return code;
}

} // namespace kehu::ast
