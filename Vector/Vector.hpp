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

#include <cstring> // exclusively for std::memcpy()

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"
#include "Allocator.hpp"

namespace alt // Vector belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Datatype, class Allocator = alt::Allocator<Datatype> >
class Vector
{

/// MEMBER VARIABLES
private:
    u32       mCount;       // The number of elements in the Vector
    u32       mLength;      // The total number of elements the Vector can hold before a growth event
    u16       mGrowth;      // The percent growth of the Vector's length during a growth event
    Allocator mAllocator;   // The memory Allocator of the Vector
    Datatype* mArray;       // The array of elements held in the Vector

/// DEFAULT CONSTRUCTOR, DESTRUCTOR, & INITIALIZER
public:
    Vector() noexcept: // default constructor
        mCount(0),
        mLength(0),
        mGrowth(100),
        mAllocator(),
        mArray(nullptr)
    {}

    ~Vector() noexcept // destructor
    {
        if (mArray)
            mAllocator.Deallocate(mArray);
    }

    bool Init(u32 initLength = 1)
    {
        if (mArray || ! initLength)
            return true;
        mArray = mAllocator.Allocate(initLength);
        mLength = initLength;
        return false;
    }

/// OVERLOADED CONSTRUCTORS
public:
    Vector(u32 initLength):
        mCount(0),
        mLength(initLength),
        mGrowth(100),
        mAllocator(),
        mArray(nullptr)
    {
        if (mLength)
            mArray = mAllocator.Allocate(mLength);
    }

    explicit Vector(u32 initLength, u16 percentGrowthRate):
        mCount(0),
        mLength(initLength),
        mGrowth(percentGrowthRate),
        mAllocator(),
        mArray(nullptr)
    {
        if (mLength)
            mArray = mAllocator.Allocate(mLength);
    }

    explicit Vector(Datatype* initArray, u32 initCount, u32 initLength) noexcept:
        mCount(initCount),
        mLength(initLength),
        mGrowth(100),
        mAllocator(),
        mArray(initArray)
    {}

/// COPY CONSTRUCTOR, MOVE CONSTRUCTOR, & ASSIGNMENT OPERATOR
public:
    Vector(const Vector& copy): // copy constructor
        mCount(copy.mCount),
        mLength(copy.mLength),
        mGrowth(copy.mGrowth),
        mAllocator(copy.mAllocator),
        mArray(nullptr)
    {
        if (this->mLength)
        {
            this->mArray = this->mAllocator.Allocate(this->mLength);
            std::memcpy(this->mArray, copy.mArray, this->mLength);
        }
    }

    Vector(Vector&& move) noexcept: // move constructor
        mCount(move.mCount),
        mLength(move.mLength),
        mGrowth(move.mGrowth),
        mAllocator((Allocator&&)(move.mAllocator)),
        mArray(move.mArray)
    {
        move.mArray  = nullptr;
    }

    Vector& operator = (const Vector& copy)
    {
        this->mAllocator.Deallocate(this->mArray);
        this->mCount     = copy.mCount;
        this->mLength    = copy.mLength;
        this->mGrowth    = copy.mGrowth;
        this->mAllocator = copy.mAllocator;
        if (this->mLength)
        {
            this->mArray = this->mAllocator.Allocate(this->mLength);
            std::memcpy(this->mArray, copy.mArray, this->mLength);
        }
        else
            this->mArray = nullptr;
        return *this;
    }

    Vector& operator = (Vector&& move) noexcept
    {
        this->mAllocator.Deallocate(this->mArray);
        this->mCount     = move.mCount;
        this->mLength    = move.mLength;
        this->mGrowth    = move.mGrowth;
        this->mAllocator = (Allocator&&)(move.mAllocator);
        this->mArray     = move.mArray;
        move.mArray      = nullptr;
        return *this;
    }

/// SIZE & CAPACITY ACCESSORS
public:
    u32 DataSize(u32 num = 1) const
    {
        return sizeof(Datatype) * num;
    }

