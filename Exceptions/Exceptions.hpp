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


#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "Keywords.hpp"
#include "Types.hpp"

namespace alt   // EXCEPTIONS for namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Errno
{
    SUCCESS        = 0,
    FAILURE        = 1,
    MALLOC_FAILURE = 2,
    INVALID_PARAM  = 3,
    INVALID_INDEX  = 4,
    DIVIDE_BY_ZERO = 5,
    INT_OVERFLOW   = 6
}; // end enum Errno



/// FAILURE = 1
EXCEPTION Except
{
/// MEMBER VARIABLES
private:
    const u8        Err_;
    const STR const Msg_;

/// CONSTRUCTORS
public:
    Except()                                     noexcept;
    Except(const STR const msg)                  noexcept;
    Except(const Errno err, const STR const msg) noexcept;

/// ACCESSORS
public:
    const Errno     Err(void) const noexcept;
    const STR const Msg(void) const noexcept;

}; // end EXCEPTION Except



/// MALLOC_FAILURE = 2
EXCEPTION MallocFailure:
    public Except
{
/// CONSTRUCTORS
public:
    MallocFailure()                    noexcept;
    MallocFailure(const STR const msg) noexcept;

}; // end EXCEPTION MallocFailure



/// INVALID_PARAM = 3
EXCEPTION InvalidParam:
    public Except
{
/// CONSTRUCTORS
public:
    InvalidParam()                    noexcept;
    InvalidParam(const STR const msg) noexcept;

}; // end EXCEPTION InvalidParam



/// INVALID_INDEX = 4
EXCEPTION InvalidIndex:
    public Except
{
/// CONSTRUCTORS
public:
    InvalidIndex()                    noexcept;
    InvalidIndex(const STR const msg) noexcept;

}; // end EXCEPTION InvalidIndex



/// DIVIDE_BY_ZERO = 5
EXCEPTION DivideByZero:
    public Except
{
/// CONSTRUCTORS
public:
    DivideByZero()                    noexcept;
    DivideByZero(const STR const msg) noexcept;

}; // end EXCEPTION InvalidIndex



/// INT_OVERFLOW = 6
EXCEPTION IntOverflow:
    public Except
{
/// CONSTRUCTORS
public:
    IntOverflow()                    noexcept;
    IntOverflow(const STR const msg) noexcept;

}; // end EXCEPTION IntOverflow

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt



/// EXCEPTION Except definitions

inline alt::Except::Except() noexcept:
    Err_((u8)(Errno::FAILURE)),
    Msg_("Except")
{}

inline alt::Except::Except(const STR const msg) noexcept:
    Err_((u8)(Errno::FAILURE)),
    Msg_(msg)
{}

inline alt::Except::Except(const alt::Errno err, const STR const msg) noexcept:
    Err_((u8)(err)),
    Msg_(msg)
{}

inline const alt::Errno alt::Except::Err(void) const noexcept
{
    return (alt::Errno)(Err_);
}

inline const STR const alt::Except::Msg(void) const noexcept
{
    return Msg_;
}



/// EXCEPTION MallocFailure definitions

inline alt::MallocFailure::MallocFailure() noexcept:
    Except(Errno::MALLOC_FAILURE, "MallocFailure")
{}

inline alt::MallocFailure::MallocFailure(const STR const msg) noexcept:
    Except(Errno::MALLOC_FAILURE, msg)
{}



/// EXCEPTION InvalidParam definitions

inline alt::InvalidParam::InvalidParam() noexcept:
    Except(Errno::INVALID_PARAM, "InvalidParam")
{}

inline alt::InvalidParam::InvalidParam(const STR const msg) noexcept:
    Except(Errno::INVALID_PARAM, msg)
{}



/// EXCEPTION InvalidIndex definitions

inline alt::InvalidIndex::InvalidIndex() noexcept:
    Except(Errno::INVALID_INDEX, "InvalidIndex")
{}

inline alt::InvalidIndex::InvalidIndex(const STR const msg) noexcept:
    Except(Errno::INVALID_INDEX, msg)
{}



/// EXCEPTION DivideByZero definitions

inline alt::DivideByZero::DivideByZero() noexcept:
    Except(Errno::DIVIDE_BY_ZERO, "DivideByZero")
{}

inline alt::DivideByZero::DivideByZero(const STR const msg) noexcept:
    Except(Errno::DIVIDE_BY_ZERO, msg)
{}



/// EXCEPTION IntOverflow definitions

inline alt::IntOverflow::IntOverflow() noexcept:
    Except(Errno::INT_OVERFLOW, "IntOverflow")
{}

inline alt::IntOverflow::IntOverflow(const STR const msg) noexcept:
    Except(Errno::INT_OVERFLOW, msg)
{}

#endif // end EXCEPTIONS_HPP
