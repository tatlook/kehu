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

template <typename T>
static const T *require_cast(const std::unique_ptr<syntax_node> &node)
{
        if (typeid(*node) != typeid(T))
                throw syntax_error("cannot cast " __FILE__);
        return static_cast<T *>(node.get());
}

static std::unique_ptr<syntax_node> transform_global_variable_definition(
                const tiled_statement_node *node)
{

}

static std::unique_ptr<syntax_node> transform_function_definition(
                const tiled_statement_node *node)
{
        if (node->lex.size() < 2) // TODO
                return transform_global_variable_definition(node);

}

static std::unique_ptr<syntax_node> transform_global_definition(
                const std::unique_ptr<syntax_node> &node)
{
        const auto &st = require_cast<tiled_statement_node>(node);
        return transform_function_definition(st);
}

static std::unique_ptr<syntax_node> transform_compile_unit(
                const std::unique_ptr<syntax_node> &node)
{
        const auto &cu = require_cast<compile_unit_node>(node);
        for (const auto &node2 : cu->global_definitions) {
                transform_global_definition(node2);
        }
        
}

std::unique_ptr<syntax_node> transform_ast(
                const std::unique_ptr<syntax_node> syntax_node)
{
        return transform_compile_unit(syntax_node);
}

} // namespace kehu::ast
