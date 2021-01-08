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

#include "u128.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// DEFAULT CONSTRUCTOR & DESTRUCTOR

alt::u128::u128() noexcept:
    UpperHalf_(0),
    LowerHalf_(0)
{}

alt::u128::~u128() noexcept
{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// OVERLOADED CONSTRUCTORS

alt::u128::u128(const u64& lowerhalf) noexcept:
    UpperHalf_(0),
    LowerHalf_(lowerhalf)
{}

alt::u128::u128(const u64& upperhalf, const u64& lowerhalf) noexcept:
    UpperHalf_(upperhalf),
    LowerHalf_(lowerhalf)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// COPY CONSTRUCTOR & ASSIGNMENT OPERATOR

alt::u128::u128(const u128& copy) noexcept:
    UpperHalf_(copy.UpperHalf_),
    LowerHalf_(copy.LowerHalf_)
{}

alt::u128& alt::u128::operator = (const alt::u128& copy) noexcept
{
    UpperHalf_ = copy.UpperHalf_;
    LowerHalf_ = copy.LowerHalf_;
    return *this;
}

alt::u128& alt::u128::operator = (const u64& copy) noexcept
{
    UpperHalf_ = 0;
    LowerHalf_ = copy;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// CASTING OPERATOR

alt::u64 alt::u128::operator + (void) const noexcept
{
    return LowerHalf_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// INCREMENT & DECREMENT

alt::u128& alt::u128::operator ++ (void) noexcept
{
    u64 overflow = LowerHalf_;
    LowerHalf_++;
    if (overflow > LowerHalf_)
        UpperHalf_++;
    return *this;
}

alt::u128 alt::u128::operator ++ (int) noexcept
{
    u128 rtn = *this;
    this->LowerHalf_++;
    if (rtn.LowerHalf_ > this->LowerHalf_)
        this->UpperHalf_++;
    return rtn;
}

alt::u128& alt::u128::operator -- (void) noexcept
{
    u64 overflow = LowerHalf_;
    LowerHalf_--;
    if (overflow < LowerHalf_)
        UpperHalf_--;
    return *this;
}

alt::u128 alt::u128::operator -- (int) noexcept
{
    u128 rtn = *this;
    this->LowerHalf_--;
    if (rtn.LowerHalf_ < this->LowerHalf_)
        this->UpperHalf_--;
    return rtn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// BITWISE OPERATORS

alt::u128 alt::u128::operator ~ (void) const noexcept
{
    return u128
    {
        ~(UpperHalf_),
        ~(LowerHalf_)
    };
}

alt::u128 alt::u128::operator & (const alt::u128& andarg) const noexcept
{
    return u128
    {
        (this->UpperHalf_ & andarg.UpperHalf_),
        (this->LowerHalf_ & andarg.LowerHalf_)
    };
}

alt::u128 alt::u128::operator & (const u64& andarg) const noexcept
{
    return u128
    {
        0,
        (LowerHalf_ & andarg)
    };
}

alt::u128 alt::u128::operator | (const alt::u128& orarg) const noexcept
{
    return u128
    {
        (this->UpperHalf_ | orarg.UpperHalf_),
        (this->LowerHalf_ | orarg.LowerHalf_)
    };
}

alt::u128 alt::u128::operator | (const u64& orarg) const noexcept
{
    return u128
    {
        UpperHalf_,
        (LowerHalf_ | orarg)
    };
}

alt::u128 alt::u128::operator ^ (const alt::u128& xorarg) const noexcept
{
    return u128
    {
        (this->UpperHalf_ ^ xorarg.UpperHalf_),
        (this->LowerHalf_ ^ xorarg.LowerHalf_)
    };
}

alt::u128 alt::u128::operator ^ (const u64& xorarg) const noexcept
{
    return u128
    {
        (this->UpperHalf_ ^ 0),
        (this->LowerHalf_ ^ xorarg)
    };
}

alt::u128 alt::u128::operator << (const u8& bits) const noexcept
{
    if (! bits)
        return u128 { *this };
    if (bits >= 128)
        return u128 { 0, 0 };
    if (bits >= 64)
        return u128 { LowerHalf_ << (bits - 64), 0 };
    u64 trans = LowerHalf_ >> (64 - bits);
    return u128 { (UpperHalf_ << bits) | trans, LowerHalf_ << bits };
}

alt::u128 alt::u128::operator >> (const u8& bits) const noexcept
{
    if (! bits)
        return u128 { *this };
    if (bits >= 128)
        return u128 { 0, 0 };
    if (bits >= 64)
        return u128 { 0, UpperHalf_ >> (bits - 64) };
    u64 trans = UpperHalf_ << (64 - bits);
    return u128 { UpperHalf_ >> bits, (LowerHalf_ >> bits) | trans };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ARITHMETIC OPERATORS

alt::u128 alt::u128::operator + (const alt::u128& addend) const noexcept
{
    u128 rtn
    {
        (this->UpperHalf_ + addend.UpperHalf_),
        (this->LowerHalf_ + addend.LowerHalf_)
    };
    if (rtn.LowerHalf_ < this->LowerHalf_)
        rtn.UpperHalf_++;
    return rtn;
}

alt::u128 alt::u128::operator + (const u64& addend) const noexcept
{
    u128 rtn
    {
        this->UpperHalf_,
        (this->LowerHalf_ + addend)
    };
    if (rtn.LowerHalf_ < this->LowerHalf_)
        rtn.UpperHalf_++;
    return rtn;
}

alt::u128 alt::u128::operator - (const alt::u128& subtrahend) const noexcept
{
    u128 rtn
    {
        (this->UpperHalf_ - subtrahend.UpperHalf_),
        (this->LowerHalf_ - subtrahend.LowerHalf_)
    };
    if (rtn.LowerHalf_ > this->LowerHalf_)
        rtn.UpperHalf_--;
    return rtn;
}

alt::u128 alt::u128::operator - (const u64& subtrahend) const noexcept
{
    u128 rtn
    {
        this->UpperHalf_,
        (this->LowerHalf_ - subtrahend)
    };
    if (rtn.LowerHalf_ > this->LowerHalf_)
        rtn.UpperHalf_--;
    return rtn;
}

alt::u128 alt::u128::operator * (alt::u128 multiplier) const noexcept
{
    u128 sum = 0;
    for (u32 shft = 0; (bool)(multiplier); multiplier >>= 1, shft++)
        if ( (bool)(multiplier & 0x1) )
            sum += this->operator<<(shft);
    return sum;
}

alt::u128 alt::u128::operator * (u64 multiplier) const noexcept
{
    u128 sum = 0;
    for (u32 shft = 0; (bool)(multiplier); multiplier >>= 1, shft++)
        if ( (bool)(multiplier & 0x1) )
            sum += this->operator<<(shft);
    return sum;
}

alt::u128 alt::u128::operator / (const alt::u128& divisor) const
{
    if (! divisor)
        throw DivideByZero {};
    u128 quotient = 0, remainder = *this;
    for (; remainder >= divisor; ++quotient, remainder -= divisor);
    return quotient;
}

alt::u128 alt::u128::operator / (const u64& divisor) const
{
    if (! divisor)
        throw DivideByZero {};
    u128 quotient = 0, remainder = *this;
    for (; remainder >= divisor; ++quotient, remainder -= divisor);
    return quotient;
}

alt::u128 alt::u128::operator % (const u128& divisor) const noexcept
{
    if (! divisor)
        return u128 { *this };
    u128 remainder = *this;
    for (; remainder >= divisor; remainder -= divisor);
    return remainder;
}

alt::u128 alt::u128::operator % (const u64& divisor) const noexcept
{
    if (! divisor)
        return u128 { *this };
    u128 remainder = *this;
    for (; remainder >= divisor; remainder -= divisor);
    return remainder;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// BITWISE ASSIGNMENT OPERATORS

alt::u128& alt::u128::operator &= (const alt::u128& andarg) noexcept
{
    this->LowerHalf_ &= andarg.LowerHalf_;
    this->UpperHalf_ &= andarg.UpperHalf_;
    return *this;
}

alt::u128& alt::u128::operator &= (const u64& andarg) noexcept
{
    LowerHalf_ &= andarg;
    UpperHalf_ = 0;
    return *this;
}

alt::u128& alt::u128::operator |= (const alt::u128& orarg) noexcept
{
    this->LowerHalf_ |= orarg.LowerHalf_;
    this->UpperHalf_ |= orarg.UpperHalf_;
    return *this;
}

alt::u128& alt::u128::operator |= (const u64& orarg) noexcept
{
    LowerHalf_ |= orarg;
    return *this;
}

alt::u128& alt::u128::operator ^= (const alt::u128& xorarg) noexcept
{
    this->LowerHalf_ ^= xorarg.LowerHalf_;
    this->UpperHalf_ ^= xorarg.UpperHalf_;
    return *this;
}

alt::u128& alt::u128::operator ^= (const u64& xorarg) noexcept
{
    LowerHalf_ ^= xorarg;
    UpperHalf_ ^= 0;
    return *this;
}

alt::u128& alt::u128::operator <<= (const u8& bits) noexcept
{
    if (bits >= 128)
    {
        UpperHalf_ = 0;
        LowerHalf_ = 0;
    }
    else if (bits >= 64)
    {
        UpperHalf_ = LowerHalf_ << (bits - 64);
        LowerHalf_ = 0;
    }
    else if (bits)
    {
        UpperHalf_ <<= bits;
        UpperHalf_ |=  LowerHalf_ >> (64 - bits);
        LowerHalf_ <<= bits;
    }
    return *this;
}

alt::u128& alt::u128::operator >>= (const u8& bits) noexcept
{
    if (bits >= 128)
    {
        LowerHalf_ = 0;
        UpperHalf_ = 0;
    }
    else if (bits >= 64)
    {
        LowerHalf_ = UpperHalf_ >> (bits - 64);
        UpperHalf_ = 0;
    }
    else if (bits)
    {
        LowerHalf_ >>= bits;
        LowerHalf_ |=  UpperHalf_ << (64 - bits);
        UpperHalf_ >>= bits;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ARITHMETIC ASSIGNMENT OPERATORS

alt::u128& alt::u128::operator += (const alt::u128& addend) noexcept
{
    u64 overflow = this->LowerHalf_;
    this->LowerHalf_ += addend.LowerHalf_;
    this->UpperHalf_ += addend.UpperHalf_;
    if (overflow > this->LowerHalf_)
        this->UpperHalf_++;
    return *this;
}

alt::u128& alt::u128::operator += (const u64& addend) noexcept
{
    u64 overflow = this->LowerHalf_;
    this->LowerHalf_ += addend;
    if (overflow > this->LowerHalf_)
        this->UpperHalf_++;
    return *this;
}

alt::u128& alt::u128::operator -= (const alt::u128& subtrahend) noexcept
{
    u64 overflow = this->LowerHalf_;
    this->LowerHalf_ -= subtrahend.LowerHalf_;
    this->UpperHalf_ -= subtrahend.UpperHalf_;
    if (overflow < this->LowerHalf_)
        this->UpperHalf_--;
    return *this;
}

alt::u128& alt::u128::operator -= (const u64& subtrahend) noexcept
{
    u64 overflow = this->LowerHalf_;
    this->LowerHalf_ -= subtrahend;
    if (overflow < this->LowerHalf_)
        this->UpperHalf_--;
    return *this;
}

alt::u128& alt::u128::operator *= (alt::u128 multiplier) noexcept
{
    u128 sum = 0;
    for (u32 shft = 0; (bool)(multiplier); multiplier >>= 1, shft++)
        if ( (bool)(multiplier & 0x1) )
            sum += this->operator<<(shft);
    this->operator=(sum);
    return *this;
}

alt::u128& alt::u128::operator *= (u64 multiplier) noexcept
{
    u128 sum = 0;
    for (u32 shft = 0; (bool)(multiplier); multiplier >>= 1, shft++)
        if ( (bool)(multiplier & 0x1) )
            sum += this->operator<<(shft);
    this->operator=(sum);
    return *this;
}

alt::u128& alt::u128::operator /= (const alt::u128& divisor)
{
    if (! divisor)
        throw DivideByZero {};
    this->operator=(0);
    u128 remainder = *this;
    for (; remainder >= divisor; this->operator++(), remainder -= divisor);
    return *this;
}

alt::u128& alt::u128::operator /= (const u64& divisor)
{
    if (! divisor)
        throw DivideByZero {};
    this->operator=(0);
    u128 remainder = *this;
    for (; remainder >= divisor; this->operator++(), remainder -= divisor);
    return *this;
}

alt::u128& alt::u128::operator %= (const alt::u128& divisor) noexcept
{
    if ( (bool)(divisor) )
        for (; this->operator>=(divisor); this->operator-=(divisor));
    return *this;
}

alt::u128& alt::u128::operator %= (const u64& divisor) noexcept
{
    if ( (bool)(divisor) )
        for (; this->operator>=(divisor); this->operator-=(divisor));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// LOGICAL OPERATORS

bool alt::u128::operator ! (void) noexcept
{
    return ! (UpperHalf_ | LowerHalf_);
}

bool alt::u128::operator && (const alt::u128& andarg) noexcept
{
    return (this->UpperHalf_ | this->LowerHalf_) && (andarg.UpperHalf_ | andarg.LowerHalf_);
}

bool alt::u128::operator && (const u64& andarg) noexcept
{
    return (UpperHalf_ | LowerHalf_) && andarg;
}

bool alt::u128::operator && (bool andarg) noexcept
{
    return (UpperHalf_ | LowerHalf_) && andarg;
}

bool alt::u128::operator || (const alt::u128& andarg) noexcept
{
    return (this->UpperHalf_ | this->LowerHalf_) || (andarg.UpperHalf_ | andarg.LowerHalf_);
}

bool alt::u128::operator || (const u64& andarg) noexcept
{
    return (UpperHalf_ | LowerHalf_) || andarg;
}

bool alt::u128::operator || (bool andarg) noexcept
{
    return (UpperHalf_ | LowerHalf_) || andarg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// COMPARISON OPERATORS

bool alt::u128::operator == (const alt::u128& that) noexcept
{
    return (this->UpperHalf_ == that.UpperHalf_) && (this->LowerHalf_ == that.LowerHalf_);
}

bool alt::u128::operator == (const u64& that) noexcept
{
    return (! UpperHalf_) && (LowerHalf_ == that);
}

bool alt::u128::operator != (const alt::u128& that) noexcept
{
    return ! this->operator==(that);
}

bool alt::u128::operator != (const u64& that) noexcept
{
    return ! this->operator==(that);
}

bool alt::u128::operator < (const alt::u128& that) noexcept
{
    if (this->UpperHalf_ < that.UpperHalf_) return true;
    if (this->UpperHalf_ > that.UpperHalf_) return false;
    if (this->LowerHalf_ < that.LowerHalf_) return true;
    if (this->LowerHalf_ > that.LowerHalf_) return false;
    return false;
}

bool alt::u128::operator < (const u64& that) noexcept
{
    if (UpperHalf_)        return false;
    if (LowerHalf_ < that) return true;
    if (LowerHalf_ > that) return false;
    return false;
}

bool alt::u128::operator > (const alt::u128& that) noexcept
{
    if (this->UpperHalf_ > that.UpperHalf_) return true;
    if (this->UpperHalf_ < that.UpperHalf_) return false;
    if (this->LowerHalf_ > that.LowerHalf_) return true;
    if (this->LowerHalf_ < that.LowerHalf_) return false;
    return false;
}

bool alt::u128::operator > (const u64& that) noexcept
{
    if (UpperHalf_)        return true;
    if (LowerHalf_ < that) return false;
    if (LowerHalf_ > that) return true;
    return false;
}

bool alt::u128::operator <= (const alt::u128& that) noexcept
{
    if (this->operator==(that))
        return true;
    return this->operator<(that);
}

bool alt::u128::operator <= (const u64& that) noexcept
{
    if (this->operator==(that))
        return true;
    return this->operator<(that);
}

bool alt::u128::operator >= (const alt::u128& that) noexcept
{
    if (this->operator==(that))
        return true;
    return this->operator>(that);
}

bool alt::u128::operator >= (const u64& that) noexcept
{
    if (this->operator==(that))
        return true;
    return this->operator>(that);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// CASTING OPERATORS

alt::u128::operator bool() const noexcept
{
    return (bool)(UpperHalf_ | LowerHalf_);
}

alt::u128::operator alt::i8() const noexcept
{
    return (i8)(LowerHalf_);
}

alt::u128::operator alt::u8() const noexcept
{
    return (u8)(LowerHalf_);
}

alt::u128::operator alt::i16() const noexcept
{
    return (i16)(LowerHalf_);
}

alt::u128::operator alt::u16() const noexcept
{
    return (u16)(LowerHalf_);
}

alt::u128::operator alt::i32() const noexcept
{
    return (i32)(LowerHalf_);
}

alt::u128::operator alt::u32() const noexcept
{
    return (u32)(LowerHalf_);
}

alt::u128::operator alt::i64() const noexcept
{
    return (i64)(LowerHalf_);
}

alt::u128::operator alt::u64() const noexcept
{
    return LowerHalf_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// OSTREAM INTERFACE

std::ostream& operator << (std::ostream& OS, const alt::u128& num)
{
    using namespace alt;
    READONLY iCHAR HEX[0x10] =
    {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'
    };
    bool open = false;
    for (i32 shft = 124; shft >= 0; shft -= 4)
    {
        u8 fourbits = ( (u8)(num>>shft) ) & 0xF;
        if (fourbits || open || ! shft)
        {
            open = true;
            OS << HEX[fourbits];
        }
    }
    return OS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
