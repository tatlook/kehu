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
using kehu::diagnostic::location;
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

static std::shared_ptr<value_node> read_raw_char(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if (t->type != TOKEN_CHAR)
                diagnostic::report("incomprehensible token", *t);
        auto rawvalue = std::make_shared<raw_char_node>();
        rawvalue->value = std::get<char>(t->value);
        rawvalue->location = t->location;
        ++t;
        return rawvalue;
}

static std::shared_ptr<value_node> read_raw_string(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if (t->type != TOKEN_STRING)
                throw read_raw_char(t, end);
        auto rawvalue = std::make_shared<raw_string_node>();
        rawvalue->value = std::get<std::string>(t->value);
        rawvalue->location = t->location;
        ++t;
        return rawvalue;
}

static std::shared_ptr<value_node> read_raw_integer(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if (t->type != TOKEN_INTEGER)
                return read_raw_string(t, end);
        auto rawvalue = std::make_shared<raw_integer_node>();
        rawvalue->value = std::get<signed long>(t->value);
        rawvalue->location = t->location;
        ++t;
        return rawvalue;
}

static std::shared_ptr<value_node> read_word(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if (t->type != TOKEN_IDENTIFIER)
                return read_raw_integer(t, end);
        auto word = std::make_shared<word_node>();
        word->word = std::get<string>(t->value);
        word->location = t->location;
        ++t;
        return word;
}

static bool is_type(const Token &t)
{
        if (t.type != TOKEN_IDENTIFIER)
                return false;
        const string &s = std::get<string>(t.value);
        if (s.size() < 2)
                return false;
        if (s.at(0) == '%')
                return true;
        return false;
}

static std::shared_ptr<value_node> read_type(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if ( ! is_type(*t))
                return read_word(t, end);
        auto type = std::make_shared<type_node>();
        type->name = std::get<string>(t->value);
        type->location = t->location;
        ++t;
        return type;
}

static std::shared_ptr<value_node> read_variable(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if ( ! is_variable(*t))
                return read_type(t, end);
        auto var = std::make_shared<variable_reference_node>();
        var->name = std::get<string>(t->value);
        var->location = t->location;
        ++t;
        return var;
}

static std::shared_ptr<tiled_statement_node> read_tiled_statement(
                vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end);

static std::shared_ptr<value_node> read_tiled_block(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        if (*t != "{") 
                return read_variable(t, end);
        location begin = t->location;
        ++t;
        auto block = std::make_shared<tiled_block_node>();
        while (true) {
                if (t == end)
                        diagnostic::report("unexpected ending", t[-1]);
                if (*t == '.') {
                        ++t;
                        continue;
                }
                if (*t == "}")
                        break;
                block->statements.push_back(read_tiled_statement(t, end));
        }
        block->location = t->location + begin;
        ++t;
        return block;
}

static std::shared_ptr<tiled_statement_node> read_tiled_statement(
                vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        auto primeval = std::make_shared<tiled_statement_node>();
        location begin = t->location;
        while (true) {
                if (t == end)
                        diagnostic::report("unexpected ending", t[-1]);
                if (*t == '.')
                        break;
                auto value_node = read_tiled_block(t, end);
                primeval->lex.push_back(value_node);
        }
        primeval->location = t->location + begin;
        ++t;
        return primeval;
}

static std::shared_ptr<tiled_block_node> read_root_block(vector<Token>::const_iterator &t,
                const vector<Token>::const_iterator &end)
{
        auto root = std::make_shared<tiled_block_node>();
        while (t != end) {
                root->statements.push_back(read_tiled_statement(t, end));
        }
        return root;
}

std::shared_ptr<tiled_block_node> parse_primeval_ast(
                const std::vector<token::Token> &tokens)
{
        vector<Token>::const_iterator t = tokens.begin();
        vector<Token>::const_iterator end = tokens.end();
        return read_root_block(t, end);
}

} // namespace kehu::ast

