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

#if !defined(_KEHU_AST_H)
#define _KEHU_AST_H

#include <vector>
#include <string>
#include <variant>
#include <stdexcept>
#include <memory>

#include "token.h"
#include "diagnostic.h"

namespace kehu::dump
{

template <typename T_node>
std::string dump(const T_node &node);

}

namespace kehu::ast
{

class ast_visitor;

/**
 * @brief Base class of all ast nodes.
 */
struct syntax_node
{
        /**
         * @brief Where this sytax node is
         * From first token to last token.
         */
        diagnostic::location location;

        virtual void accept(ast_visitor &visitor) const = 0;

        bool operator==(const syntax_node &other) const
        {
                return typeid(this) == typeid(&other)
                        && dump::dump(*this) == dump::dump(other);
        }

        bool operator!=(const syntax_node &other) const
        {
                return ! (*this == other);
        }

        friend std::ostream &operator<<(std::ostream &out, const syntax_node &node)
        {
                return out << dump::dump(node);
        }
};

struct tiled_element_node : syntax_node
{
        virtual bool is_expression() const
        {
                return false;
        }

        virtual bool is_word() const
        {
                return false;
        }

        virtual bool is_block() const
        {
                return false;
        }

        virtual bool is_variable() const
        {
                return false;
        }

        virtual bool is_type() const
        {
                return false;
        }
};

struct expression_node : tiled_element_node
{
        bool is_expression() const final override
        {
                return true;
        }
};

class type_node : public expression_node
{
        const std::string name;
public:
        explicit type_node(const std::string &name)
                : name(name)
        {}

        const std::string &get_name() const
        {
                return name;
        }
        
        virtual void accept(ast_visitor &visitor) const override;


        bool is_type() const final override
        {
                return true;
        }
};

class variable_node : public expression_node
{
        const std::string name;
public:
        explicit variable_node(const std::string &name)
                : name(name)
        {}

        const std::string &get_name() const
        {
                return name;
        }
        
        virtual void accept(ast_visitor &visitor) const override;


        bool is_variable() const final override
        {
                return true;
        }
};

template <typename T_value>
class literal_node : public expression_node
{
        const T_value value;
public:
        explicit literal_node(const T_value &value)
                : value(value)
        {}

        const T_value &get_value() const
        {
                return value;
        }
};

template class literal_node<char>;
class char_literal_node : public literal_node<char>
{
public:
        explicit char_literal_node(const char value)
                : literal_node<char>(value)
        {}

        virtual void accept(ast_visitor &visitor) const override;

};

template class literal_node<std::string>;
class string_literal_node : public literal_node<std::string>
{
public:
        explicit string_literal_node(const std::string &value)
                : literal_node<std::string>(value)
        {}

        virtual void accept(ast_visitor &visitor) const override;

};

template class literal_node<signed long>;
class integer_literal_node : public literal_node<signed long>
{
public:
        explicit integer_literal_node(const signed long value)
                : literal_node<signed long>(value)
        {}

        virtual void accept(ast_visitor &visitor) const override;

};

class word_node : public tiled_element_node
{
        const std::string word;
public:
        explicit word_node(const std::string &word)
                : word(word)
        {}

        const std::string &get_name() const
        {
                return word;
        }

        bool is_word() const final override
        {
                return true;
        }

        virtual void accept(ast_visitor &visitor) const override;

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
struct block_node : tiled_element_node
{
        std::vector<std::shared_ptr<T>> statements;

        bool is_block() const final override
        {
                return true;
        }
};

struct tiled_statement_node;
template class block_node<tiled_statement_node>;

struct tiled_block_node : block_node<tiled_statement_node>
{
        virtual void accept(ast_visitor &visitor) const override;
};

/**
 * @brief The primeval expression before re-analysing.
 * It might be
 * <pre>
 * int saatana
 * </pre>
 */
class tiled_statement_node : public statement_node
{
        const std::vector<std::shared_ptr<tiled_element_node>> lex;
public:
        explicit tiled_statement_node(const std::vector
                        <std::shared_ptr<tiled_element_node>> &lex)
                : lex(lex)
        {}

        const std::vector<std::shared_ptr<tiled_element_node>> &get_lex() const
        {
                return lex;
        }

