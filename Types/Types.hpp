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

#ifndef TYPES_hpp
#define TYPES_hpp

/// PRIMITIVE DATATYPE ABBREVIATIONS ///////////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER // if we're using the Microsoft C++ Compiler (cl.exe)

/// 8 bit signed character
typedef signed char                iCHAR;
/// 8 bit unsigned character
typedef unsigned char              uCHAR;
/// wchar_t type definition
typedef wchar_t                    wCHAR;
/// size_t type definition
typedef size_t                     uSIZE;
/// 8 bit signed integer
typedef __int8                     i8;
/// 8 bit unsigned integer
typedef unsigned __int8            u8;
/// 16 bit signed integer
typedef __int16                    i16;
/// 16 bit unsigned integer
typedef unsigned __int16           u16;
/// 32 bit signed integer
typedef __int32                    i32;
/// 32 bit unsigned integer
typedef unsigned __int32           u32;
/// 64 bit signed integer
typedef __int64                    i64;
/// 64 bit unsigned integer
typedef unsigned __int64           u64;
/// 32 bit signed floating point
typedef float                      f32;
/// 64 bit signed floating point
typedef double                     f64;

#else // if we're using any other compiler

/// 8 bit signed character
typedef signed char                iCHAR;
/// 8 bit unsigned character
typedef unsigned char              uCHAR;
/// wchar_t type definition
typedef wchar_t                    wCHAR;
/// size_t type definition
typedef size_t                     uSIZE;
/// 8 bit signed integer
typedef signed char                i8;
/// 8 bit unsigned integer
typedef unsigned char              u8;
/// 16 bit signed integer
typedef short int                  i16;
/// 16 bit unsigned integer
typedef unsigned short int         u16;
/// 32 bit signed integer
typedef int                        i32;
/// 32 bit unsigned integer
typedef unsigned int               u32;
/// 64 bit signed integer
typedef long long int              i64;
/// 64 bit unsigned integer
typedef unsigned long long int     u64;
/// 32 bit signed floating point
typedef float                      f32;
/// 64 bit signed floating point
typedef double                     f64;

#endif // _MSC_VER

/**
*  char* preprocessor definition
*  This is a preprocessor definition (rather than a typedef) to prevent compiler discrepancies.
**/
#define STR char*

/// PRIMITIVE DATATYPE RANGE DEFINITIONS /////////////////////////////////////////////////////////////////////////

/// 8 bit signed character MINIMUM
/// Decimal         -128
/// Hexadecimal     80
/// Binary          1000 0000
#define iCHAR_MIN 0x80i8
/// 8 bit signed character MAXIMUM
/// Decimal         127
/// Hexadecimal     7F
/// Binary          0111 1111
#define iCHAR_MAX 0x7Fi8
/// 8 bit unsigned character MINIMUM
/// Decimal         0
/// Hexadecimal     00
/// Binary          0000 0000
#define uCHAR_MIN 0x00ui8
/// 8 bit unsigned character MAXIMUM
/// Decimal         255
/// Hexadecimal     FF
/// Binary          1111 1111
#define uCHAR_MAX 0xFFui8
/// 8 bit signed integer MINIMUM
/// Decimal         -128
/// Hexadecimal     80
/// Binary          1000 0000
#define i8_MIN 0x80i8
/// 8 bit signed integer MAXIMUM
/// Decimal         127
/// Hexadecimal     7F
/// Binary          0111 1111
#define i8_MAX 0x7Fi8
/// 8 bit unsigned integer MINIMUM
/// Decimal         0
/// Hexadecimal     00
/// Binary          0000 0000
#define u8_MIN 0x00ui8
/// 8 bit unsigned integer MAXIMUM
/// Decimal         255
/// Hexadecimal     FF
/// Binary          1111 1111
#define u8_MAX 0xFFui8
/// 16 bit signed integer MINIMUM
/// Decimal         -32768
/// Hexadecimal     8000
/// Binary          1000 0000 ...
#define i16_MIN 0x8000i16
/// 16 bit signed integer MAXIMUM
/// Decimal         32767
/// Hexadecimal     7FFF
/// Binary          0111 1111 ...
#define i16_MAX 0x7FFFi16
/// 16 bit unsigned integer MINIMUM
/// Decimal         0
/// Hexadecimal     0000
/// Binary          0000 ...
#define u16_MIN 0x0000ui16
/// 16 bit unsigned integer MAXIMUM
/// Decimal         65535
/// Hexadecimal     FFFF
/// Binary          1111 ...
#define u16_MAX 0xFFFFui16
/// 32 bit signed integer MINIMUM
/// Decimal         ‭-2147483648‬
/// Hexadecimal     8000 0000
/// Binary          1000 0000 ...
#define i32_MIN 0x80000000i32
/// 32 bit signed integer MAXIMUM
/// Decimal         2147483647
/// Hexadecimal     7FFF FFFF
/// Binary          0111 1111 ...
#define i32_MAX 0x7FFFFFFFi32
/// 32 bit unsigned integer MINIMUM
/// Decimal         0
/// Hexadecimal     0000 0000
/// Binary          0000 ...
#define u32_MIN 0x00000000ui32
/// 32 bit unsigned integer MAXIMUM
/// Decimal         4294967295‬
/// Hexadecimal     FFFF FFFF
/// Binary          1111 ...
#define u32_MAX 0xFFFFFFFFui32
/// 64 bit signed integer MINIMUM
/// Decimal         -9223372036854775808
/// Hexadecimal     8000 0000 0000 0000
/// Binary          1000 0000 ...
#define i64_MIN 0x8000000000000000i64
/// 64 bit signed integer MAXIMUM
/// Decimal         9223372036854775807
/// Hexadecimal     7FFF FFFF FFFF FFFF
/// Binary          0111 1111 ...
#define i64_MAX 0x7FFFFFFFFFFFFFFFi64
/// 64 bit unsigned integer MINIMUM
/// Decimal         0
/// Hexadecimal     0000 0000 0000 0000
/// Binary          0000 ...
#define u64_MIN 0x0000000000000000ui64
/// 64 bit unsigned integer MAXIMUM
/// Decimal         18446744073709551615
/// Hexadecimal     FFFF FFFF FFFF FFFF
/// Binary          1111 ...
#define u64_MAX 0xFFFFFFFFFFFFFFFFui64

#endif // end TYPES_hpp
