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

#ifndef VECTOR_hpp
#define VECTOR_hpp

#include <cstring>  // exclusively for std::memcpy()

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"
#include "Allocator.hpp"

namespace alt   // Vector belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Datatype, class Allocator = alt::Allocator<Datatype> >
class Vector
{
////////////////////////////////////////////////////////////

/// MEMBER VARIABLES
private:
    u32       Count_;       // The number of elements in the Vector
    u32       Length_;      // The total number of elements the Vector can hold before a growth event
    u16       Growth_;      // The percent growth of the Vector's length during a growth event
    Allocator Allocator_;   // The memory Allocator of the Vector
    Datatype* Array_;       // The array of elements held in the Vector

////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR, DESTRUCTOR, & INITIALIZER
public:

Vector() noexcept: // default constructor
    Count_(0),
    Length_(0),
    Growth_(100),
    Allocator_(),
    Array_(nullptr)
{}

~Vector() noexcept // destructor
{
    if (Array_)
        Allocator_.Deallocate(Array_);
}

bool Init(u32 initLength = 1)
{
    if (Array_ || ! initLength)
        return true;
    Array_ = Allocator_.Allocate(initLength);
    Length_ = initLength;
    return false;
}

////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTORS
public:

Vector(u32 initLength):
    Count_(0),
    Length_(initLength),
    Growth_(100),
    Allocator_(),
    Array_(nullptr)
{
    if (Length_)
        Array_ = Allocator_.Allocate(Length_);
}

explicit Vector(u32 initLength, u16 percentGrowthRate):
    Count_(0),
    Length_(initLength),
    Growth_(percentGrowthRate),
    Allocator_(),
    Array_(nullptr)
{
    if (Length_)
        Array_ = Allocator_.Allocate(Length_);
}

/// ARRAY INJECTION CONSTRUCTOR TBD
// explicit Vector(Datatype* initArray, u32 initCount, u32 initLength) noexcept:
//     Count_(initCount),
//     Length_(initLength),
//     Growth_(100),
//     Allocator_(),
//     Array_(initArray)
// {}

////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR, MOVE CONSTRUCTOR, & ASSIGNMENT OPERATOR
public:

Vector(const Vector& copy): // copy constructor
    Count_(copy.Count_),
    Length_(copy.Length_),
    Growth_(copy.Growth_),
    Allocator_(copy.Allocator_),
    Array_(nullptr)
{
    if (this->Length_)
    {
        this->Array_ = this->Allocator_.Allocate(this->Length_);
        std::memcpy(this->Array_, copy.Array_, this->Length_);
    }
}

Vector(Vector&& move) noexcept: // move constructor
    Count_(move.Count_),
    Length_(move.Length_),
    Growth_(move.Growth_),
    Allocator_((Allocator&&)(move.Allocator_)),
    Array_(move.Array_)
{
    move.Array_  = nullptr;
}

Vector& operator = (const Vector& copy)
{
    this->Allocator_.Deallocate(this->Array_);
    this->Count_     = copy.Count_;
    this->Length_    = copy.Length_;
    this->Growth_    = copy.Growth_;
    this->Allocator_ = copy.Allocator_;
    if (this->Length_)
    {
        this->Array_ = this->Allocator_.Allocate(this->Length_);
        std::memcpy(this->Array_, copy.Array_, this->Length_);
    }
    else
        this->Array_ = nullptr;
    return *this;
}

Vector& operator = (Vector&& move) noexcept
{
    this->Allocator_.Deallocate(this->Array_);
    this->Count_     = move.Count_;
    this->Length_    = move.Length_;
    this->Growth_    = move.Growth_;
    this->Allocator_ = (Allocator&&)(move.Allocator_);
    this->Array_     = move.Array_;
    move.Array_      = nullptr;
    return *this;
}

////////////////////////////////////////////////////////////
/// SIZE & CAPACITY ACCESSORS
public:

u32 DataSize(u32 num = 1) const
{
    return sizeof(Datatype) * num;
}

u32 Size(void) const
{
    return Count_;
}

u32 Capacity(void) const
{
    return Length_;
}

bool Empty(void) const
{
    return (Count_ == 0);
}

bool Full(void) const
{
    return (Count_ == Length_);
}

////////////////////////////////////////////////////////////
/// SIZE & CAPACITY MODIFIERS
public:

bool Resize(u32 newCapacity)
{
    if (newCapacity == Length_)
        return true;
    else if (newCapacity < Count_)
        return Truncate(newCapacity);
    else if (newCapacity < Length_)
        return Shrink(newCapacity);
    else
        return Grow(newCapacity);
}

bool Grow(void)
{
    if (Length_)
        return Grow((Length_ * (Growth_ + 100)) / 100);
    return Grow((Growth_ + 100) / 100);
}

bool Grow(u32 newCapacity)
{
    if (newCapacity <= Length_)
        return true;
    Datatype* newArray = Allocator_.Allocate(newCapacity);
    std::memcpy(newArray, Array_, DataSize(Count_));
    Allocator_.Deallocate(Array_);
    Length_ = newCapacity;
    Array_  = newArray;
    return false;
}

bool Shrink(void)
{
    return Shrink(Count_);
}

bool Shrink(u32 newCapacity)
{
    if (! newCapacity ||
        newCapacity <  Count_ ||
        newCapacity >= Length_)
        return true;
    Datatype* newArray = Allocator_.Allocate(newCapacity);
    std::memcpy(newArray, Array_, DataSize(Count_));
    Allocator_.Deallocate(Array_);
    Length_ = newCapacity;
    Array_  = newArray;
    return false;
}

/// NOTE: passing zero will set Count_ & Length_ to zero, will destruct & deallocate Array_, and set Array_ to nullptr
bool Truncate(u32 newCapacity)
{
    if (newCapacity >= Count_)
        return true;
    Datatype* newArray = nullptr;
    if (newCapacity)
    {
        newArray = Allocator_.Allocate(newCapacity);
        std::memcpy(newArray, Array_, DataSize(newCapacity));
    }
    Allocator_.Deallocate(Array_);
    Count_  = newCapacity;
    Length_ = newCapacity;
    Array_  = newArray;
    return false;
}

////////////////////////////////////////////////////////////
/// MEMORY ACCESSORS & MODIFIERS
public:

const Datatype& At(u32 index) const
{
    if (index >= Count_)
        throw alt::InvalidIndex();
    return Array_[index];
}

Datatype& At(u32 index)
{
    if (index >= Count_)
        throw alt::InvalidIndex();
    return Array_[index];
}

const Datatype& operator [] (u32 index) const
{
    return Array_[index];
}

/// WARNING: this method can destroy the Count_ invariant
Datatype& operator [] (u32 index)
{
    return Array_[index];
}

/// NOTE: includes bounds checking, and cannot destroy the Count_ invariant
bool Swap(u32 index1st, u32 index2nd)
{
    if (index1st >= Count_ ||
        index2nd >= Count_)
        return true;
    Datatype tmp     = Array_[index1st];
    Array_[index1st] = Array_[index2nd];
    Array_[index2nd] = tmp;
    return false;
}

/// WARNING: this method can destroy the Count_ invariant
void Swap(Datatype* const ptr1st, Datatype* const ptr2nd) noexcept
{
    Datatype tmp = *ptr1st;
    *ptr1st      = *ptr2nd;
    *ptr2nd      = tmp;
}

////////////////////////////////////////////////////////////
/// SEARCH METHODS
public:

bool Contains(const Datatype& x) const
{
    const Datatype* ptr = Array_;
    const Datatype* const end = ptr + Count_;
    for (; ptr < end; ptr++)
        if (*ptr == x)
            return true;
    return false;
}

i64 IndexOf(const Datatype& x) const
{
    const Datatype* ptr = Array_;
    for (i64 i = 0; i < Count_; ptr++, i++)
        if (*ptr == x)
            return i;
    return -1;
}

bool IndexOf(const Datatype& x, u32& rtn) const
{
    const Datatype* ptr = Array_;
    for (u32 i = 0; i < Count_; ptr++, i++)
        if (*ptr == x)
        {
            rtn = i;
            return true;
        }
    return false;
}

i64 LastIndexOf(const Datatype& x) const
{
    const Datatype* ptr = Array_ + (Count_ - 1);
    for (i64 i = Count_ - 1; i >= 0; ptr--, i--)
        if (*ptr == x)
            return i;
    return -1;
}

bool LastIndexOf(const Datatype& x, u32& rtn) const
{
    const Datatype* ptr = Array_ + (Count_ - 1);
    for (u32 i = Count_ - 1; i >= 0; ptr--, i--)
        if (*ptr == x)
        {
            rtn = i;
            return true;
        }
    return false;
}

////////////////////////////////////////////////////////////
/// CONTAINER METHODS
public:

bool Get(u32 index, Datatype& rtn)
{
    if (index >= Count_)
        return true;
    rtn = Array_[index];
    return Remove(index);
}

bool PushFront(const Datatype& x)
{
    if (Full() &&
        Grow())
        return true;
    Datatype* const end = Array_;
    Datatype* ptr = end + Count_;
    for (; ptr > end; ptr--)
        Swap(ptr - 1, ptr);
    *end = x;
    Count_++;
    return false;
}

bool PushBack(const Datatype& x)
{
    if (Full() &&
        Grow())
        return true;
    Array_[Count_] = x;
    Count_++;
    return false;
}

const Datatype& PeekFront(void) const
{
    return At(0);
}

Datatype& PeekFront(void)
{
    return At(0);
}

const Datatype& PeekBack(void) const
{
    return At(Count_ - 1);
}

Datatype& PeekBack(void)
{
    return At(Count_ - 1);
}

bool PopFront(Datatype& rtn)
{
    return Get(0, rtn);
}

bool PopBack(Datatype& rtn)
{
    return Get(Count_ - 1, rtn);
}

/// NOTE: index can be within the range [0, Count_], otherwise this method fails and returns true
bool Insert(u32 index, const Datatype& x)
{
    if (Full() &&
        Grow())
        return true;
    if (index > Count_)
        return true;
    Datatype* const end = Array_ + index;
    Datatype* ptr = Array_ + Count_;
    for (; ptr > end; ptr--)
        Swap(ptr - 1, ptr);
    *end = x;
    Count_++;
    return false;
}

bool Remove(u32 index)
{
    if (index >= Count_)
        return true;
    Count_--;
    Datatype* ptr = Array_ + index;
    Datatype* const end = Array_ + Count_;
    for (; ptr < end; ptr++)
        Swap(ptr, ptr + 1);
    return false;
}

void Erase(void)
{
    Count_ = 0;
}

////////////////////////////////////////////////////////////
/// VECTOR OPERATION METHODS
public:

void Append(const Vector& that)
{
    this->Resize(this->Length_ + that.Length_);
    std::memcpy(this->Array_ + this->Count_, that.Array_, DataSize(that.Count_));
    this->Count_ += that.Count_;
}

void operator += (const Vector& that)
{
    this->Append(that);
}

/// NOTE: only checks for list equivalency, not object equivalency - less rigorous than alt::Vector::operator==()
bool Equals(const Vector& that) const
{
    if (this->Count_ != that.Count_)
        return false;
    const Datatype* this_ptr = this->Array_;
    const Datatype* that_ptr = that.Array_;
    const Datatype* const this_end = this_ptr + this->Count_;
    for (; this_ptr < this_end; this_ptr++, that_ptr++)
        if (*this_ptr != *that_ptr)
            return false;
    return true;
}

/// NOTE: checks for object equivalency - much more rigorous than alt::Vector::Equals()
bool operator == (const Vector& that) const
{
    if (this->Length_    != that.Length_ ||
        this->Growth_    != that.Growth_ ||
        this->Allocator_ != that.Allocator_)
        return false;
    return this->Equals(that);
}

/// NOTE: returns the opposite of operator ==
bool operator != (const Vector& that) const
{
    return ! this->operator == (that);
}

////////////////////////////////////////////////////////////
}; // end template class Vector

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end VECTOR_hpp
