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

#if !defined(_KEHU_TYPES_H)
#define _KEHU_TYPES_H

#include <string>
#include <llvm/IR/IRBuilder.h>
#include <array>

namespace kehu::types
{

class type
{
private:
        /**
         * @brief Unique name of this type.
         * The id is like @c %vector , @c %int
         */
        const std::string id;
protected:
        explicit type(const std::string &id) : id(id)
        {}
public:
        const std::string &get_id() const
        {
                return id;
        }

        bool operator==(const type &other) const
        {
                return id == other.id;
        }

        bool operator==(const std::string &id) const
        {
                return this->id == id;
        }

        virtual llvm::Type *get_llvm_type(llvm::LLVMContext &context) const = 0;
};

class int_type : public type
{
private:
        static int_type obj;

        int_type() : type("%int")
        {}
public:
        int_type(const int_type &) = delete;

        void operator=(const int_type &) = delete;

        static const int_type &get();

        llvm::Type *get_llvm_type(llvm::LLVMContext &context) const override;
};

class string_type : public type
{
private:
        static string_type obj;

        string_type() : type("%string")
        {}
public:
        string_type(const string_type &) = delete;

        void operator=(const string_type &) = delete;

        static const string_type &get();

        llvm::Type *get_llvm_type(llvm::LLVMContext &context) const override;
};

class interface_type : public type
{
public:
        ;
};

class class_type : public type
{
public:
        llvm::Type *get_llvm_type(llvm::LLVMContext &context) const override;
};

} // namespace kehu::types

#endif // _KEHU_TYPES_H
