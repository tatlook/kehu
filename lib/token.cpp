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

Token::operator std::string() const
{
        switch (type) {
        case TOKEN_IDENTIFIER:
                return std::get<std::string>(value);
        case TOKEN_SYMBOL:
                return std::string(1, std::get<char>(value));
        case TOKEN_INTEGER:
                return std::to_string(std::get<signed long>(value));
        default:
                throw std::logic_error("Token type out of enum: " 
                                + std::to_string((int) type));
        }
}

} // namespace kehu::token
