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

#ifndef ALLOCATOR_hpp
#define ALLOCATOR_hpp

#include <new> // exclusively for std::bad_alloc

#include "Keywords.hpp"
#include "Types.hpp"
#include "Exceptions.hpp"

namespace alt // Allocator belongs to namespace alt
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// AUTHOR:      MSP
/// VISIBILITY:  ::alt::Allocator
///
/// DESCRIPTION: This class is an encapsulation of the new operator.  Its purpose is to control the allocation and
/// deallocation of heap memory.  This class is capable of separating the two actions of allocating and constructing
/// memory, although it is not usually recommended to do so.  This class is a singleton for the reason that it can be
/// templated and encapsulated by other container classes in the alternate template library.  This is the default
/// allocator used by all the containers in the alternate template library, therefore it is defined in namespace alt
/// (for alternate, as opposed to standard).
template <typename Datatype>
class Allocator
{
/// CONSTRUCTORS
public:
    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    ///
    /// DESCRIPTION: This is the default constructor for the Allocator template class.
    Allocator() noexcept = default; // default constructor

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   copy (const Allocator&)
    ///
    /// DESCRIPTION: This is the copy constructor for the Allocator template class.
    Allocator(const Allocator& copy) noexcept = default; // copy constructor

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   move (Allocator&&)
    ///
    /// DESCRIPTION: This is the move constructor for the Allocator template class.
    Allocator(Allocator&& move) noexcept = default; // move constructor

/// METHODS
public:
    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   num (u32 = 1)
    /// RETURN:      u64
    ///
    /// DESCRIPTION: This method returns the number of bytes num Datatypes would be.
    /// return sizeof(Datatype) * 'num';
    ///
    /// NOTE: The parameter 'num' has a default value of 1.
    u64 DataSize(u32 num = 1) const
    {
        return sizeof(Datatype) * num;
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatype objects to allocate
    /// RETURN:      Datatype* ~ the address of the array of allocated objects
    ///
    /// DESCRIPTION: This method either allocates an array of objects whose length is 'size' or a single object
    /// depending on if 'size' is greater than or equal to one.
    ///
    /// NOTE: This method can throw either an alt::InvalidParam or alt::MallocFailure exception.  Be prepared to handle
    /// those exceptions should they be thrown.
    ///   - alt::InvalidParam will be thrown if size == 0
    ///   - alt::MallocFailure will be thrown if the new operator throws the std::bad_alloc exception.
    ///
    /// NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method
    /// alt::Allocator::RawAllocate() which doesn't call a constructor when allocating memory.
    ///
    /// NOTE: This method is guaranteed to either succeed and return a non-null pointer or fail and throw an exception.
    /// It will never return a nullptr.
    Datatype* Allocate(u32 size = 1) const
    {
        if (! size)
            throw alt::InvalidParam();
        Datatype* rtn = nullptr;
        try
        {
            rtn = new Datatype[size];
        }
        catch (const std::bad_alloc& ba)
        {
            throw alt::MallocFailure();
        }
        return rtn;
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatype objects to allocate
    /// RETURN:      Datatype* ~ the address of the array of allocated objects
    ///
    /// DESCRIPTION: This method either allocates an array of objects whose length is 'size' or a single object
    /// depending on if 'size' is greater than or equal to one.
    ///
    /// NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be
    /// prepared to handle a nullptr should one be returned.
    ///
    /// NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method
    /// alt::Allocator::RawMalloc() which doesn't call a constructor when allocating memory.
    Datatype* Malloc(u32 size = 1) const noexcept
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

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatype objects to allocate
    /// RETURN:      Datatype* ~ the address of the block of raw memory this method allocated
    ///
    /// DESCRIPTION: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of
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
    Datatype* RawAllocate(u32 size = 1) const
    {
        if (! size)
            throw alt::InvalidParam();
        Datatype* rtn = nullptr;
        try
        {
            rtn = (Datatype*)(new u8[sizeof(Datatype) * size]);
        }
        catch (const std::bad_alloc& ba)
        {
            throw alt::MallocFailure();
        }
        return rtn;
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatype objects to allocate
    /// RETURN:      Datatype* ~ the address of the block of raw memory this method allocated
    ///
    /// DESCRIPTION: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of
    /// bytes.
    ///
    /// NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be
    /// prepared to handle a nullptr should one be returned.
    ///
    /// NOTE: This method doesn't call a constructor when allocating memory, as opposed to the method
    /// alt::Allocator::Malloc() which calls the default constructor of the Datatype objects it allocates.
    Datatype* RawMalloc(u32 size = 1) const noexcept
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

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   objs (Datatype*&) ~ the address of the array of objects to be deallocated
    /// RETURN:      void
    ///
    /// DESCRIPTION: This method deallocates the array of objects pointed to by the parameter 'objs'.
    ///
    /// NOTE: The parameter 'objs' is passed by reference so that it can be set to nullptr after deallocation.
    ///
    /// NOTE: This method calls the destructor on all the objects it deallocates, as opposed to
    /// alt::Allocator::RawDeallocate() which does not call the destructor on any object it deallocates.
    void Deallocate(Datatype*& objs) const
    {
        if (objs)
        {
            delete [] objs;
            objs = nullptr;
        }
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   block (Datatype*&) ~ the address of the block of memory to be deallocated
    /// RETURN:      void
    ///
    /// DESCRIPTION: This method deallocates the block of memory pointed to by the parameter 'block'.
    ///
    /// NOTE: The parameter 'block' is passed by reference so that it can be set to nullptr after deallocation.
    ///
    /// NOTE: This method does not call the destructor on any object it deallocates, as opposed to
    /// alt::Allocator::Deallocate() which calls the destructor on all the objects it deallocates.
    void RawDeallocate(Datatype*& block) const
    {
        if (block)
        {
            delete [] (u8*)(block);
            block = nullptr;
        }
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   base (Datatype*) ~ the address of the block of raw memory
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatypes to be constructed
    /// RETURN:      void
    ///
    /// DESCRIPTION: The method calls the default constructor on all the Datatype objects up to 'size' starting at the
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

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   base (Datatype*) ~ the address of the block of non-raw memory
    /// PARAMETER:   size (u32 = 1) ~ the number of Datatype objects to be constructed
    /// RETURN:      void
    ///
    /// DESCRIPTION: This method calls the destructor on all the Datatype objects up to 'size' starting at the memory
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

/// OPERATORS
public:
    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// OVERLOAD:    ::alt::Allocator::operator=()
    /// PARAMETER:   copy (const Allocator&)
    /// RETURN:      Allocator&
    ///
    /// DESCRIPTION: This is the assignment operator for the Allocator template class.
    Allocator& operator = (const Allocator& copy) noexcept = default; // assignment operator

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// OVERLOAD:    ::alt::Allocator::operator=()
    /// PARAMETER:   move (const Allocator&)
    /// RETURN:      Allocator&
    ///
    /// DESCRIPTION: This is the assignment operator for the Allocator template class.
    Allocator& operator = (Allocator&& move) noexcept = default; // assignment operator

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   that (const Allocator&)
    /// RETURN:      bool
    ///
    /// DESCRIPTION: This is the equivalency operator for the Allocator template class.
    ///
    /// NOTE: This operator always returns true, because only an Allocator templated to the same typename can be passed
    /// to this operator.  For example, if one Allocator is templated to integers and another to characters, comparing
    /// the two using this operator would result in a compile-time error.  Therefore, if the Allocator being compared
    /// is templated to the same typename, then both Allocators are perfectly equal because this class contains no
    /// member variables.
    bool operator == (const Allocator& that) const
    {
        return true;
    }

    /// AUTHOR:      MSP
    /// VISIBILITY:  public
    /// PARAMETER:   that (const Allocator&)
    /// RETURN:      bool
    ///
    /// DESCRIPTION: This is the non-equivalency operator for the Allocator template class.
    ///
    /// NOTE: This operator simply returns the opposite of the equivalency operator.
    bool operator != (const Allocator& that) const
    {
        return false;
    }

}; // end template class Allocator

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end namespace alt

#endif // end ALLOCATOR_hpp
