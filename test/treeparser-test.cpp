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

#include <kehu/dump.h>
#include <gtest/gtest.h>
#include <fstream>
#include <parse_tiled.cpp>
#include <typeinfo>

using namespace kehu::ast;
using namespace kehu::token;
using namespace kehu;

TEST(ParseTiled, ReadType)
{
        const vector<Token> tokens = tokenize({
                "%type-name+yes"
        });
        auto t = tokens.begin();
        auto ast = read_type(t, tokens.end());
        ASSERT_EQ(typeid(*ast), typeid(type_node));
        auto string = std::static_pointer_cast<type_node>(ast);
        ASSERT_EQ(string->get_name(), "%type-name+yes");
}

TEST(ParseTiled, ReadRawString)
{
        const vector<Token> tokens = tokenize({
                "\"yes\""
        });
        auto t = tokens.begin();
        auto ast = read_raw_string(t, tokens.end());
        ASSERT_EQ(typeid(*ast), typeid(string_literal_node));
        auto string = std::static_pointer_cast<string_literal_node>(ast);
        ASSERT_EQ(string->get_value(), "yes");
}

TEST(ParseTiled, ReadStatment)
{
        const vector<Token> tokens = tokenize({
                "yes $ze."
        });
        auto t = tokens.begin();
        auto statement = read_tiled_statement(t, tokens.end());
        ASSERT_EQ(statement->get_lex().size(), 2);
        ASSERT_EQ(typeid(*(statement->get_lex()[0])), typeid(word_node));
        ASSERT_EQ(typeid(*(statement->get_lex()[1])), typeid(variable_node));
}

TEST(ParseTiled, ReadBlock)
{
        const vector<Token> tokens = tokenize({
                "{ yes. }."
        });
        auto t = tokens.begin();
        auto ast = read_tiled_block(t, tokens.end());
        ASSERT_EQ(typeid(*ast), typeid(tiled_block_node));
        auto block = std::static_pointer_cast<tiled_block_node>(ast);
        ASSERT_EQ(block->get_statements().size(), 1);
        const vector<Token> statement_tokens = tokenize({
                "yes."
        });
        t = statement_tokens.begin();
        auto statement = read_tiled_statement(t, tokens.end());
        ASSERT_EQ(*block->get_statements()[0], *statement);
}

TEST(ParseTiled, TreePa)
{
        vector<Token> tokens = tokenize({
                "@d v $2 k { }."
        });
        auto ast = parse_tiled_tree(tokens);
        std::ofstream of;
        of.open("k.ll");
        of << dump::dump(*ast);
}
