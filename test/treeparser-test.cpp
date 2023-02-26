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
#include <tiled_parse.cpp>

using namespace kehu::ast;
using namespace kehu::token;

static vector<Token> make_tokens() {
        return tokenize({
                "@d v $2 k @{ @}."
        });
}

TEST(TreeParser, TreePa) {
        vector<Token> tokens = make_tokens();
        std::unique_ptr<kehu::ast::syntax_node> ast = parse_primeval_ast(tokens);
        std::ofstream of;
        of.open("k.ll");
        of << ast->generate_kehu_code();
}
