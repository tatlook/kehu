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


find_package(GTest)

add_executable(
        kehu-test
        test-main.cpp
        tokenizer-test.cpp
        treeparser-test.cpp
)

include(GoogleTest)
gtest_discover_tests(kehu-test)

target_link_libraries(
        kehu-test
        kehu-lib
        GTest::gtest_main
)
        
target_include_directories(kehu-test PRIVATE ../include ../lib)

include(CTest)
add_test(NAME Compiler COMMAND kehu test.pnl m.ll)

add_custom_target(file-copy ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/test.pnl)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test.pnl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.pnl
                                        ${CMAKE_CURRENT_BINARY_DIR}/test.pnl
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test.pnl)

