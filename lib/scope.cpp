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

#include <kehu/scope.h>

namespace kehu::ast
{

using types::type;

const type &scope::get_type(const std::string &id) const
{
        auto t = std::find_if(types.begin(), types.end(), 
                        [&id](const type *t) -> bool {
                                return *t == id;
                        });
        if (t != types.end())
                return **t;
        if (parent == nullptr)
                throw access_failed("FCYOU");
        return parent->get_type(id);
}

root_scope::root_scope() : scope(nullptr)
{
        types.push_back(&types::int_type::get());
        types.push_back(&types::string_type::get());
}

root_scope root_scope::obj;

const root_scope &root_scope::get()
{
        return obj;
}

void root_scope::leave()
{}

}
