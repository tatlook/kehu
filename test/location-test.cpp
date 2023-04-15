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
        location loc1 = location(2, 2, 2, 2);
        location loc2 = location(2, 2, 3, 2);
        location loc3 = location(2, 2, 3, 2);
        EXPECT_NE(loc1, loc2);
        EXPECT_EQ(loc2, loc3);
        EXPECT_EQ(loc1, location::somewhere);
        EXPECT_EQ(loc2, location::somewhere); 
}

TEST(location, operator_plus)
{
        location loc1 = location(2, 2, 2, 2);
        location loc2 = location(2, 2, 3, 2);
        location expect = location(2, 2, 3, 2);
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = location(6, 2, 10, 2);
        loc2 = location(2, 2, 3, 2);
        expect = location(2, 2, 10, 2);
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = location(6, 9, 10, 2);
        loc2 = location(2, 2, 3, 2);
        expect = location(2, 2, 10, 2);
        EXPECT_EQ(expect, loc1 + loc2);
        loc1 = location(1, 1, 2, 1);
        loc2 = location(5, 2, 8, 2);
        expect = location(1, 1, 8, 2);
        EXPECT_EQ(expect, loc1 + loc2);
}
