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

#ifndef ARRAYPOINTER_hpp
#define ARRAYPOINTER_hpp

namespace alt // ArrayPointer belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype>
class ArrayPointer
{

/// RAII ENCAPSULATED ARRAY
private:
    Datatype* Array_;   // The encapsulated array.

/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:
    ArrayPointer() noexcept:    // default constructor
        Array_(nullptr)
    {}

    ~ArrayPointer() noexcept    // destructor
    {
        if (Array_)
            delete [] Array_;
    }

/// OVERLOADED CONSTRUCTOR
public:
    ArrayPointer(Datatype* arr) noexcept:
        Array_(arr)
    {}

/// COPY CONSTRUCTOR, MOVE CONSTRUCTOR, & ASSIGNMENT OPERATOR
public:
    ArrayPointer(const ArrayPointer& copy) = delete;    // NO DUPLICATION

    ArrayPointer(ArrayPointer&& move) noexcept:     // transfer of ownership is allowed
        Array_(move.Array_)
    {
        move.Array_ = nullptr;
    }

    ArrayPointer& operator = (const ArrayPointer& copy) = delete;   // NO DUPLICATION

    ArrayPointer& operator = (ArrayPointer&& move) noexcept     // transfer of ownership is allowed
    {
        if (this->Array_)
            delete [] this->Array_;
        this->Array_ = move.Array_;
        move.Array_  = nullptr;
        return *this;
    }

    ArrayPointer& operator = (Datatype* arr) noexcept
    {
        if (Array_)
            delete [] Array_;
        Array_ = arr;
        return *this;
    }

/// OPERATOR OVERLOADS
public:
    const Datatype* operator & (void) const
    {
        return Array_;
    }

    Datatype* operator & (void)
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

    const Datatype& operator [] (unsigned long long int index) const
    {
        return Array_[index];
    }

    Datatype& operator [] (unsigned long long int index)
    {
        return Array_[index];
    }

}; // end template class ArrayPointer

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end ARRAYPOINTER_hpp
