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
/// CREATED: 2021.08.08

#ifndef INDEX_HPP
#define INDEX_HPP

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"

namespace alt // Index belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Index final
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// MEMBER VARIABLES
private:

	i64 _Value;

////////////////////////////////////////////////////////////////////////////////
/// CONSTRUCTORS, DESTRUCTORS, & ASSIGNMENT OPERATOR - DECLARATIONS
public:

/// DEFAULT
Index() noexcept;

/// OVERLOADED
Index(const i64 value) noexcept;
Index& operator = (const i64 value) noexcept;

/// COPY
Index(const Index& copy) noexcept;
Index& operator = (const Index& copy) noexcept;

/// MOVE
Index(Index&& move) noexcept;
Index& operator = (Index&& move) noexcept;

/// DESTRUCTOR
~Index() noexcept;

////////////////////////////////////////////////////////////////////////////////
/// METHOD - DECLARATIONS
public:

bool Valid(void) const noexcept;
u64 Value(void) const noexcept;

////////////////////////////////////////////////////////////////////////////////
/// UNARY OPERATOR - DECLARATIONS
public:

explicit operator bool (void) const noexcept;
explicit operator i64 (void) const noexcept;
explicit operator u64 (void) const noexcept;

bool operator ! (void) const noexcept;
auto operator & (void) = delete;
Index operator ~ (void) const noexcept;
auto operator * (void) = delete;
auto operator + (void) = delete;
Index operator - (void) const noexcept;

Index& operator ++ (void) noexcept;
Index operator ++ (int) noexcept;
Index& operator -- (void) noexcept;
Index operator -- (int) noexcept;

////////////////////////////////////////////////////////////////////////////////
/// ASSIGNMENT OPERATOR - DECLARATIONS
public:

Index& operator += (const Index& that) noexcept;
Index& operator -= (const Index& that) noexcept;
Index& operator *= (const Index& that) noexcept;
Index& operator /= (const Index& that) noexcept;
Index& operator %= (const Index& that) noexcept;
Index& operator &= (const Index& that) noexcept;
Index& operator |= (const Index& that) noexcept;
Index& operator ^= (const Index& that) noexcept;
Index& operator <<= (const Index& that) noexcept;
Index& operator >>= (const Index& that) noexcept;

Index& operator += (const i64 value) noexcept;
Index& operator -= (const i64 value) noexcept;
Index& operator *= (const i64 value) noexcept;
Index& operator /= (const i64 value) noexcept;
Index& operator %= (const i64 value) noexcept;
Index& operator &= (const i64 value) noexcept;
Index& operator |= (const i64 value) noexcept;
Index& operator ^= (const i64 value) noexcept;
Index& operator <<= (const i64 value) noexcept;
Index& operator >>= (const i64 value) noexcept;

friend i64& operator += (i64& lhs, const Index& rhs) noexcept;
friend i64& operator -= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator *= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator /= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator %= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator &= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator |= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator ^= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator <<= (i64& lhs, const Index& rhs) noexcept;
friend i64& operator >>= (i64& lhs, const Index& rhs) noexcept;

////////////////////////////////////////////////////////////////////////////////
/// COMPARISON OPERATOR - DECLARATIONS
public:

bool operator == (const Index& that) const noexcept;
bool operator != (const Index& that) const noexcept;
bool operator < (const Index& that) const noexcept;
bool operator > (const Index& that) const noexcept;
bool operator <= (const Index& that) const noexcept;
bool operator >= (const Index& that) const noexcept;

bool operator == (const i64 value) const noexcept;
bool operator != (const i64 value) const noexcept;
bool operator < (const i64 value) const noexcept;
bool operator > (const i64 value) const noexcept;
bool operator <= (const i64 value) const noexcept;
bool operator >= (const i64 value) const noexcept;

friend bool operator == (const i64& lhs, const Index& rhs) noexcept;
friend bool operator != (const i64& lhs, const Index& rhs) noexcept;
friend bool operator < (const i64& lhs, const Index& rhs) noexcept;
friend bool operator > (const i64& lhs, const Index& rhs) noexcept;
friend bool operator <= (const i64& lhs, const Index& rhs) noexcept;
friend bool operator >= (const i64& lhs, const Index& rhs) noexcept;

////////////////////////////////////////////////////////////////////////////////
/// MEMBER ACCESS OPERATOR - DECLARATIONS
public:

auto operator [] (Index) = delete;
auto operator [] (Index&) = delete;
auto operator [] (i64) = delete;
auto operator -> (void) = delete;
auto operator ->* (Index) = delete;
auto operator ->* (Index&) = delete;
auto operator ->* (i64) = delete;

////////////////////////////////////////////////////////////////////////////////
/// MISCELLANEOUS OPERATOR - DECLARATIONS
public:

auto operator , (Index) = delete;
auto operator , (Index&) = delete;
auto operator , (i64) = delete;

u64 operator () (void) const noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end class Index final

/// NAME ALIAS
typedef Index Count;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CONSTRUCTORS, DESTRUCTORS, & ASSIGNMENT OPERATOR - INLINE DEFINITIONS

