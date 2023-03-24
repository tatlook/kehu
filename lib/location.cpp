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

#include <kehu/diagnostic.h>

#include <stdexcept>
#include <ostream>

namespace kehu::diagnostic
{


const location location::somewhere = {
        .first_linec = -1,
        .first_charc = -1,
        .last_linec = -1,
        .last_charc = -1,
};


location location::operator+(const location &other) const
{
        location result;
        if (this->first_linec > other.first_linec) {
                result.first_linec = other.first_linec;
                result.first_charc = other.first_charc;
        } else if (this->first_linec < other.first_linec) {
                result.first_linec = this->first_linec;
                result.first_charc = this->first_charc;
        } else { // if (this->first_linec < other.first_linec)
                result.first_linec = other.first_linec;
                if (other.first_charc > this->first_charc)
                        result.first_charc = this->first_charc;
                else
                        result.first_charc = other.first_charc;
        }
        if (this->last_linec < other.last_linec) {
                result.last_linec = other.last_linec;
                result.last_charc = other.last_charc;
        } else if (this->last_linec > other.last_linec) {
                result.last_linec = this->last_linec;
                result.last_charc = this->last_charc;
        } else { // if (this->last_linec < other.last_linec)
                result.last_linec = other.last_linec;
                if (other.last_charc < this->last_charc)
                        result.last_charc = this->last_charc;
                else
                        result.last_charc = other.last_charc;
        }
        return result;
}

static bool equals(const location &loc1, const location &loc2)
{
        return loc1.first_linec == loc2.first_linec
                && loc1.first_charc == loc2.first_charc
                && loc1.last_linec == loc2.last_linec
                && loc1.last_charc == loc2.last_charc;
}

bool location::operator==(const location &other) const
{
        if (equals(*this, somewhere) || equals(other, somewhere))
                return true;
        return equals(*this, other);
}

std::ostream &operator<<(std::ostream &out, const location &loc)
{
        return out << loc.first_linec << ':' << loc.first_charc
                << " - "
                << loc.last_linec << ':' << loc.last_charc;
}

} // namespace kehu::diagnostic

