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


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <vector>

#include <kehu/ast.h>
#include <kehu/token.h>

using namespace kehu;
using std::vector;
using std::string;

vector<string> read_source(std::istream &source)
{
        vector<string> lines;
        while ( ! source.eof()) {
                string line;
                std::getline(source, line);
                lines.push_back(line);
        }
        return lines;
}

int main(int argc, char const *argv[])
{
        if (argc < 3) {
                std::cout << "Kehu - a toe language" << std::endl
                        << "Copyright (C) 2023 Zhen You Zhe" << std::endl
                        << "Usage: " << argv[0] << " [source] [target]" << std::endl;
                return 0;
        }
        std::ifstream source;
        source.open(argv[1]);

        if ( ! source) {
                perror(argv[1]);
                return errno;
        }
        std::vector<token::Token> tokens;
        try {
                tokens = token::tokenize(read_source(source));
        } catch (const token::token_exception &e) {
                std::cerr << e.what() << '\n';
                return 1;
        }
        

        std::ofstream target;
        target.open(argv[2]);

        if ( ! target) {
                perror(argv[0]);
                return errno;
        }
        for (const token::Token &t : tokens) {
                target << (string) t << " " << t.linec << std::endl;
        }

        std::unique_ptr<ast::syntax_node> ast;
        try {
                ast.reset(ast::parse_primeval_ast(tokens).release());
        } catch (ast::syntax_error &e) {
                token::Token t = e.get_error_token();
                if (t.linec != 0) {
                        std::cerr << std::to_string(t.linec) << ": ";
                }
                std::cerr << e.what();
                if (t.linec != 0) {
                        std::cerr << std::endl << "\t" << std::to_string((int) t.type)
                                << (string) t << std::endl;
                }
                return 1;
        }
        target << ast->generate_kehu_code();
        target.close();

        return 0;
}

