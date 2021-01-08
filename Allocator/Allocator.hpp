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
/// AUTHOR:  Maximilian S Puglie (MSP)
/// CREATED: 2021.01.06

#ifndef ALLOCATOR_hpp
#define ALLOCATOR_hpp

#include <new>  // exclusively for std::bad_alloc

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"

namespace alt   // Allocator belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// AUTH: MSP
/// VISI: ::alt::Allocator
///
/// INFO: This class is an encapsulation of the new operator.  Its purpose is to control the allocation and
/// deallocation of heap memory.  This class is capable of separating the two actions of allocating and constructing
/// memory, although it is not usually recommended to do so.  This class is a singleton for the reason that it can be
/// templated and encapsulated by other container classes in the alternate template library.  This is the default
/// allocator used by all the containers in the alternate template library, therefore it is defined in namespace alt
/// (for alternate, as opposed to standard).
template <typename Datatype>
class Allocator
{
////////////////////////////////////////////////////////////
/// CONSTRUCTORS
public:

/// AUTH: MSP
/// VISI: public
///
/// INFO: This is the default constructor for the Allocator template class.
Allocator() noexcept
{}

/// AUTH: MSP
/// VISI: public
/// PRAM: copy (const Allocator&)
///
/// INFO: This is the copy & move constructor for the Allocator template class.
Allocator(const Allocator& copy) noexcept
{}

/// AUTH: MSP
/// VISI: public
///
/// INFO: This is the destructor for the Allocator template class.
~Allocator() noexcept
{}

////////////////////////////////////////////////////////////
/// METHODS
public:

/// AUTH: MSP
/// VISI: public
/// PRAM: num: u32 = 1
/// RTRN: u64
///
/// INFO: This method returns the number of bytes num Datatypes would be.
/// return sizeof(Datatype) * 'num';
///
/// NOTE: The parameter 'num' has a default value of 1.
u64 Datasize(u32 num = 1) const
{
    return sizeof(Datatype) * num;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: size: u32 ~ the number of Datatype objects to allocate
/// RTRN: Datatype* ~ the address of the array of allocated objects
///
/// INFO: This method either allocates an array of objects whose length is 'size' or a single object
/// depending on if 'size' is greater than or equal to one.
///
/// NOTE: This method can throw either an alt::InvalidParam or alt::MallocFailure exception.  Be prepared to handle
/// those exceptions should they be thrown.
///   - alt::InvalidParam will be thrown if 'size' == 0
///   - alt::MallocFailure will be thrown if the new operator throws the std::bad_alloc exception.
///
/// NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method
/// alt::Allocator::RawAllocate() which doesn't call a constructor when allocating memory.
///
/// NOTE: This method is guaranteed to either succeed and return a non-null pointer or fail and throw an exception.
/// It will never return a nullptr.
Datatype* Allocate(u32 size) const
{
    if (! size)
        throw alt::InvalidParam {};
    Datatype* rtn = nullptr;
    try
    {
        rtn = new Datatype[size];
    }
    catch (const std::bad_alloc& ba)
    {
        throw alt::MallocFailure {};
    }
    return rtn;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: size: u32 ~ the number of Datatype objects to allocate
/// RTRN: Datatype* ~ the address of the array of allocated objects
///
/// INFO: This method either allocates an array of objects whose length is 'size' or a single object
/// depending on if 'size' is greater than or equal to one.
///
/// NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be
/// prepared to handle a nullptr should one be returned.
///
/// NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method
/// alt::Allocator::RawMalloc() which doesn't call a constructor when allocating memory.
Datatype* Malloc(u32 size) const noexcept
{
    if (! size)
        return nullptr;
    Datatype* rtn = nullptr;
    try
    {
        rtn = new Datatype[size];
    }
    catch (const std::bad_alloc& ba)
    {
        return nullptr;
    }
    return rtn;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: size: u32 ~ the number of Datatype objects to allocate
/// RTRN: Datatype* ~ the address of the block of raw memory this method allocated
///
/// INFO: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of
/// bytes.
///
/// NOTE: This method can throw either an alt::InvalidParam or alt::MallocFailure exception.  Be prepared to handle
/// those exceptions should they be thrown.
///   - alt::InvalidParam will be thrown if size == 0
///   - alt::MallocFailure will be thrown if the new operator throws the std::bad_alloc exception.
///
/// NOTE: This method doesn't call a constructor when allocating memory, as opposed to the method
/// alt::Allocator::Allocate() which calls the default constructor of the Datatype objects it allocates.
///
/// NOTE: This method is guaranteed to either succeed and return a non-null pointer or fail and throw an exception.
/// It will never return a nullptr.
Datatype* RawAllocate(u32 size) const
{
    if (! size)
        throw alt::InvalidParam {};
    Datatype* rtn = nullptr;
    try
    {
        rtn = (Datatype*)(new u8[sizeof(Datatype) * size]);
    }
    catch (const std::bad_alloc& ba)
    {
        throw alt::MallocFailure {};
    }
    return rtn;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: size: u32 ~ the number of Datatype objects to allocate
/// RTRN: Datatype* ~ the address of the block of raw memory this method allocated
///
/// INFO: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of
/// bytes.
///
/// NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be
/// prepared to handle a nullptr should one be returned.
///
/// NOTE: This method doesn't call a constructor when allocating memory, as opposed to the method
/// alt::Allocator::Malloc() which calls the default constructor of the Datatype objects it allocates.
Datatype* RawMalloc(u32 size) const noexcept
{
    if (! size)
        return nullptr;
    Datatype* rtn = nullptr;
    try
    {
        rtn = (Datatype*)(new u8[sizeof(Datatype) * size]);
    }
    catch (const std::bad_alloc& ba)
    {
        return nullptr;
    }
    return rtn;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: objs: Datatype*& ~ the address of the array of objects to be deallocated
/// RTRN: void
///
/// INFO: This method deallocates the array of objects pointed to by the parameter 'objs'.
///
/// NOTE: The parameter 'objs' is passed by reference so that it can be set to nullptr after deallocation.
///
/// NOTE: This method calls the destructor on all the objects it deallocates, as opposed to
/// alt::Allocator::RawDeallocate() which does not call the destructor on any object it deallocates.
///
/// WARN: It is imperative to use this method to deallocate memory allocated using either the alt::Allocator::Allocate()
/// or alt::Allocator::Malloc() method.  DO NOT call this method on memory allocated using alt::Allocator::RawAllocate()
/// or alt::Allocator::RawMalloc().
void Deallocate(Datatype*& objs) const
{
    if (objs)
    {
        delete [] objs;
        objs = nullptr;
    }
}

/// AUTH: MSP
/// VISI: public
/// PRAM: block: Datatype*& ~ the address of the block of memory to be deallocated
/// RTRN: void
///
/// INFO: This method deallocates the block of memory pointed to by the parameter 'block'.
///
/// NOTE: The parameter 'block' is passed by reference so that it can be set to nullptr after deallocation.
///
/// NOTE: This method does not call the destructor on any object it deallocates, as opposed to
/// alt::Allocator::Deallocate() which calls the destructor on all the objects it deallocates.
///
/// WARN: It is imperative to use this method to deallocate memory allocated using either the
/// alt::Allocator::RawAllocate() or alt::Allocator::RawMalloc() method.  DO NOT call this method on memory allocated
/// using alt::Allocator::Allocate() or alt::Allocator::Malloc().
void RawDeallocate(Datatype*& block) const
{
    if (block)
    {
        delete [] (u8*)(block);
        block = nullptr;
    }
}

/// AUTH: MSP
/// VISI: public
/// PRAM: base: Datatype* ~ the address of the block of raw memory
/// PRAM: size: u32 = 1 ~ the number of Datatypes to be constructed
/// RTRN: void
///
/// INFO: The method calls the default constructor on all the Datatype objects up to 'size' starting at the
/// memory address 'base'.
///
/// NOTE: If 'base' == nullptr, this method will do nothing.
void Construct(Datatype* base, u32 size = 1) const
{
    if (! base)
        return;
    Datatype* ptr = base;
    Datatype* const end = ptr + size;
    for (; ptr < end; ptr++)
        new (ptr) Datatype;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: base: Datatype* ~ the address of the block of non-raw memory
/// PRAM: size: u32 = 1 ~ the number of Datatype objects to be constructed
/// RTRN: void
///
/// INFO: This method calls the destructor on all the Datatype objects up to 'size' starting at the memory
/// address 'base'.
///
/// NOTE: If 'base' == nullptr, this method will do nothing.
void Destruct(Datatype* base, u32 size = 1) const
{
    if (! base)
        return;
    Datatype* ptr = base;
    Datatype* const end = ptr + size;
    for (; ptr < end; ptr++)
        ptr->~Datatype();
}

////////////////////////////////////////////////////////////
/// OPERATORS
public:

/// AUTH: MSP
/// VISI: public
/// PRAM: copy: const Allocator&
/// RTRN: Allocator&
///
/// INFO: This is the copy & move assignment operator for the Allocator template class.
Allocator& operator = (const Allocator& copy) noexcept
{}

/// AUTH: MSP
/// VISI: public
/// PRAM: that: const Allocator&
/// RTRN: bool
///
/// INFO: This is the equivalency operator for the Allocator template class.
///
/// NOTE: This operator always returns true, because only an Allocator templated to the same typename can be passed
/// to this operator.  For example, if one Allocator is templated to integers and another to characters, comparing
/// the two using this operator would result in a compile-time error.  Therefore, if the Allocator being compared
/// is templated to the same typename, then both Allocators are perfectly equal because this class contains no
/// member variables.
bool operator == (const Allocator& that) const noexcept
{
    return true;
}

/// AUTH: MSP
/// VISI: public
/// PRAM: that: const Allocator&
/// RTRN: bool
///
/// INFO: This is the non-equivalency operator for the Allocator template class.
///
/// NOTE: This operator always returns false, because only an Allocator templated to the same typename can be passed
/// to this operator.  For example, if one Allocator is templated to integers and another to characters, comparing
/// the two using this operator would result in a compile-time error.  Therefore, if the Allocator being compared
/// is templated to the same typename, then both Allocators are perfectly equal because this class contains no
/// member variables.
bool operator != (const Allocator& that) const noexcept
{
    return false;
}

////////////////////////////////////////////////////////////
}; // end template class Allocator

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end ALLOCATOR_hpp
