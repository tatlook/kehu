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
#include <kehu/dump.h>

namespace kehu::ast
{

static bool match_firsts_of_lex(std::shared_ptr<const tiled_statement_node> node,
                std::initializer_list<std::string> lex)
{
        if (node->get_lex().size() < lex.size())
                return false;
        auto cmpl = lex.begin();
        auto nodel = node->get_lex().begin();
        while (cmpl != lex.end()) {
                if (dump::dump(**nodel) != *cmpl)
                        return false;
                ++cmpl;
                ++nodel;
        }
        return true;
}

static std::shared_ptr<expression_node> transform_expression(
                std::shared_ptr<const tiled_statement_node> node);

static auto function_parameter_placeholder = std::make_shared<word_node>("#");

static std::shared_ptr<expression_node> transform_function_call(
                std::shared_ptr<const tiled_statement_node> node)
{
        std::vector<std::shared_ptr<const tiled_element_node>> funcd;
        std::vector<std::shared_ptr<const expression_node>> args;
        for (auto l : node->get_lex()) {
                if (l->is_expression()) {
                        args.push_back(std::dynamic_pointer_cast
                                        <expression_node>(l));
                }
                funcd.push_back(function_parameter_placeholder);
        }
        auto func_call = std::make_shared<function_call_node>(funcd, args);
        return func_call;
}

static std::shared_ptr<expression_node> transform_expression(
                std::shared_ptr<const tiled_statement_node> node)
{
        return transform_function_call(node);
}

static std::shared_ptr<executable_statement_node> transform_executable_statement(
                std::shared_ptr<const tiled_statement_node> node)
{
        auto st = std::make_shared<executable_statement_node>
                        (transform_expression(node));
        return st;
}

static std::shared_ptr<executable_block_node> transform_executable_block(
                std::shared_ptr<const tiled_block_node> node)
{
        auto exb = std::make_shared<executable_block_node>();
        for (auto st1 : node->statements) {
                auto st2 = transform_executable_statement(st1);
                exb->statements.push_back(st2);
        }
        return exb;
}

static std::shared_ptr<definition_node> transform_global_variable_definition(
                std::shared_ptr<const tiled_statement_node> node)
{
        if ( ! match_firsts_of_lex(node, { "define", "variable" }))
                diagnostic::report("of piru", *node); // TODO
        if (node->get_lex().size() < 4
                        || ( ! node->get_lex()[2]->is_type())
                        || ( ! node->get_lex()[3]->is_variable()))
                diagnostic::report("expected variable name", *node);
        auto var = std::make_shared<variable_definition_node>(
                        std::static_pointer_cast<type_node>(node->get_lex()[2]),
                        std::static_pointer_cast<variable_node>(node->get_lex()[3])
                        );
        return var;
}

static std::shared_ptr<definition_node> transform_function_definition(
                std::shared_ptr<const tiled_statement_node> node)
{
        if ( ! match_firsts_of_lex(node, { "define", "function" }))
                return transform_global_variable_definition(node);
        auto l = node->get_lex().begin();
        l += 2;
        std::vector<std::shared_ptr<const tiled_element_node>> fnlex;
        for ( ; l != (node->get_lex().end() - 1); ++l) {
                if ((*l)->is_type()) {
                        if ((l + 1) == node->get_lex().end()
                                        || ! (l[1])->is_variable())
                                diagnostic::report("Variable is expected", **l);
                        fnlex.push_back(function_parameter_placeholder);
                }
                fnlex.push_back(*l);
        }
        if ( ! node->get_lex().back()->is_block())
                diagnostic::report("missing function body", *node);
        auto block = transform_executable_block(
                        std::static_pointer_cast<tiled_block_node>
                        (node->get_lex().back()));
        auto fn = std::make_shared<function_definition_node>(fnlex, block);
        return fn;
}

static std::shared_ptr<definition_node> transform_global_definition(
                std::shared_ptr<const tiled_statement_node> st)
{
        return transform_function_definition(st);
}

static std::shared_ptr<compile_unit_node> transform_compile_unit(
                std::shared_ptr<const tiled_block_node> root)
{
        auto cu = std::make_shared<compile_unit_node>();
        for (const auto node : root->statements) {
                cu->statements.push_back(transform_global_definition(node));
        }
        return cu;
}

std::shared_ptr<compile_unit_node> transform_ast(
                std::shared_ptr<const tiled_block_node> syntax_node)
{
        return transform_compile_unit(syntax_node);
}

} // namespace kehu::ast
