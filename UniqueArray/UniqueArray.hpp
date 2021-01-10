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

#ifndef UNIQUEARRAY_hpp
#define UNIQUEARRAY_hpp

#include "Keywords.hpp"
#include "Types.hpp"

namespace alt // UniqueArray belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype>
class UniqueArray
{
////////////////////////////////////////////////////////////
/// RAII ENCAPSULATED ARRAY
private:

    Datatype* Array_;   // The encapsulated array.

////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:

UniqueArray() noexcept:
    Array_(nullptr)
{}

~UniqueArray() noexcept
{
    if (Array_)
        delete [] Array_;
}

////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

UniqueArray(Datatype arr[]) noexcept:
    Array_(arr)
{}

UniqueArray& operator = (Datatype arr[]) noexcept
{
    if (Array_)
        delete [] Array_;
    Array_ = arr;
    return *this;
}

////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

UniqueArray(const UniqueArray& copy) = delete;                // NO DUPLICATION
UniqueArray& operator = (const UniqueArray& copy) = delete;   // NO DUPLICATION

////////////////////////////////////////////////////////////
/// MOVE CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

UniqueArray(UniqueArray&& move) noexcept:                 // transfer of ownership is allowed
    Array_(move.Array_)
{
    move.Array_ = nullptr;
}


UniqueArray& operator = (UniqueArray&& move) noexcept     // transfer of ownership is allowed
{
    if (this->Array_)
        delete [] this->Array_;
    this->Array_ = move.Array_;
    move.Array_  = nullptr;
    return *this;
}

////////////////////////////////////////////////////////////
/// OVERLOADED OPERATORS
public:

const Datatype& operator * (void) const
{
    return *Array_;
}

Datatype& operator * (void)
{
    return *Array_;
}

const Datatype& operator [] (uSIZE index) const
{
    return Array_[index];
}

Datatype& operator [] (uSIZE index)
{
    return Array_[index];
}

////////////////////////////////////////////////////////////
}; // end template class UniqueArray

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end UNIQUEARRAY_hpp