    u32 Size(void) const
    {
        return mCount;
    }

    u32 Capacity(void) const
    {
        return mLength;
    }

    bool Empty(void) const
    {
        return (mCount == 0);
    }

    bool Full(void) const
    {
        return (mCount == mLength);
    }

/// SIZE & CAPACITY MODIFIERS
public:
    bool Resize(u32 newCapacity)
    {
        if (newCapacity == mLength)
            return true;
        else if (newCapacity < mCount)
            return Truncate(newCapacity);
        else if (newCapacity < mLength)
            return Shrink(newCapacity);
        else
            return Grow(newCapacity);
    }

    bool Grow(void)
    {
        if (mLength)
            return Grow((mLength * (mGrowth + 100)) / 100);
        return Grow((mGrowth + 100) / 100);
    }

    bool Grow(u32 newCapacity)
    {
        if (newCapacity <= mLength)
            return true;
        Datatype* newArray = mAllocator.Allocate(newCapacity);
        std::memcpy(newArray, mArray, DataSize(mCount));
        mAllocator.Deallocate(mArray);
        mLength = newCapacity;
        mArray  = newArray;
        return false;
    }

    bool Shrink(void)
    {
        return Shrink(mCount);
    }

    bool Shrink(u32 newCapacity)
    {
        if (! newCapacity ||
            newCapacity <  mCount ||
            newCapacity >= mLength)
            return true;
        Datatype* newArray = mAllocator.Allocate(newCapacity);
        std::memcpy(newArray, mArray, DataSize(mCount));
        mAllocator.Deallocate(mArray);
        mLength = newCapacity;
        mArray  = newArray;
        return false;
    }

    /// NOTE: passing zero will set mCount & mLength to zero, will destruct & deallocate mArray, and set mArray to
    /// nullptr
    bool Truncate(u32 newCapacity)
    {
        if (newCapacity >= mCount)
            return true;
        Datatype* newArray = nullptr;
        if (newCapacity)
        {
            newArray = mAllocator.Allocate(newCapacity);
            std::memcpy(newArray, mArray, DataSize(newCapacity));
        }
        mAllocator.Deallocate(mArray);
        mCount  = newCapacity;
        mLength = newCapacity;
        mArray  = newArray;
        return false;
    }

/// MEMORY ACCESSORS & MODIFIERS
public:
    const Datatype& At(u32 index) const
    {
        if (index >= mCount)
            throw alt::InvalidIndex();
        return mArray[index];
    }

    Datatype& At(u32 index)
    {
        if (index >= mCount)
            throw alt::InvalidIndex();
        return mArray[index];
    }

    const Datatype& operator [] (u32 index) const
    {
        return mArray[index];
    }

    /// WARNING: this method can destroy the mCount invariant
    Datatype& operator [] (u32 index)
    {
        return mArray[index];
    }

    /// NOTE: includes bounds checking, and cannot destroy the mCount invariant
    bool Swap(u32 index1st, u32 index2nd)
    {
        if (index1st >= mCount ||
            index2nd >= mCount)
            return true;
        Datatype tmp     = mArray[index1st];
        mArray[index1st] = mArray[index2nd];
        mArray[index2nd] = tmp;
        return false;
    }

    /// WARNING: this method can destroy the mCount invariant
    void Swap(Datatype* const ptr1st, Datatype* const ptr2nd) noexcept
    {
        Datatype tmp = *ptr1st;
        *ptr1st      = *ptr2nd;
        *ptr2nd      = tmp;
    }

/// SEARCH METHODS
public:
    bool Contains(const Datatype& x) const
    {
        const Datatype* ptr = mArray;
        const Datatype* const end = ptr + mCount;
        for (; ptr < end; ptr++)
            if (*ptr == x)
                return true;
        return false;
    }

    i64 IndexOf(const Datatype& x) const
    {
        const Datatype* ptr = mArray;
        for (i64 i = 0; i < mCount; ptr++, i++)
            if (*ptr == x)
                return i;
        return -1;
    }

