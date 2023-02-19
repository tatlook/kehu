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

#include <exception>
#include <assert.h>
#include <stdexcept>

#include <kehu/ast.h>

namespace kehu::ast
{

using namespace token;
using std::string;
using std::vector;

static bool is_variable(const Token &t)
{
        if (t.type != TOKEN_IDENTIFIER)
                return false;
        const string &s = std::get<string>(t.value);
        if (s.size() < 2)
                return false;
        if (s.at(0) == '$')
                return true;
        return false;
}

// static void require_period(vector<Token>::const_iterator &t,
//                 const vector<Token>::const_iterator &end)
// {
//         if (t == end)
//                 throw syntax_error("unexpected ending", t[-1]);
//         if (*t != '.')
//                 throw syntax_error("expected '.', not " + (string) *t);
//         ++t;
// }

static std::unique_ptr<variable_reference_node> read_variable(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        assert(is_variable(*t));
        auto var = std::make_unique<variable_reference_node>();
        var->name = std::get<string>(t->value);
        return var;
}

static std::unique_ptr<block_node> read_block(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end);

static std::unique_ptr<primeval_statement_node> read_primeval_statement(
                vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        auto primeval = std::make_unique<primeval_statement_node>();
        while (true) {
                if (t == end)
                        throw syntax_error("unexpected ending", t[-1]);
                if (*t == '.')
                        break;
                if (*t == "{@") {
                        auto block_node = read_block(t, end);
                        primeval->lex.push_back(std::move(block_node));
                        continue;
                }
                if (is_variable(*t)) {
                        auto variable = read_variable(t, end);
                        primeval->lex.push_back(std::move(variable));
                        continue;
                }
                if (t->type == TOKEN_IDENTIFIER) {
                        std::string s = std::get<std::string>(t->value);
                        primeval->lex.push_back(s);
                        continue;
                }
                ++t;
        }
        ++t;
        return primeval;
}

static std::unique_ptr<block_node> read_block(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        assert(*t == "@{");
        auto block = std::make_unique<block_node>();
        while (true) {
                ++t;
                if (t == end)
                        throw syntax_error("unexpected ending", t[-1]);
                if (*t == '.')
                        continue;
                if (*t == "@}") {
                        break;
                }
                block->statements.push_back(read_primeval_statement(t, end));
        }
        ++t;
        return block;
}

// static std::unique_ptr<function_definition_node> read_function(vector<Token>::const_iterator &t,
//                 const vector<Token>::const_iterator &end)
// {
//         if ( ! (t->type == TOKEN_IDENTIFIER 
//                         && std::get<string>(t->value) == "@define")) {
//                 throw syntax_error("only function definitions are alowed", *t);
//         }
//         ++t;
//         auto function = std::make_unique<function_definition_node>();
//         //vector<std::variant<string, std::unique_ptr<variable_reference_node>>> lex;
//         for ( ;; ++t) {
//                 if (t == end)
//                         throw syntax_error("unexpected ending", t[-1]);
//                 if (*t == '.')
//                         throw syntax_error("vv");
//                 if (*t == "@{") {
//                         break;
//                 }
//                 if (is_variable(*t)) {
//                         auto var = read_variable(t, end);
//                         function->lex.push_back(std::move(var));
//                 } else if (t->type == TOKEN_IDENTIFIER) {
//                         function->lex.push_back(std::get<string>(t->value));
//                 }
//         }
//         if (function->lex.empty())
//                 throw syntax_error("bb");
//         function->block = std::move(read_block(t, end));
//         return function;
// }

static std::unique_ptr<syntax_node> read_compile_unit(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        auto file = std::make_unique<file_node>();
        while (t != end) {
                file->global_definitions.push_back(read_primeval_statement(t, end));
        }
        return file;
}

std::unique_ptr<syntax_node> parse_primeval_ast(const std::vector<token::Token> &tokens)
{
        vector<Token>::const_iterator t = tokens.begin();
        vector<Token>::const_iterator end = tokens.end();
        return read_compile_unit(t, end);
}

} // namespace kehu::ast

