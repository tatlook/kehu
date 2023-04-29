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

#include "diagnostic.h"

namespace kehu::dump
{

template <typename T_node>
std::string dump(const T_node &node);

}

namespace kehu::ast
{

class tiled_tree_visitor;

class tiled_node
{
public:
      /**
         * @brief Where this sytax node is
         * From first token to last token.
         */
        diagnostic::location location;

        bool operator==(const tiled_node &other) const
        {
                return typeid(this) == typeid(&other)
                        && dump::dump(*this) == dump::dump(other);
        }

        bool operator!=(const tiled_node &other) const
        {
                return ! (*this == other);
        }

        friend std::ostream &operator<<(std::ostream &out, const tiled_node &node)
        {
                return out << dump::dump(node);
        }

        virtual void accept(tiled_tree_visitor &visitor) const = 0;
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

} // namespace kehu::ast


#endif // _KEHU_TILED_H

