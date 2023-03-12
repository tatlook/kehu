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

#include <gtest/gtest.h>
#include <fstream>
#include <parse_tiled.cpp>
#include <typeinfo>

using namespace kehu::ast;
using namespace kehu::token;

TEST(ParseTiled, ReadRawString)
{
        const vector<Token> tokens = tokenize({
                "\"yes\""
        });
        auto t = tokens.begin();
        auto ast = read_raw_string(t, tokens.end());
        ASSERT_EQ(typeid(*ast), typeid(raw_string_node));
        auto string = std::static_pointer_cast<raw_string_node>(ast);
        ASSERT_EQ(string->value, "yes");
}

TEST(ParseTiled, ReadStatment)
{
        const vector<Token> tokens = tokenize({
                "yes $ze."
        });
        auto t = tokens.begin();
        auto statement = read_tiled_statement(t, tokens.end());
        ASSERT_EQ(statement->lex.size(), 2);
        ASSERT_EQ(typeid(*(statement->lex[0])), typeid(word_node));
        ASSERT_EQ(typeid(*(statement->lex[1])), typeid(variable_reference_node));
}

TEST(ParseTiled, ReadBlock)
{
        const vector<Token> tokens = tokenize({
                "@{ yes. @}."
        });
        auto t = tokens.begin();
        auto ast = read_tiled_block(t, tokens.end());
        ASSERT_EQ(typeid(*ast), typeid(tiled_block_node));
        auto block = std::static_pointer_cast<tiled_block_node>(ast);
        ASSERT_EQ(block->statements.size(), 1);
        const vector<Token> statement_tokens = tokenize({
                "yes."
        });
        t = statement_tokens.begin();
        auto statement = read_tiled_statement(t, tokens.end());
        ASSERT_EQ(*block->statements[0], *statement);
}

TEST(ParseTiled, TreePa)
{
        vector<Token> tokens = tokenize({
                "@d v $2 k @{ @}."
        });
        auto ast = parse_primeval_ast(tokens);
        std::ofstream of;
        of.open("k.ll");
        of << ast->generate_kehu_code();
}
