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

#include <kehu/types.h>

namespace kehu::types
{

int_type int_type::obj;

const int_type &int_type::get()
{
        return obj;
}

llvm::Type *int_type::get_llvm_type(llvm::LLVMContext &context) const
{
        return llvm::IntegerType::get(context, 32);
}

string_type string_type::obj;

const string_type &string_type::get()
{
        return obj;
}

llvm::Type *string_type::get_llvm_type(llvm::LLVMContext &context) const
{
        return llvm::PointerType::get(llvm::IntegerType::get(context, 32), 1);
}

} // namespace kehu::types
