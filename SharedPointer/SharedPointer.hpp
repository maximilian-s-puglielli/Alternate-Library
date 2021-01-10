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
/// CREATED: 2021.01.09

#ifndef SHAREDPOINTER_hpp
#define SHAREDPOINTER_hpp

#include "Keywords.hpp"
#include "Types.hpp"

namespace alt   // SharedPointer belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype>
class SharedPointer
{
////////////////////////////////////////////////////////////
/// MEMBER VARIABLES
private:

    static u8 Count_;       // pointer counter
    Datatype* Pointer_;     // RAII encapsulated pointer

////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:

/// WARN: To preserve the Singular Unique Pointer per Datatype Invariant of this class, it is required that any
/// SharedPointer object be given ownership of a pointer during its construction, through its constructor.
SharedPointer() = delete;

~SharedPointer() noexcept
{
    if (Pointer_ && Count_ == 1)
        delete Pointer_;
    --Count_;
}

////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedPointer(Datatype* ptr) noexcept:
    Pointer_(ptr)
{
    ++Count_;
}

/// WARN: This operator had the ability to destroy the Singular Unique Pointer per Datatype Invariant of this class, and
/// thus was deleted.
SharedPointer& operator = (Datatype* ptr) = delete;

////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedPointer(const SharedPointer& copy) noexcept:
    Pointer_(copy.Pointer_)
{
    ++Count_;
}

/// WARN: This operator had the ability to destroy the Singular Unique Pointer per Datatype Invariant of this class, and
/// thus was deleted.
SharedPointer& operator = (const SharedPointer& copy) = delete;

////////////////////////////////////////////////////////////
/// MOVE CONSTRUCTOR & ASSIGNMENT OPERATOR
public:

SharedPointer(SharedPointer&& move) = delete;   // transfer of ownership wouldn't make sense

/// WARN: This operator had the ability to destroy the Singular Unique Pointer per Datatype Invariant of this class, and
/// thus was deleted.
SharedPointer& operator = (SharedPointer&& move) = delete;

////////////////////////////////////////////////////////////
/// OPERATOR OVERLOADS
public:

const Datatype& operator * (void) const
{
    return *Pointer_;
}

Datatype& operator * (void)
{
    return *Pointer_;
}

const Datatype* const operator -> (void) const
{
    return Pointer_;
}

Datatype* const operator -> (void)
{
    return Pointer_;
}

////////////////////////////////////////////////////////////
}; // end template class SharedPointer

template <typename Datatype>
alt::u8 SharedPointer<Datatype>::Count_ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end SHAREDPOINTER_hpp
