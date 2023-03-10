# Kehu - a toe language
# Copyright (C) 2023 Zhen You Zhe
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

add_library(
        kehu-lib
        token.cpp
        tokenize.cpp
        ast.cpp
        parse_tiled.cpp
        transform_ast.cpp
)

target_include_directories(kehu-lib PRIVATE ../include)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs core)

message(STATUS "Found LLVM lib: ${llvm_libs}")

# Link against LLVM libraries
target_link_libraries(kehu-lib ${llvm_libs})
