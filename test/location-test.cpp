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

#include <kehu/diagnostic.h>

using namespace kehu::diagnostic;

TEST(location, operator_equal)
{
        location loc1 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 2,
                .last_charc = 2,
        };
        location loc2 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        location loc3 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        EXPECT_NE(loc1, loc2);
        EXPECT_EQ(loc2, loc3);
        EXPECT_EQ(loc1, location::somewhere);
        EXPECT_EQ(loc2, location::somewhere); 
}

TEST(location, operator_plus)
{
        location loc1 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 2,
                .last_charc = 2,
        };
        location loc2 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        location expect = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = {
                .first_linec = 6,
                .first_charc = 2,
                .last_linec = 10,
                .last_charc = 2,
        };
        loc2 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        expect = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 10,
                .last_charc = 2,
        };
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = {
                .first_linec = 6,
                .first_charc = 9,
                .last_linec = 10,
                .last_charc = 2,
        };
        loc2 = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 3,
                .last_charc = 2,
        };
        expect = {
                .first_linec = 2,
                .first_charc = 2,
                .last_linec = 10,
                .last_charc = 2,
        };
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = {
                .first_linec = 1,
                .first_charc = 1,
                .last_linec = 2,
                .last_charc = 1,
        };
        loc2 = {
                .first_linec = 5,
                .first_charc = 2,
                .last_linec = 8,
                .last_charc = 2,
        };
        expect = {
                .first_linec = 1,
                .first_charc = 1,
                .last_linec = 8,
                .last_charc = 2,
        };
        EXPECT_EQ(expect, loc1 + loc2);
}
