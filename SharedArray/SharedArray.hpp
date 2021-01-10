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
/// CREATED: 2021.01.10

#ifndef SHAREDARRAY_hpp
#define SHAREDARRAY_hpp

#include "Keywords.hpp"
#include "Types.hpp"

namespace alt   // SharedArray belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype>
class SharedArray
{
////////////////////////////////////////////////////////////
/// MEMBER VARIABLES
private:

    static u8 Count_;   // array counter
    Datatype* Array_;   // RAII encapsulated array

////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:

/// WARN: To preserve the Singular Unique Array per Datatype Invariant of this class, it is required that any
/// SharedArray object be given ownership of an array during its construction, through its constructor.
SharedArray() = delete;

~SharedArray() noexcept
{
    if (Array_ && Count_ == 1)
        delete [] Array_;
    --Count_;
}

////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedArray(Datatype arr[]) noexcept:
    Array_(arr)
{
    ++Count_;
}

/// WARN: This operator had the ability to destroy the Singular Unique Array per Datatype Invariant of this class, and
/// thus was deleted.
SharedArray& operator = (Datatype arr[]) = delete;

////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedArray(const SharedArray& copy) noexcept:
    Array_(copy.Array_)
{
    ++Count_;
}

/// WARN: This operator had the ability to destroy the Singular Unique Pointer per Datatype Invariant of this class, and
/// thus was deleted.
SharedArray& operator = (const SharedArray& copy) = delete;

////////////////////////////////////////////////////////////
/// MOVE CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedArray(SharedArray&& move) = delete;   // transfer of ownership wouldn't make sense

/// WARN: This operator had the ability to destroy the Singular Unique Pointer per Datatype Invariant of this class, and
/// thus was deleted.
SharedArray& operator = (SharedArray&& move) = delete;

////////////////////////////////////////////////////////////
/// OPERATOR OVERLOADS
public:

const Datatype* const operator & (void) const
{
    return Array_;
}

Datatype* const operator & (void)
{
    return Array_;
}

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
}; // end template class SharedArray

template <typename Datatype>
alt::u8 SharedArray<Datatype>::Count_ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end SHAREDARRAY_hpp
