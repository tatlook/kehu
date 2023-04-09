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
#include <kehu/token.h>

using namespace kehu::token;
using kehu::diagnostic::location;

TEST(Token, OperatorEquals)
{
        Token t1 = {
                .type = TOKEN_CHAR,
                .value = '"',
        };
        Token t2 = {
                .location = location::somewhere,
                .type = TOKEN_CHAR,
                .value = '"',
        };
        ASSERT_TRUE(t1 == t2);
        ASSERT_FALSE(t1 != t2);
        t2 = {
                .location = location::somewhere,
                .type = TOKEN_STRING,
                .value = "\"",
        };
        ASSERT_FALSE(t1 == t2);
        ASSERT_TRUE(t1 != t2);
}

TEST(Token, ToString)
{
        Token t = {
                .location = location::somewhere,
                .type = TOKEN_INTEGER,
                .value = '"',
        };
        ASSERT_THROW(to_string(t),
                        std::bad_variant_access);
        t = {
                .location = location::somewhere,
                .type = TOKEN_CHAR,
                .value = '"',
        };
        ASSERT_EQ(to_string(t), "'\"'");
        t = {
                .location = location::somewhere,
                .type = TOKEN_STRING,
                .value = "voi saatana",
        };
        ASSERT_EQ(to_string(t), "\"voi saatana\"");
        t = {
                .location = location::somewhere,
                .type = TOKEN_IDENTIFIER,
                .value = "voi saatana",
        };
        ASSERT_EQ(to_string(t), "voi saatana");
        t = {
                .location = location::somewhere,
                .type = TOKEN_INTEGER,
                .value = 3000L,
        };
        ASSERT_EQ(to_string(t), "3000");
        t = {
                .location = location::somewhere,
                .type = TOKEN_SYMBOL,
                .value = ',',
        };
        ASSERT_EQ(to_string(t), ",");
}
