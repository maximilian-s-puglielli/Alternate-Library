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
/// CREATED: 2021.08.06

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"

#include <cstring> // exclusively for std::memcpy() and std::memset()

namespace alt // Array belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Datatype, i64 _Capacity>
class Array
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// MEMBER VARIABLES
private:

	i64 _Count;
	Datatype _Array[_Capacity];

////////////////////////////////////////////////////////////////////////////////
/// DEFAULT CONSTRUCTOR & DESTRUCTOR
public:

Array() noexcept:
	_Count(0),
	_Array{0}
{}

virtual
~Array() noexcept
{}

////////////////////////////////////////////////////////////////////////////////
/// OVERLOADED CONSTRUCTORS
public:

explicit Array(const i64 init_count, Datatype* const init_array) noexcept:
	_Count(init_count),
	_Array{0}
{
	if (( this->_Count > 0      )&&
		( init_array != nullptr ))
		std::memcpy(this->_Array, init_array, Datasize(this->_Count));
}

////////////////////////////////////////////////////////////////////////////////
/// COPY CONSTRUCTOR, MOVE CONSTRUCTOR, & ASSIGNMENT OPERATOR
public:

Array(const Array& copy) noexcept:
	_Count(copy._Count),
	_Array{0}
{
	if (this->_Count > 0)
		std::memcpy(this->_Array, copy._Array, Datasize(this->_Count));
}

Array(Array&& move) noexcept:
	_Count(move._Count),
	_Array{0}
{
	if (this->_Count >= 0)
	{
		if (this->_Count > 0)
			std::memcpy(this->_Array, move._Array, Datasize(this->_Count));
		std::memset(move._Array, 0, Datasize(move._Count));
		move._Count = -1;
	}
}

Array& operator = (const Array& copy) noexcept
{
	this->_Count = copy._Count;
	if (this->_Count > 0)
		std::memcpy(this->_Array, copy._Array, Datasize(this->_Count));
}

