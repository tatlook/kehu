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

static bool match_firsts_of_lex(const std::shared_ptr<tiled_statement_node> node,
                std::initializer_list<std::string> lex)
{
        if (node->lex.size() < lex.size())
                return false;
        auto l = lex.begin();
        for (int i = 0; i < node->lex.size(); i++, ++l) {
                if (node->lex[i]->generate_kehu_code() != *l)
                        return false;
        }
        return true;
}

static std::shared_ptr<executable_statement_node> transform_executable_statement(
                const std::shared_ptr<tiled_statement_node> node)
{
        auto st = std::make_shared<executable_statement_node>();

        // TODO

        return st;
}

static std::shared_ptr<executable_block_node> transform_executable_block(
                const std::shared_ptr<tiled_block_node> node)
{
        auto exb = std::make_shared<executable_block_node>();
        for (auto st1 : node->statements) {
                auto st2 = transform_executable_statement(st1);
                exb->statements.push_back(st2);
        }
        return exb;
}

static std::shared_ptr<definition_node> transform_global_variable_definition(
                const std::shared_ptr<tiled_statement_node> node)
{
        if ( ! match_firsts_of_lex(node, { "define", "variable" }))
                throw syntax_error("of piru"); // TODO
        if (node->lex.size() < 4
                        || typeid(*node->lex[2])
                        != typeid(type_node)
                        || typeid(*node->lex[3])
                        != typeid(variable_reference_node))
                throw syntax_error("expected variable name");
        auto var = std::make_shared<variable_definition_node>();
        var->type = std::static_pointer_cast<type_node>(node->lex[2]);
        var->variable = std::static_pointer_cast
                        <variable_reference_node>(node->lex[3]);
        return var;
}

static std::shared_ptr<definition_node> transform_function_definition(
                const std::shared_ptr<tiled_statement_node> node)
{
        if ( ! match_firsts_of_lex(node, { "define", "function" }))
                return transform_global_variable_definition(node);
        if (typeid(node->lex.back()) != typeid(tiled_block_node))
                throw syntax_error("missing function body");

        auto fn = std::make_shared<function_definition_node>();
        
        auto &&l = node->lex.begin();
        l += 2;
        for ( ; l != (node->lex.end() - 1); ++l) {
                fn->lex.push_back(*l); // TODO: parameter and type not word
        }
        fn->block = transform_executable_block(
                std::static_pointer_cast<tiled_block_node>(node->lex.back()));
        return fn;
}

static std::shared_ptr<definition_node> transform_global_definition(
                const std::shared_ptr<tiled_statement_node> st)
{
        return transform_function_definition(st);
}

static std::shared_ptr<compile_unit_node> transform_compile_unit(
                const std::shared_ptr<tiled_block_node> root)
{
        auto cu = std::make_shared<compile_unit_node>();
        for (const auto node : root->statements) {
                cu->statements.push_back(transform_global_definition(node));
        }
        return cu;
}

std::shared_ptr<compile_unit_node> transform_ast(
                const std::shared_ptr<tiled_block_node> syntax_node)
{
        return transform_compile_unit(syntax_node);
}

} // namespace kehu::ast
