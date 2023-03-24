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

#if !defined(_KEHU_DIAGNOSTIC_H)
#define _KEHU_DIAGNOSTIC_H

#include <ostream>
#include <string>

namespace kehu::diagnostic
{

/**
 * @brief location of a code fragment
 * Describes 
 * 
 * @author Zhen You Zhe
 */
struct location
{
        /**
         * @brief the location of somewhere
         * Expression <tt>somewhere == other</tt> is always true.
         * 
         * @see operator==
         */
        static const location somewhere;

        /**
         * @brief count of the first line of @c location
         */
        int first_linec;

        /**
         * @brief count of the first char of first line
         */
        int first_charc;

        /**
         * @brief count of the last line of @c location
         */
        int last_linec;

        /**
         * @brief count of the last char of last line
         */
        int last_charc;

        /**
         * @brief Joins two locations
         * Returns a new location, which have two locations and the place between
         * @c this and @c other. 
         * 
         * @param other the other location to join
         * 
         * @return a new location
         */
        location operator+(const location &other) const;

        bool operator==(const location &other) const;

        bool operator!=(const location &other) const
        {
                return ! (*this == other);
        }
};

std::ostream &operator<<(std::ostream &out, const location &loc);

class diagnostic_message
{
        std::string message;
        location location;
public:
        diagnostic_message(/* args */);
        ~diagnostic_message();
};


} // namespace kehu::diagnostic


#endif // _KEHU_DIAGNOSTIC_H

