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

#include <tokenize.cpp>
#include <token.cpp>

using namespace kehu::token;
using kehu::diagnostic::location;

using std::string;
using std::vector;

TEST(TokenizerTest, ReadSymbol)
{
        string s = "(.v g";
        string::const_iterator c = s.begin();
        Token token = read_symbol(c, s.end());
        ASSERT_EQ(token.type, TOKEN_SYMBOL);
        ASSERT_EQ(std::get<char>(token.value), '(');
}

TEST(TokenizerTest, ReadIdentifier)
{
        string s = "saata{^7&na34*}. vg";
        string::const_iterator c = s.begin();
        Token token = read_identifier(c, s.end());
        ASSERT_EQ(token.type, TOKEN_IDENTIFIER);
        ASSERT_EQ(std::get<string>(token.value), "saata{^7&na34*}");
}

TEST(TokenizerTest, ReadNumber)
{
        string s = "0xFFcc93q0/\\,*&";
        string::const_iterator c = s.begin();
        Token token = read_number(c, s.end());
        ASSERT_EQ(token.type, TOKEN_INTEGER);
        ASSERT_EQ(std::get<signed long>(token.value), 0xFFcc93);
        s = "07073 q0/\\,*&";
        c = s.begin();
        token = read_number(c, s.end());
        ASSERT_EQ(token.type, TOKEN_INTEGER);
        ASSERT_EQ(std::get<signed long>(token.value), 07073);
#if 0 // TODO: support binary
        s = "0b1000101v7073q0/\\,*&";
        c = s.begin();
        token = read_number(c, s.end());
        ASSERT_EQ(token.type, TOKEN_INTEGER);
        ASSERT_EQ(std::get<signed long>(token.value), 0b1000101);
#endif
}

TEST(TokenizerTest, ReadCharSection)
{
        string s = "\\n";
        string::const_iterator c = s.begin();
        char chr = read_char_section(c, s.end());
        ASSERT_EQ(chr, '\n');
        ASSERT_EQ(c, s.end());
        s = "n";
        c = s.begin();
        chr = read_char_section(c, s.end());
        ASSERT_EQ(chr, 'n');
        ASSERT_EQ(c, s.end());
}

TEST(TokenizerTest, ReadChar)
{
        string s = "'\\n'";
        string::const_iterator c = s.begin();
        Token token = read_char(c, s.end());
        ASSERT_EQ(token.type, TOKEN_CHAR);
        ASSERT_EQ(std::get<char>(token.value), '\n');   
        ASSERT_EQ(c, s.end());
        s = "'n'";
        c = s.begin();
        token = read_char(c, s.end());
        ASSERT_EQ(token.type, TOKEN_CHAR);
        ASSERT_EQ(std::get<char>(token.value), 'n');   
        ASSERT_EQ(c, s.end());
}

TEST(TokenizerTest, ReadString)
{
        string s = "\"voi*\\\"*\\n \\t#\"";
        string::const_iterator c = s.begin();
        Token token = read_string(c, s.end());
        ASSERT_EQ(token.type, TOKEN_STRING);
        ASSERT_EQ(std::get<std::string>(token.value), "voi*\"*\n \t#");
}

TEST(TokenizerTest, LineTokens)
{
        string line = "voi saatana 88, 6   $kk @inline ";
        vector<Token> expect;
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_IDENTIFIER,
                .value = "voi"
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_IDENTIFIER,
                .value = "saatana"
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_INTEGER,
                .value = 88L
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_SYMBOL,
                .value = ','
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_INTEGER,
                .value = 6L
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_IDENTIFIER,
                .value = "$kk"
        });
        expect.push_back({
                .location = location::somewhere,
                .type = TOKEN_IDENTIFIER,
                .value = "@inline"
        });
        const vector<Token> &actual = tokenize_line(0, line);
        ASSERT_EQ(expect.size(), actual.size());
        for (int i = 0; i < expect.size(); i++) {
                EXPECT_EQ(expect.at(i), actual.at(i));
        }
}
