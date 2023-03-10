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

#if !defined(_SYNTAX_TREE_H)
#define _SYNTAX_TREE_H

#include <vector>
#include <string>
#include <variant>
#include <stdexcept>
#include <memory>

#include "token.h"

namespace kehu::ast
{

/**
 * @brief Base class of all ast nodes.
 */
struct syntax_node
{
        /**
         * @brief Generates kehu code.
         * The code is not strictly human-readle.
         * 
         * @return string of a kehu code
         */
        virtual std::string generate_kehu_code() const = 0;

        bool operator==(const syntax_node &other) const
        {
                return typeid(this) == typeid(&other)
                        && this->generate_kehu_code() == other.generate_kehu_code();
        }

        bool operator!=(const syntax_node &other) const
        {
                return ! (*this == other);
        }

        friend std::ostream &operator<<(std::ostream &out, const syntax_node &node)
        {
                return out << node.generate_kehu_code();
        }
};

struct value_node : syntax_node
{
};

struct expression_node : value_node
{
};

struct variable_reference_node : expression_node
{
        std::string name;
        std::string generate_kehu_code() const override;
};

struct raw_char_value_node : expression_node
{
        char value;
        std::string generate_kehu_code() const override;
};

struct raw_string_value_node : expression_node
{
        std::string value;
        std::string generate_kehu_code() const override;
};

struct raw_integer_value_node : expression_node
{
        signed long value;
        std::string generate_kehu_code() const override;
};

struct word_node : value_node
{
        std::string word;
        std::string generate_kehu_code() const override;
};

struct statement_node : syntax_node
{
};

/**
 * 
 * @brief 
 * @tparam T a statement_node
 */
template <typename T>
struct block_node : value_node
{
        std::vector<std::unique_ptr<T>> statements;
        std::string generate_kehu_code() const override;
private:
        inline void __test_have_member() {
                std::string (T::*__test)() const = T::generate_kehu_code;
        };
};

struct tiled_statement_node;
template class block_node<tiled_statement_node>;

struct tiled_block_node : block_node<tiled_statement_node>
{
};

/**
 * @brief 
 */
struct compile_unit_node : syntax_node
{
        std::vector<std::unique_ptr<syntax_node>> global_definitions;
        std::string generate_kehu_code() const override;
};

/**
 * @brief The primeval expression before re-analysing.
 * It might be
 * <pre>
 * int saatana
 * </pre>
 */
struct tiled_statement_node : statement_node
{
        std::vector<std::unique_ptr<value_node>> lex;
        std::string generate_kehu_code() const override;
};

/**
 * @brief Parses form token list to a primeval ast
 * 
 * @author Zhen You Zhe
 */
std::unique_ptr<syntax_node> parse_primeval_ast(const std::vector<token::Token> &tokens);

std::unique_ptr<syntax_node> transform_ast(
                const std::unique_ptr<syntax_node> syntax_node);

class syntax_error : public std::runtime_error
{
        const token::Token error_token;
public:
        explicit syntax_error(const std::string &message)
                        : std::runtime_error(message), error_token({.linec = 0})
        {}

        explicit syntax_error(const std::string &message, token::Token t) 
                        : std::runtime_error(message), error_token(t)
        {}

        const token::Token &get_error_token() const noexcept
        {
                return error_token;
        }
};

struct executable_statement_node : tiled_statement_node
{
};

struct function_block_node : block_node<executable_statement_node>
{
};

struct function_definition_node : syntax_node
{
        std::vector<std::unique_ptr<value_node>> lex;
        function_block_node block;
        std::string generate_kehu_code() const override;
};

} // namespace kehu::ast

#endif // _SYNTAX_TREE_H
