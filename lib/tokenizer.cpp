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

#include <cctype>
#include <string>
#include <vector>

#include <kehu/token.h>

namespace kehu::token
{

static bool is_symbol(char c)
{
        switch (c) {
        case ',':
        case '(':
        case ')':
        case '.':
                return true;
        }
        return false;
}

static bool is_identifier_char(char c)
{
        if (is_symbol(c))
                return false;
        if (std::isspace(c))
                return false;
        return true;
}

static Token read_identifier(std::string::const_iterator &c, 
                const std::string::const_iterator &end)
{
        if (is_identifier_char(*c)) {
                std::string value;
                for ( ; c != end && is_identifier_char(*c); ++c) {
                        value += *c;
                }
                --c;
                Token token = {};
                token.type = TOKEN_IDENTIFIER;
                token.value = value;
                return token;
        }
        throw token_exception("Unknown token/char");
}

static Token read_number(std::string::const_iterator &c, 
                const std::string::const_iterator &end)
{
        // int base = 10;
        // if (std::isdigit(*c)) {
        //     /* '0x', '0b', '0o' */
        //     if (*c == '0') {
        //         ++c;
        //         switch (*c) {
        //             case 'o':
        //                 base = 8;
        //                 break;
        //             case 'x':
        //                 base = 6;
        //                 break;
        //             case 'b':
        //                 base = 2;
        //                 break;
        //             default:
        //                 --c;
        //         }
        //         ++c;
        //     }
        //     std::string value;
        //     for ( ; is_identifier_char(*c); ++c) {
        //         value += *c;
        //     }
        //     --c;
        //     
        // }
        if (std::isdigit(*c)) {
                std::string value;
                for ( ; c != end && is_identifier_char(*c); ++c) {
                        value += *c;
                }
                --c;
                long number = std::stol(value, nullptr, 0);
                Token token = {};
                token.type = TOKEN_INTEGER;
                token.value = number;
                return token;
        }
        return read_identifier(c, end);
}

static Token read_symbol(std::string::const_iterator &c, 
                const std::string::const_iterator &end)
{
        if (is_symbol(*c)) {
                Token token = {};
                token.type = TOKEN_SYMBOL;
                token.value = *c;
                return token;
        }
        return read_number(c, end);
}

class string_eof {
};

static Token read_token_after_spaces(std::string::const_iterator &c, 
                const std::string::const_iterator &end)
{
        while (true) {
                if (c == end)
                        throw string_eof();
                if ( ! std::isspace(*c))
                        return read_symbol(c, end);
                ++c;
        }
}

static std::string take_down_comments(const std::string &s)
{
        int index = s.find_first_of('#');
        /* if we have not '#' in the std::string */
        if (index == s.npos)
                return s;
        return s.substr(0, index);
}

/**
 * Returns all tokens of this line
 */
static std::vector<Token> tokenize_line(int linec, const std::string &line)
{
        std::vector<Token> line_tokens;
        for (std::string::const_iterator c = line.begin(); c != line.end(); ++c) {
                try {
                        Token token = read_token_after_spaces(c, line.end());
                        token.linec = linec;
                        line_tokens.push_back(token);
                } catch (string_eof) {
                        break;
                }
        }
        return line_tokens;
}

const std::vector<Token> &tokenize(const std::vector<std::string> &original_lines)
{
        int linec = 1;
        std::vector<Token> *tokens = new std::vector<Token>();
        for (const std::string &original_line : original_lines) {
                const std::string &uncommented_line = take_down_comments(original_line);
                const std::vector<Token> &line_tokens = tokenize_line(linec, uncommented_line);
                tokens->insert(tokens->end(), line_tokens.begin(), line_tokens.end());
                linec++;
        }
        return *tokens;
}

} // namespace kehu::token

