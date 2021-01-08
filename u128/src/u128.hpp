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

#ifndef U128_hpp
#define U128_hpp

#include <iostream>

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"

namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class u128
{
////////////////////////////////////////////////////////////

    /// 128 bit unsigned integer MINIMUM
    /// Decimal         0
    /// Hexidecimal     0000 0000 0000 0000 0000 0000 0000 0000
    /// Binary          0000 ...
#   define u128_MIN ( alt::u128 { u64_MIN, u64_MIN } )

    /// 128 bit unsigned integer MAXIMUM
    /// Decimal         340,282,366,920,938,463,463,374,607,431,768,211,456
    /// Hexidecimal     FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
    /// Binary          1111 ...
#   define u128_MAX ( alt::u128 { u64_MAX, u64_MAX } )

////////////////////////////////////////////////////////////
private:

    /// PRIVATE MEMBER VARIABLES
    u64 UpperHalf_;
    u64 LowerHalf_;

////////////////////////////////////////////////////////////
public:

    /// DEFAULT CONSTRUCTOR & DESTRUCTOR
    u128()  noexcept;
    ~u128() noexcept;

    /// OVERLOADED CONSTRUCTORS
    u128(const u64& lowerhalf)                       noexcept;
    u128(const u64& upperhalf, const u64& lowerhalf) noexcept;

    /// COPY CONSTRUCTOR & COPY ASSIGNMENT OPERATORS
    u128(const u128& copy)              noexcept;
    u128& operator = (const u128& copy) noexcept;
    u128& operator = (const u64&  copy) noexcept;

////////////////////////////////////////////////////////////
public:

    /// CASTING OPERATOR, NEGATIVE OPERATOR
    u64  operator + (void) const noexcept;
    // operator - () = delete;

////////////////////////////////////////////////////////////
public:

    /// INCREMENT & DECREMENT
    u128& operator ++ (void) noexcept;
    u128  operator ++ (int)  noexcept;
    u128& operator -- (void) noexcept;
    u128  operator -- (int)  noexcept;

////////////////////////////////////////////////////////////
public:

    /// BITWISE OPERATORS
    u128 operator ~  (void)               const noexcept;
    u128 operator &  (const u128& andarg) const noexcept;
    u128 operator &  (const u64&  andarg) const noexcept;
    u128 operator |  (const u128& orarg)  const noexcept;
    u128 operator |  (const u64&  orarg)  const noexcept;
    u128 operator ^  (const u128& xorarg) const noexcept;
    u128 operator ^  (const u64&  xorarg) const noexcept;
    u128 operator << (const u8&   bits)   const noexcept;
    u128 operator >> (const u8&   bits)   const noexcept;

////////////////////////////////////////////////////////////
public:

    /// ARITHMETIC OPERATORS
    u128 operator + (const u128& addend)     const noexcept;
    u128 operator + (const u64&  addend)     const noexcept;
    u128 operator - (const u128& subtrahend) const noexcept;
    u128 operator - (const u64&  subtrahend) const noexcept;
    u128 operator *       (u128  multiplier) const noexcept;
    u128 operator *       (u64   multiplier) const noexcept;
    u128 operator / (const u128& divisor)    const;
    u128 operator / (const u64&  divisor)    const;
    u128 operator % (const u128& divisor)    const noexcept;
    u128 operator % (const u64&  divisor)    const noexcept;

////////////////////////////////////////////////////////////
public:

    /// BITWISE ASSIGNMENT OPERATORS
    u128& operator &=  (const u128& andarg) noexcept;
    u128& operator &=  (const u64&  andarg) noexcept;
    u128& operator |=  (const u128& orarg)  noexcept;
    u128& operator |=  (const u64&  orarg)  noexcept;
    u128& operator ^=  (const u128& xorarg) noexcept;
    u128& operator ^=  (const u64&  xorarg) noexcept;
    u128& operator <<= (const u8&   bits)   noexcept;
    u128& operator >>= (const u8&   bits)   noexcept;

////////////////////////////////////////////////////////////
public:

    /// ARITHMETIC ASSIGNMENT OPERATORS
    u128& operator += (const u128& addend)     noexcept;
    u128& operator += (const u64&  addend)     noexcept;
    u128& operator -= (const u128& subtrahend) noexcept;
    u128& operator -= (const u64&  subtrahend) noexcept;
    u128& operator *=        (u128 multiplier) noexcept;
    u128& operator *=        (u64  multiplier) noexcept;
    u128& operator /= (const u128& divisor);
    u128& operator /= (const u64&  divisor);
    u128& operator %= (const u128& divisor)    noexcept;
    u128& operator %= (const u64&  divisor)    noexcept;

////////////////////////////////////////////////////////////
public:

    /// LOGICAL OPERATORS
    bool operator !  (void)               noexcept;
    bool operator && (const u128& andarg) noexcept;
    bool operator && (const u64&  andarg) noexcept;
    bool operator && (bool andarg)        noexcept;
    bool operator || (const u128& andarg) noexcept;
    bool operator || (const u64&  andarg) noexcept;
    bool operator || (bool andarg)        noexcept;

////////////////////////////////////////////////////////////
public:

    /// COMPARISON OPERATORS
    bool operator == (const u128& that) noexcept;
    bool operator == (const u64&  that) noexcept;
    bool operator != (const u128& that) noexcept;
    bool operator != (const u64&  that) noexcept;
    bool operator <  (const u128& that) noexcept;
    bool operator <  (const u64&  that) noexcept;
    bool operator >  (const u128& that) noexcept;
    bool operator >  (const u64&  that) noexcept;
    bool operator <= (const u128& that) noexcept;
    bool operator <= (const u64&  that) noexcept;
    bool operator >= (const u128& that) noexcept;
    bool operator >= (const u64&  that) noexcept;

////////////////////////////////////////////////////////////
public:

    /// MEMBER ACCESS OPERATORS
    // u8 operator [] (const u8 i) const noexcept;
    // operator *   () = delete;
    // operator &   () = delete;
    // operator ->  () = delete;
    // operator .   () = delete;
    // operator ->* () = delete;
    // operator .*  () = delete;

////////////////////////////////////////////////////////////
public:

    /// CASTING OPERATORS
    explicit operator bool() const noexcept;
    explicit operator i8()   const noexcept;
    explicit operator u8()   const noexcept;
    explicit operator i16()  const noexcept;
    explicit operator u16()  const noexcept;
    explicit operator i32()  const noexcept;
    explicit operator u32()  const noexcept;
    explicit operator i64()  const noexcept;
    explicit operator u64()  const noexcept;

////////////////////////////////////////////////////////////
}; // end class u128

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

/// OSTREAM INTERFACE
std::ostream& operator << (std::ostream& OS, const alt::u128& num);

#endif // end U128_hpp
