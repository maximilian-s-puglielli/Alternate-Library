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

#ifndef UNIQUEPOINTER_hpp
#define UNIQUEPOINTER_hpp

namespace alt   // UniquePointer belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype>
class UniquePointer
{
////////////////////////////////////////////////////////////
/// RAII ENCAPSULATED POINTER
private:

    Datatype* Pointer_;     // The encapsulated pointer.

////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:

UniquePointer() noexcept:   // default constructor
    Pointer_(nullptr)
{}

~UniquePointer() noexcept   // destructor
{
    if (Pointer_)
        delete Pointer_;
}

////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTOR
public:

UniquePointer(Datatype* ptr) noexcept:
    Pointer_(ptr)
{}

////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR, MOVE CONSTRUCTOR, & ASSIGNMENT OPERATOR
public:

UniquePointer(const UniquePointer& copy) = delete;  // NO DUPLICATION

UniquePointer(UniquePointer&& move) noexcept:   // transfer of ownership is allowed
    Pointer_(move.Pointer_)
{
    move.Pointer_ = nullptr;
}

UniquePointer& operator = (const UniquePointer& copy) = delete;     // NO DUPLICATION

UniquePointer& operator = (UniquePointer&& move)    // transfer of ownership is allowed
{
    if (this->Pointer_)
        delete this->Pointer_;
    this->Pointer_ = move.Pointer_;
    move.Pointer_  = nullptr;
    return *this;
}

UniquePointer& operator = (Datatype* ptr) noexcept
{
    if (Pointer_)
        delete Pointer_;
    Pointer_ = ptr;
    return *this;
}

////////////////////////////////////////////////////////////
/// OPERATORS OVERLOADS
public:

const Datatype& operator * (void) const
{
    return *Pointer_;
}

Datatype& operator * (void)
{
    return *Pointer_;
}

const Datatype* operator -> (void) const
{
    return Pointer_;
}

Datatype* operator -> (void)
{
    return Pointer_;
}

////////////////////////////////////////////////////////////
}; // end template class UniquePointer

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end UNIQUEPOINTER_hpp
