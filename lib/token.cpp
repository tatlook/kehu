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

#include <kehu/token.h>
#include <stdexcept>
#include <ostream>
#include <sstream>

namespace kehu::token
{

bool Token::operator==(const Token &t2) const
{
        if (t2.linec != this->linec)
                return false;
        if (t2.type != this->type)
                return false;
        if (t2.value != this->value)
                return false;
        return true;
}

bool Token::operator==(const std::variant
                <double, signed long, std::string, char> value) const
{
        return value == this->value;
}

std::string to_string(const Token &t)
{
        std::ostringstream out;
        out << t;
        return out.str();
}

std::ostream &operator<<(std::ostream &out, const Token &t)
{
        switch (t.type) {
        case TOKEN_IDENTIFIER:
                return out << std::get<std::string>(t.value);
        case TOKEN_SYMBOL:
                return out << std::get<char>(t.value);
        case TOKEN_INTEGER:
                return out << std::get<signed long>(t.value);
        case TOKEN_STRING:
                return out << '"' << std::get<std::string>(t.value) << '"';
        case TOKEN_CHAR:
                return out << '\'' << std::get<char>(t.value) << '\'';
        default:
                throw std::logic_error("Token type out of enum: " 
                                + std::to_string((int) t.type));
        }
}

} // namespace kehu::token