Array& operator = (Array&& move) noexcept
{
	this->_Count = move._Count;
	if (this->_Count >= 0)
	{
		if (this->_Count > 0)
			std::memcpy(this->_Array, move._Array, Datasize(this->_Count));
		std::memset(move._Array, 0, Datasize(move._Count));
		move._Count = -1;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// SIZE & CAPACITY ACCESSORS
public:

u64 Datasize(const u64 num = 1) const noexcept
{
	return sizeof(Datatype) * num;
}

i64 Count(void) const noexcept
{
	return _Count;
}

i64 Capacity(void) const noexcept
{
	return _Capacity;
}

bool Empty(void) const noexcept
{
	return (_Count == 0);
}

bool Full(void) const noexcept
{
	return (_Count == _Capacity);
}

////////////////////////////////////////////////////////////////////////////////
/// MEMORY ACCESSORS & MODIFIERS
public:

const Datatype& At(const i64 index) const
{
	if (index < 0 || _Count <= index)
		throw alt::InvalidIndex();
	return _Array[index];
}

Datatype& At(const i64 index)
{
	if (index < 0 || _Count <= index)
		throw alt::InvalidIndex();
	return _Array[index];
}

const Datatype& operator [] (const i64 index) const noexcept
{
	return _Array[index];
}

/// WARN: this method can destroy the _Count invariant
Datatype& operator [] (const i64 index) noexcept
{
	return _Array[index];
}

/// NOTE: includes bounds checking, and cannot destroy the _Count invariant
bool Swap(const i64 index1st, const i64 index2nd) noexcept
{
	if (( index1st < 0 || _Count <= index1st )||
		( index2nd < 0 || _Count <= index2nd ))
		return true;
	_Swap(_Array + index1st, _Array + index2nd);
	return false;
}

/// NOTE: includes bounds checking, and cannot destroy the _Count invariant
bool Swap(Datatype* const ptr1st, Datatype* const ptr2nd) noexcept
{
	if ((ptr1st == nullptr)||
		(ptr2nd == nullptr))
		return true;
	{
		const i64 index1st = ptr1st - _Array;
		const i64 index2nd = ptr2nd - _Array;
		if (( index1st < 0 || _Count <= index1st )||
			( index2nd < 0 || _Count <= index2nd ))
			return true;
	}
	_Swap(ptr1st, ptr2nd);
	return false;
}

////////////////////////////////////////////////////////////////////////////////
/// SWAP HELPER METHOD
private:

/// WARN: this method can destroy the _Count invariant
void _Swap(Datatype* const ptr1st, Datatype* const ptr2nd) noexcept
{
	Datatype tmp = *ptr1st;
	*ptr1st      = *ptr2nd;
	*ptr2nd      = tmp;
}

////////////////////////////////////////////////////////////////////////////////
/// SEARCH METHODS
public:

bool Contains(const Datatype& x) const noexcept
{
	const Datatype* ptr = _Array;
	const Datatype* const end = ptr + _Count;
	for (; ptr < end; ptr++)
		if (*ptr == x)
			return true;
	return false;
}

i64 IndexOf(const Datatype& x) const noexcept
{
	const Datatype* ptr = _Array;
	for (i64 i = 0; i < _Count; ptr++, i++)
		if (*ptr == x)
			return i;
	return -1;
}

i64 LastIndexOf(const Datatype& x) const noexcept
{
	const Datatype* ptr = _Array + (_Count - 1);
	for (i64 i = _Count - 1; i >= 0; ptr--, i--)
		if (*ptr == x)
			return i;
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
/// CONTAINER METHODS
public:

bool Get(u32 index, Datatype& rtn) noexcept
{
	if (index < 0 || _Count <= index)
		return true;
	rtn = _Array[index];
	return Remove(index);
}

bool Push(const Datatype& x) noexcept
{
	if (Full())
		return true;
	Datatype* const end = _Array;
	Datatype* ptr = end + _Count;
	for (; ptr > end; ptr--)
		_Swap(ptr - 1, ptr);
	*end = x;
	_Count++;
	return false;
}

bool Enqueue(const Datatype& x) noexcept
{
	if (Full())
		return true;
	_Array[_Count++] = x;
	return false;
}

bool operator += (const Datatype& x) noexcept
{
	return Enqueue(x);
}

const Datatype& Peek(void) const
{
	return At(0);
}

Datatype& Peek(void)
{
	return At(0);
}

const Datatype& PeekBack(void) const
{
	return At(_Count - 1);
}

Datatype& PeekBack(void)
{
	return At(_Count - 1);
}

bool Pop(Datatype& rtn) noexcept
{
	return Get(0, rtn);
}

bool PopBack(Datatype& rtn) noexcept
{
	return Get(_Count - 1, rtn);
}

/// NOTE: index can be within the range [0, _Count], otherwise this method fails and returns true
bool Insert(u32 index, const Datatype& x) noexcept
{
	if (Full())
		return true;
	if (index < 0 || _Count <= index)
		return true;
	Datatype* const end = _Array + index;
	Datatype* ptr = _Array + _Count;
	for (; ptr > end; ptr--)
		_Swap(ptr - 1, ptr);
	*end = x;
	_Count++;
	return false;
}

bool Remove(const i64 index) noexcept
{
	if (index < 0 || _Count <= index)
		return true;
	_Count--;
	Datatype* ptr = _Array + index;
	Datatype* const end = _Array + _Count;
	for (; ptr < end; ptr++)
		_Swap(ptr, ptr + 1);
	return false;
}

void Erase(void) noexcept
{
	_Count = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// ARRAY OPERATION METHODS
public:

bool Equals(const Array& that) const noexcept
{
	if (this->_Count != that._Count)
		return false;
	const Datatype* this_ptr = this->_Array;
	const Datatype* that_ptr = that._Array;
	const Datatype* const this_end = this_ptr + this->_Count;
	for (; this_ptr < this_end; this_ptr++, that_ptr++)
		if (*this_ptr != *that_ptr)
			return false;
	return true;
}

bool operator == (const Array& that) const noexcept
{
	return this->Equals(that);
}

/// NOTE: returns the opposite of operator ==
bool operator != (const Array& that) const noexcept
{
	return ! this->operator == (that);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

#endif // end ARRAY_HPP
