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

#if !defined(_KEHU_DUMP_H)
#define _KEHU_DUMP_H

#include <string>
#include "ast.h"
#include "tiled.h"

namespace kehu::dump
{

/**
 * @brief Generates kehu code.
 * The code is not strictly human-readle.
 * 
 * @return string of a kehu code
 */
class dumper : public ast::tiled_tree_visitor
{
        std::string code;
public:
        const std::string &get_code() const
        {
                return code;
        }

        virtual void visit(const ast::type_node &node) override;
        virtual void visit(const ast::variable_node &node) override;
        virtual void visit(const ast::char_literal_node &node) override;
        virtual void visit(const ast::string_literal_node &node) override;
        virtual void visit(const ast::integer_literal_node &node) override;
        virtual void visit(const ast::word_node &node) override;
        virtual void visit(const ast::tiled_block_node &node) override;
        virtual void visit(const ast::tiled_statement_node &node) override;
        virtual void visit(const ast::compile_unit_node &node) override;
};

template <typename T_node>
inline std::string dump(const T_node &node)
{
        dumper du;
        node.accept(du);
        return du.get_code();
}

} // namespace kehu::dump


#endif // _KEHU_DUMP_H
