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

#if !defined(_TOKEN_H)
#define _TOKEN_H

#include <vector>
#include <string>
#include <variant>
#include <stdexcept>

namespace kehu::token
{

enum token_type
{
        TOKEN_IDENTIFIER,
        TOKEN_SYMBOL,
        TOKEN_INTEGER,
        TOKEN_STRING,
        TOKEN_CHAR,
};


struct Token
{
        int linec; /* where do token found */
        enum token_type type;
        std::variant<double, signed long, std::string, char> value;
        bool operator==(const Token &t2) const;
        bool operator==(const std::variant<double, signed long, std::string, char> value) const;
        bool operator!=(const Token &t2) const {
                return ! (*this == t2);
        }
        bool operator!=(const std::variant<double, signed long, std::string, char> value) const {
                return ! (*this == value);
        }
};

std::ostream &operator<<(std::ostream &out, const Token &t);
std::string to_string(const Token &t);

const std::vector<Token> &tokenize(
                const std::vector<std::string> &original_lines);


class token_exception : public std::runtime_error
{
public:
        explicit token_exception(const std::string &message) : std::runtime_error(message) 
        {}
};
        
} // namespace pncl::token

#endif // _TOKEN_H
