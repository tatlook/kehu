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

#if !defined(_KEHU_SCOPE_H)
#define _KEHU_SCOPE_H

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>
#include "types.h"

namespace kehu::ast
{

class access_failed : public std::runtime_error
{
public:
        explicit access_failed(const char *s) : std::runtime_error(s)
        {}
};

class scope
{
protected:
        /**
         * @brief Parent scope.
         */
        scope *const parent;

        std::vector<std::reference_wrapper<scope>> children;

        std::vector<const types::type *> types;

        scope(scope *parent) : parent(parent)
        {}
public:
        /**
         * @brief Do something while leaving scope
         * 
         */
        virtual void leave() = 0;

        const types::type &get_type(const std::string &id) const;
};

class root_scope final : public scope
{
private:
        static root_scope obj;
        
        root_scope();
public:
        root_scope(const root_scope &) = default;

        void operator=(const root_scope &) = delete;

        static const root_scope &get();

        void leave() override;
};

class package_scope : public scope
{
public:
        explicit package_scope(std::string package_name);

        void define_variable();
        void define_function();
        void define_class();
        void leave() override;
};

class class_scope : public scope
{
public:
        void define_variable();
        void leave() override;
};

class exec_scope : public scope
{
public:
        void leave() override;
};

} // namespace kehu::ast

#endif // _KEHU_SCOPE_H