    bool IndexOf(const Datatype& x, u32& rtn) const
    {
        const Datatype* ptr = mArray;
        for (u32 i = 0; i < mCount; ptr++, i++)
            if (*ptr == x)
            {
                rtn = i;
                return true;
            }
        return false;
    }

    i64 LastIndexOf(const Datatype& x) const
    {
        const Datatype* ptr = mArray + (mCount - 1);
        for (i64 i = mCount - 1; i >= 0; ptr--, i--)
            if (*ptr == x)
                return i;
        return -1;
    }

    bool LastIndexOf(const Datatype& x, u32& rtn) const
    {
        const Datatype* ptr = mArray + (mCount - 1);
        for (u32 i = mCount - 1; i >= 0; ptr--, i--)
            if (*ptr == x)
            {
                rtn = i;
                return true;
            }
        return false;
    }

/// CONTAINER METHODS
public:
    bool Get(u32 index, Datatype& rtn)
    {
        if (index >= mCount)
            return true;
        rtn = mArray[index];
        return Remove(index);
    }

    bool PushFront(const Datatype& x)
    {
        if (Full() &&
            Grow())
            return true;
        Datatype* const end = mArray;
        Datatype* ptr = end + mCount;
        for (; ptr > end; ptr--)
            Swap(ptr - 1, ptr);
        *end = x;
        mCount++;
        return false;
    }

    bool PushBack(const Datatype& x)
    {
        if (Full() &&
            Grow())
            return true;
        mArray[mCount] = x;
        mCount++;
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
        return At(mCount - 1);
    }

    Datatype& PeekBack(void)
    {
        return At(mCount - 1);
    }

    bool PopFront(Datatype& rtn)
    {
        return Get(0, rtn);
    }

    bool PopBack(Datatype& rtn)
    {
        return Get(mCount - 1, rtn);
    }

    /// NOTE: index can be within the range [0, mCount], otherwise this method fails and returns true
    bool Insert(u32 index, const Datatype& x)
    {
        if (Full() &&
            Grow())
            return true;
        if (index > mCount)
            return true;
        Datatype* const end = mArray + index;
        Datatype* ptr = mArray + mCount;
        for (; ptr > end; ptr--)
            Swap(ptr - 1, ptr);
        *end = x;
        mCount++;
        return false;
    }

    bool Remove(u32 index)
    {
        if (index >= mCount)
            return true;
        mCount--;
        Datatype* ptr = mArray + index;
        Datatype* const end = mArray + mCount;
        for (; ptr < end; ptr++)
            Swap(ptr, ptr + 1);
        return false;
    }

    void Erase(void)
    {
        mCount = 0;
    }

/// VECTOR OPERATION METHODS
public:
    void Append(const Vector& that)
    {
        this->Resize(this->mLength + that.mLength);
        std::memcpy(this->mArray + this->mCount, that.mArray, DataSize(that.mCount));
        this->mCount += that.mCount;
    }

    void operator += (const Vector& that)
    {
        this->Append(that);
    }

    /// NOTE: only checks for list equivalency, not object equivalency - less rigorous than alt::Vector::operator==()
    bool Equals(const Vector& that) const
    {
        if (this->mCount != that.mCount)
            return false;
        const Datatype* this_ptr = this->mArray;
        const Datatype* that_ptr = that.mArray;
        const Datatype* const this_end = this_ptr + this->mCount;
        for (; this_ptr < this_end; this_ptr++, that_ptr++)
            if (*this_ptr != *that_ptr)
                return false;
        return true;
    }

    /// NOTE: checks for object equivalency - much more rigorous than alt::Vector::Equals()
    bool operator == (const Vector& that) const
    {
        if (this->mLength    != that.mLength ||
            this->mGrowth    != that.mGrowth ||
            this->mAllocator != that.mAllocator)
            return false;
        return this->Equals(that);
    }

    /// NOTE: returns the opposite of operator ==
    bool operator != (const Vector& that) const
    {
        return ! this->operator == (that);
    }

}; // end template class Vector

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end VECTOR_hpp
