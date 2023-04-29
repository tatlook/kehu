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

#include "tiled.h"
#include "token.h"
#include "diagnostic.h"

namespace kehu::ast
{

class tiled_tree_visitor;

struct expression_node : tiled_element_node
{
        bool is_expression() const final override
        {
                return true;
        }
};

class type_node : public tiled_element_node
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
        
        virtual void accept(tiled_tree_visitor &visitor) const override;

        bool is_type() const final override
        {
                return true;
        }
};

class variable_node : public tiled_element_node
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
        
        virtual void accept(tiled_tree_visitor &visitor) const override;


        bool is_variable() const final override
        {
                return true;
        }
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

        virtual void accept(tiled_tree_visitor &visitor) const override;

};


template <typename T_value>
class literal_node : public tiled_element_node
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

        virtual void accept(tiled_tree_visitor &visitor) const override;

};

template class literal_node<std::string>;
class string_literal_node : public literal_node<std::string>
{
public:
        explicit string_literal_node(const std::string &value)
                : literal_node<std::string>(value)
        {}

        virtual void accept(tiled_tree_visitor &visitor) const override;

};

template class literal_node<signed long>;
class integer_literal_node : public literal_node<signed long>
{
public:
        explicit integer_literal_node(const signed long value)
                : literal_node<signed long>(value)
        {}

        virtual void accept(tiled_tree_visitor &visitor) const override;

};

class tiled_statement_node;

class tiled_block_node : public tiled_element_node
{
        std::vector<std::shared_ptr<tiled_statement_node>> statements;
public:
        bool is_block() const final override
        {
                return true;
        }

        const std::vector<std::shared_ptr<tiled_statement_node>>
                        &get_statements() const
        {
                return statements;
        }

        std::vector<std::shared_ptr<tiled_statement_node>>
                        &get_statements()
        {
                return statements;
        }

        virtual void accept(tiled_tree_visitor &visitor) const override;
};

/**
 * @brief The primeval expression before re-analysing.
 * It might be
 * <pre>
 * int saatana
 * </pre>
 */
class tiled_statement_node : public tiled_node
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

        virtual void accept(tiled_tree_visitor &visitor) const override;

};

/**
 * @brief Parses form token list to a primeval ast
 * 
 * @author Zhen You Zhe
 */
std::shared_ptr<tiled_block_node> parse_tiled_tree(const std::vector<token::Token> &tokens);

class compile_unit_node : public tiled_block_node
{
public:
        virtual void accept(tiled_tree_visitor &visitor) const override;
};

class tiled_tree_visitor
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
        virtual void visit(const compile_unit_node &node) = 0;
};

} // namespace kehu::ast

#endif // _KEHU_AST_H