        virtual void accept(ast_visitor &visitor) const override;

};

/**
 * @brief Parses form token list to a primeval ast
 * 
 * @author Zhen You Zhe
 */
std::shared_ptr<tiled_block_node> parse_primeval_ast(const std::vector<token::Token> &tokens);

class executable_statement_node : public statement_node
{
        std::shared_ptr<expression_node> expression;
public:
        explicit executable_statement_node(std::shared_ptr<expression_node>
                        expression)
                : expression(expression)
        {}

        std::shared_ptr<const expression_node> get_expression() const
        {
                return expression;
        }

        virtual void accept(ast_visitor &visitor) const override;

};

struct definition_node : syntax_node
{
        virtual bool is_variable_definition() const
        {
                return false;
        }

        virtual bool is_function_definition() const
        {
                return false;
        }
};

class variable_definition_node : public definition_node
{
        std::shared_ptr<const type_node> type;
        std::shared_ptr<const variable_node> variable;
public:
        variable_definition_node(std::shared_ptr<const type_node> type,
                        std::shared_ptr<const variable_node> variable)
                : type(type), variable(variable)
        {}

        std::shared_ptr<const type_node> get_type() const
        {
                return type;
        }

        std::shared_ptr<const variable_node> get_variable() const
        {
                return variable;
        }

        virtual void accept(ast_visitor &visitor) const override;


        bool is_variable_definition() const final override
        {
                return true;
        }
};

struct executable_block_node : block_node<executable_statement_node>
{
        virtual void accept(ast_visitor &visitor) const override;
};

template struct block_node<executable_statement_node>;

class function_definition_node : public definition_node
{
        std::vector<std::shared_ptr<const tiled_element_node>> lex;
        std::shared_ptr<const executable_block_node> block;
public:
        explicit function_definition_node(const std::vector
                        <std::shared_ptr<const tiled_element_node>> &lex,
                        std::shared_ptr<executable_block_node> block)
                : lex(lex), block(block)
        {}

        std::vector<std::shared_ptr<const tiled_element_node>> get_lex() const
        {
                return lex;
        }

        std::shared_ptr<const executable_block_node> get_block() const
        {
                return block;
        };

        virtual void accept(ast_visitor &visitor) const override;


        bool is_function_definition() const final override
        {
                return true;
        }
};

/**
 * @brief A function call
 * Calls a function @link function @endlink.
 * 
 */
class function_call_node : public expression_node
{
        /**
         * @brief The function
         * 
         */
        std::vector<std::shared_ptr<const tiled_element_node>> function;

        /**
         * @brief Arguments to the function.
         * 
         */
        std::vector<std::shared_ptr<const expression_node>> args;
public:
        explicit function_call_node(const std::vector
                        <std::shared_ptr<const tiled_element_node>> &function,
                        const std::vector
                        <std::shared_ptr<const expression_node>> &args)
                : function(function), args(args)
        {}
        
        std::vector<std::shared_ptr<const tiled_element_node>> get_function() const
        {
                return function;
        }

        std::vector<std::shared_ptr<const expression_node>> get_args() const
        {
                return args;
        }

        virtual void accept(ast_visitor &visitor) const override;
};

struct definition_block_node : block_node<definition_node>
{
        virtual void accept(ast_visitor &visitor) const override;
};

template class block_node<definition_node>;

struct compile_unit_node : definition_block_node
{
};

std::shared_ptr<compile_unit_node> transform_ast(
                std::shared_ptr<const tiled_block_node> root_node);

class ast_visitor
{
public:
        virtual void visit(const type_node &node) = 0;
        virtual void visit(const variable_node &node) = 0;
        virtual void visit(const char_literal_node &node) = 0;
        virtual void visit(const string_literal_node &node) = 0;
        virtual void visit(const integer_literal_node &node) = 0;
        virtual void visit(const word_node &node) = 0;
        virtual void visit(const tiled_block_node &node) = 0;
        virtual void visit(const tiled_statement_node &node) = 0;
        virtual void visit(const executable_statement_node &node) = 0;
        virtual void visit(const variable_definition_node &node) = 0;
        virtual void visit(const executable_block_node &node) = 0;
        virtual void visit(const function_definition_node &node) = 0;
        virtual void visit(const function_call_node &node) = 0;
        virtual void visit(const definition_block_node &node) = 0;
        virtual void visit(const compile_unit_node &node) = 0;
};

} // namespace kehu::ast

#endif // _KEHU_AST_H
