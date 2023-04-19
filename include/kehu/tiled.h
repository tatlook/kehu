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

#if !defined(_KEHU_TILED_H)
#define _KEHU_TILED_H

namespace kehu::ast
{

class tiled_ast_visitor;

class tiled_node
{
public:
        virtual void accept(tiled_ast_visitor &visitor) const = 0;
};


class tiled_element_node : public tiled_node
{
public:
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

        virtual void accept(completed_ast_visitor &visitor) const override;

};

template class literal_node<std::string>;
class string_literal_node : public literal_node<std::string>
{
public:
        explicit string_literal_node(const std::string &value)
                : literal_node<std::string>(value)
        {}

        virtual void accept(completed_ast_visitor &visitor) const override;

};

template class literal_node<signed long>;
class integer_literal_node : public literal_node<signed long>
{
public:
        explicit integer_literal_node(const signed long value)
                : literal_node<signed long>(value)
        {}

        virtual void accept(completed_ast_visitor &visitor) const override;

};

class tiled_ast_visitor
{
public:

};

} // namespace kehu::ast


#endif // _KEHU_TILED_H