inline Index::Index() noexcept:
	_Value(0)
{}

inline Index::Index(const i64 value) noexcept:
	_Value(value)
{}

inline Index& Index::operator = (const i64 value) noexcept
{
	_Value = value;
}

inline Index::Index(const Index& copy) noexcept:
	_Value(copy._Value)
{}

inline Index& Index::operator = (const Index& copy) noexcept
{
	_Value = copy._Value;
}

inline Index::Index(Index&& move) noexcept:
	_Value(move._Value)
{
	move._Value = -1;
}

inline Index& Index::operator = (Index&& move) noexcept
{
	_Value = move._Value;
	move._Value = -1;
}

inline Index::~Index() noexcept
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// METHOD - INLINE DEFINITIONS

inline bool Index::Valid(void) const noexcept
{
	return _Value != -1;
}

inline u64 Index::Value(void) const noexcept
{
	return _Value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// UNARY OPERATOR - INLINE DEFINITIONS

inline Index::operator bool (void) const noexcept
{
	return Valid();
}

inline Index::operator i64 (void) const noexcept
{
	return _Value;
}

inline Index::operator u64 (void) const noexcept
{
	return _Value;
}

inline bool Index::operator ! (void) const noexcept
{
	return ! Valid();
}

inline Index Index::operator ~ (void) const noexcept
{
	return { ~ _Value };
}

inline Index Index::operator - (void) const noexcept
{
	return { - _Value };
}

inline Index& Index::operator ++ (void) noexcept
{
	_Value++;
	return *this;
}

inline Index Index::operator ++ (int) noexcept
{
	Index temp = *this;
	++(*this);
	return temp;
}

inline Index& Index::operator -- (void) noexcept
{
	_Value--;
	return *this;
}

inline Index Index::operator -- (int) noexcept
{
	Index temp = *this;
	--(*this);
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ASSIGNMENT OPERATOR - INLINE DEFINITIONS

inline Index& Index::operator += (const Index& that) noexcept
{
	this->_Value += that._Value;
	return *this;
}

inline Index& Index::operator -= (const Index& that) noexcept
{
	this->_Value -= that._Value;
	return *this;
}

inline Index& Index::operator *= (const Index& that) noexcept
{
	this->_Value *= that._Value;
	return *this;
}

inline Index& Index::operator /= (const Index& that) noexcept
{
	this->_Value /= that._Value;
	return *this;
}

inline Index& Index::operator %= (const Index& that) noexcept
{
	this->_Value %= that._Value;
	return *this;
}

inline Index& Index::operator &= (const Index& that) noexcept
{
	this->_Value &= that._Value;
	return *this;
}

inline Index& Index::operator |= (const Index& that) noexcept
{
	this->_Value |= that._Value;
	return *this;
}

inline Index& Index::operator ^= (const Index& that) noexcept
{
	this->_Value ^= that._Value;
	return *this;
}

inline Index& Index::operator <<= (const Index& that) noexcept
{
	this->_Value <<= that._Value;
	return *this;
}

inline Index& Index::operator >>= (const Index& that) noexcept
{
	this->_Value >>= that._Value;
	return *this;
}

inline Index& Index::operator += (const i64 value) noexcept
{
	_Value += value;
	return *this;
}

inline Index& Index::operator -= (const i64 value) noexcept
{
	_Value -= value;
	return *this;
}

inline Index& Index::operator *= (const i64 value) noexcept
{
	_Value *= value;
	return *this;
}

inline Index& Index::operator /= (const i64 value) noexcept
{
	_Value /= value;
	return *this;
}

inline Index& Index::operator %= (const i64 value) noexcept
{
	_Value %= value;
	return *this;
}

inline Index& Index::operator &= (const i64 value) noexcept
{
	_Value &= value;
	return *this;
}

inline Index& Index::operator |= (const i64 value) noexcept
{
	_Value |= value;
	return *this;
}

inline Index& Index::operator ^= (const i64 value) noexcept
{
	_Value ^= value;
	return *this;
}

inline Index& Index::operator <<= (const i64 value) noexcept
{
	_Value <<= value;
	return *this;
}

inline Index& Index::operator >>= (const i64 value) noexcept
{
	_Value >>= value;
	return *this;
}

inline i64& operator += (i64& lhs, const Index& rhs) noexcept
{
	lhs += rhs._Value;
	return lhs;
}

inline i64& operator -= (i64& lhs, const Index& rhs) noexcept
{
	lhs -= rhs._Value;
	return lhs;
}

inline i64& operator *= (i64& lhs, const Index& rhs) noexcept
{
	lhs *= rhs._Value;
	return lhs;
}

inline i64& operator /= (i64& lhs, const Index& rhs) noexcept
{
	lhs /= rhs._Value;
	return lhs;
}

inline i64& operator %= (i64& lhs, const Index& rhs) noexcept
{
	lhs %= rhs._Value;
	return lhs;
}

inline i64& operator &= (i64& lhs, const Index& rhs) noexcept
{
	lhs &= rhs._Value;
	return lhs;
}

inline i64& operator |= (i64& lhs, const Index& rhs) noexcept
{
	lhs |= rhs._Value;
	return lhs;
}

inline i64& operator ^= (i64& lhs, const Index& rhs) noexcept
{
	lhs ^= rhs._Value;
	return lhs;
}

inline i64& operator <<= (i64& lhs, const Index& rhs) noexcept
{
	lhs <<= rhs._Value;
	return lhs;
}

inline i64& operator >>= (i64& lhs, const Index& rhs) noexcept
{
	lhs >>= rhs._Value;
	return lhs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// COMPARISON OPERATOR - INLINE DEFINITIONS

inline bool Index::operator == (const Index& that) const noexcept
{
	return this->_Value == that._Value;
}

inline bool Index::operator != (const Index& that) const noexcept
{
	return this->_Value != that._Value;
}

inline bool Index::operator < (const Index& that) const noexcept
{
	return this->_Value < that._Value;
}

inline bool Index::operator > (const Index& that) const noexcept
{
	return this->_Value > that._Value;
}

inline bool Index::operator <= (const Index& that) const noexcept
{
	return this->_Value <= that._Value;
}

inline bool Index::operator >= (const Index& that) const noexcept
{
	return this->_Value >= that._Value;
}

inline bool Index::operator == (const i64 value) const noexcept
{
	return _Value == value;
}

inline bool Index::operator != (const i64 value) const noexcept
{
	return _Value != value;
}

inline bool Index::operator < (const i64 value) const noexcept
{
	return _Value < value;
}

inline bool Index::operator > (const i64 value) const noexcept
{
	return _Value > value;
}

inline bool Index::operator <= (const i64 value) const noexcept
{
	return _Value <= value;
}

inline bool Index::operator >= (const i64 value) const noexcept
{
	return _Value >= value;
}

inline bool operator == (const i64& lhs, const Index& rhs) noexcept
{
	return lhs == rhs._Value;
}

inline bool operator != (const i64& lhs, const Index& rhs) noexcept
{
	return lhs != rhs._Value;
}

inline bool operator < (const i64& lhs, const Index& rhs) noexcept
{
	return lhs < rhs._Value;
}

inline bool operator > (const i64& lhs, const Index& rhs) noexcept
{
	return lhs > rhs._Value;
}

inline bool operator <= (const i64& lhs, const Index& rhs) noexcept
{
	return lhs <= rhs._Value;
}

inline bool operator >= (const i64& lhs, const Index& rhs) noexcept
{
	return lhs >= rhs._Value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// MISCELLANEOUS OPERATOR - INLINE DEFINITIONS

inline u64 Index::operator () (void) const noexcept
{
	return _Value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ARITHMETIC OPERATORS

inline alt::Index operator + (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs += rhs;
	return lhs;
}

inline alt::Index operator + (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs += rhs;
	return lhs;
}

inline alt::i64 operator + (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs += rhs;
	return lhs;
}

inline alt::Index operator - (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs -= rhs;
	return lhs;
}

inline alt::Index operator - (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs -= rhs;
	return lhs;
}

inline alt::Index operator - (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs -= rhs;
	return lhs;
}

inline alt::Index operator * (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs *= rhs;
	return rhs;
}

inline alt::Index operator * (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs *= rhs;
	return rhs;
}

inline alt::Index operator * (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs *= rhs;
	return rhs;
}

inline alt::Index operator / (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs /= rhs;
	return lhs;
}

inline alt::Index operator / (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs /= rhs;
	return lhs;
}

inline alt::Index operator / (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs /= rhs;
	return lhs;
}

inline alt::Index operator % (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs %= rhs;
	return lhs;
}

inline alt::Index operator % (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs %= rhs;
	return lhs;
}

inline alt::Index operator % (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs %= rhs;
	return lhs;
}

inline alt::Index operator & (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs &= rhs;
	return lhs;
}

inline alt::Index operator & (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs &= rhs;
	return lhs;
}

inline alt::Index operator & (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs &= rhs;
	return lhs;
}

inline alt::Index operator | (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs |= rhs;
	return lhs;
}

inline alt::Index operator | (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs |= rhs;
	return lhs;
}

inline alt::Index operator | (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs |= rhs;
	return lhs;
}

inline alt::Index operator ^ (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs ^= rhs;
	return lhs;
}

inline alt::Index operator ^ (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs ^= rhs;
	return lhs;
}

inline alt::Index operator ^ (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs ^= rhs;
	return lhs;
}

inline alt::Index operator << (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs <<= rhs;
	return lhs;
}

inline alt::Index operator << (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs <<= rhs;
	return lhs;
}

inline alt::Index operator << (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs <<= rhs;
	return lhs;
}

inline alt::Index operator >> (alt::Index lhs, const alt::Index& rhs) noexcept
{
	lhs >>= rhs;
	return lhs;
}

inline alt::Index operator >> (alt::Index lhs, const alt::i64 rhs) noexcept
{
	lhs >>= rhs;
	return lhs;
}

inline alt::Index operator >> (alt::i64 lhs, const alt::Index& rhs) noexcept
{
	lhs >>= rhs;
	return lhs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // end INDEX_HPP
