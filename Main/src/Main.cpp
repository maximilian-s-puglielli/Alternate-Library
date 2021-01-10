/// Copyright (C) 2021 Maximilian S Puglielli (MSP)
/// 
/// The full copyright license belonging to this repository may be found in the
/// parent directory in the file named 'LICENSE'.
///
/// This program is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the Free
/// Software Foundation, either version 3 of the License, or (at your option)
/// any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
/// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
/// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
/// more details.
///
/// You should have received a copy of the GNU General Public License along with
/// this program.  If not, see <https://www.gnu.org/licenses/>.
///
/// AUTHOR:  Maximilian S Puglielli (MSP)
/// CREATED: 2021.01.06

#include <iostream>

#include "Keywords.hpp"
#include "Types.hpp"

#include "Exceptions.hpp"

#include "Allocator.hpp"

#include "Vector.hpp"

#include "UniquePointer.hpp"
#include "SharedPointer.hpp"
#include "UniqueArray.hpp"
#include "SharedArray.hpp"

#include "u128.hpp"

READONLY STR TAB  = "        ";
READONLY STR INFO = "INFO:   ";
READONLY STR WARN = "WARN:   ";
READONLY STR FAIL = "FAIL:   ";
READONLY STR EXIT = "EXIT:   ";

void TestExceptions    ( void );
void TestAllocator     ( void );
void TestVector        ( void );
void TestUniquePointer ( void );
void TestArrayPointer  ( void );
void TestU128          ( void );

int main(int argc, const STR const argv[])
{
    std::cout << std::endl;
    try
    {
        TestExceptions();
        TestAllocator();
        TestVector();
        TestUniquePointer();
        TestArrayPointer();
        TestU128();
    }
    catch (const alt::Except& err)
    {
        std::cout << EXIT << "FAILURE" << std::endl << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& err)
    {
        std::cout << EXIT << "FAILURE" << std::endl << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << EXIT << "SUCCESS" << std::endl << std::endl;
    return EXIT_SUCCESS;
}

void TestExceptions(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning Exceptions Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "Exceptions Test Passed" << std::endl << std::endl;
}

void TestAllocator(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning Allocator Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "Allocator Test Passed" << std::endl << std::endl;
}

void TestVector(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning Vector Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "Vector Test Passed" << std::endl << std::endl;
}

void TestUniquePointer(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning UniquePointer Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "UniquePointer Test Passed" << std::endl << std::endl;
}

void TestArrayPointer(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning ArrayPointer Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "ArrayPointer Test Passed" << std::endl << std::endl;
}

void TestU128(void)
{
    using namespace alt;
    std::cout << INFO << "Beginning u128 Test" << std::endl;

    /// TODO: write tests here

    std::cout << INFO << "u128 Test Passed" << std::endl << std::endl;
}
