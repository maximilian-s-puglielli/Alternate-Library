<!--
Copyright (C) 2021 Maximilian S Puglielli (MSP)

The full copyright license belonging to this repository may be found in the
parent directory in the file named 'LICENSE'.

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <https://www.gnu.org/licenses/>.

AUTHOR:  Maximilian S Puglielli (MSP)
CREATED: 2021.01.06
-->

# template class alt::Allocator<Datatype> #

```txt
TEMPLATE CLASS alt::Allocator<Datatype>
--------------------------------------------------------------------------------
/// NO MEMBER VARIABLES
--------------------------------------------------------------------------------
/// CONSTRUCTORS
    +  Allocator ( )                       noexcept
    +  Allocator ( const Allocator& copy ) noexcept
    + ~Allocator ( )                       noexcept
--------------------------------------------------------------------------------
/// METHODS
    + u64       Datasize      ( u32 num = 1 )                  const noexcept
    + Datatype* Allocate      ( u32 size )                     const
    + Datatype* Malloc        ( u32 size )                     const noexcept
    + Datatype* RawAllocate   ( u32 size )                     const
    + Datatype* RawMalloc     ( u32 size )                     const noexcept
    + void      Deallocate    ( Datatype*& objs )              const
    + void      RawDeallocate ( Datatype*& block )             const
    + void      Construct     ( Datatype* base, u32 size = 1 ) const
    + void      Destruct      ( Datatype* base, u32 size = 1 ) const
--------------------------------------------------------------------------------
/// OPERATORS
    + Allocator& operator =  ( const Allocator& copy )       noexcept
    + bool       operator == ( const Allocator& that ) const noexcept
    + bool       operator != ( const Allocator& that ) const noexcept
--------------------------------------------------------------------------------
```

<br>

# CONSTRUCTORS #

## public Allocator ( ) noexcept ##

## public Allocator ( const Allocator& copy ) noexcept ##

## public ~Allocator ( ) noexcept ##

<br>

# METHODS #

## public u64 Datasize ( u32 num = 1 ) const noexcept ##

INFO: This method returns the number of bytes 'num' Datatypes would be.

NOTE: The parameter 'num' has a default value of 1.

<br>

## public Datatype* Allocate ( u32 size ) const ##

INFO: This method either allocates an array of objects whose length is 'size' or a single object depending on if 'size' is greater than or equal to one.

NOTE: This method can throw either an alt::InvalidParam or alt::MallocFailure exception.  Be prepared to handle those exceptions should they be thrown.
  - alt::InvalidParam will be thrown if 'size' == 0
  - alt::MallocFailure will be thrown if the new operator throws the std::bad_alloc exception.

NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method alt::Allocator::RawAllocate() which doesn't call a constructor when allocating memory; alt::Allocator::RawAllocate() allocates raw memory instead.

NOTE: This method is guaranteed to either succeed and return a non-null pointer or fail and throw an exception.  It will never return a nullptr.

<br>

## Datatype* Malloc ( u32 size ) const noexcept ##

INFO: This method either allocates an array of objects whose length is 'size' or a single object depending on if 'size' is greater than or equal to one.

NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be prepared to handle a nullptr should one be returned.

NOTE: This method calls the default constructor of each Datatype object it allocates, as opposed to the method alt::Allocator::RawMalloc() which doesn't call a constructor when allocating memory; alt::Allocator::RawAllocate() allocates raw memory instead.

<br>

## Datatype* RawAllocate ( u32 size ) const ##

INFO: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of bytes.

NOTE: This method can throw either an alt::InvalidParam or alt::MallocFailure exception.  Be prepared to handle those exceptions should they be thrown.
  - alt::InvalidParam will be thrown if 'size' == 0
  - alt::MallocFailure will be thrown if the new operator throws the std::bad_alloc exception.

NOTE: This method doesn't call a constructor when allocating memory, it allocates raw memory instead, as opposed to the method alt::Allocator::Allocate() which calls the default constructor of the Datatype objects it allocates.

NOTE: This method is guaranteed to either succeed and return a non-null pointer or fail and throw an exception.  It will never return a nullptr.

<br>

## Datatype* RawMalloc ( u32 size ) const noexcept ##

INFO: This method allocates a block of raw memory whose length is (sizeof(Datatype) * 'size') number of bytes.

NOTE: This method does not throw any exceptions.  Instead, if unsuccessful this method returns nullptr.  Be prepared to handle a nullptr should one be returned.

NOTE: This method doesn't call a constructor when allocating memory, it allocates raw memory instead, as opposed to the method alt::Allocator::Malloc() which calls the default constructor of the Datatype objects it allocates.

<br>

## void Deallocate ( Datatype*& objs ) const ##

INFO: This method deallocates the array of objects pointed to by the parameter 'objs'.

NOTE: The parameter 'objs' is passed by reference so that it can be set to nullptr after deallocation.

NOTE: This method calls the destructor on all the objects it deallocates, as opposed to alt::Allocator::RawDeallocate() which does not call the destructor on any object it deallocates.

WARN: It is imperative to use this method to deallocate memory allocated using either the alt::Allocator::Allocate() or alt::Allocator::Malloc() method.  DO NOT call this method on memory allocated using alt::Allocator::RawAllocate() or alt::Allocator::RawMalloc().

<br>

## void RawDeallocate ( Datatype*& block ) const ##

INFO: This method deallocates the block of memory pointed to by the parameter 'block'.

NOTE: The parameter 'block' is passed by reference so that it can be set to nullptr after deallocation.

NOTE: This method does not call the destructor on any object it deallocates, as opposed to alt::Allocator::Deallocate() which calls the destructor on all the objects it deallocates.

WARN: It is imperative to use this method to deallocate memory allocated using either the alt::Allocator::RawAllocate() or alt::Allocator::RawMalloc() method.  DO NOT call this method on memory allocated using alt::Allocator::Allocate() or alt::Allocator::Malloc().

<br>

## void Construct ( Datatype* base, u32 size = 1 ) const ##

INFO: The method calls the default constructor on all the Datatype objects up to 'size' starting at the memory address 'base'.

NOTE: If 'base' == nullptr, this method will do nothing.

<br>

## void Destruct ( Datatype* base, u32 size = 1 ) const ##

INFO: This method calls the destructor on all the Datatype objects up to 'size' starting at the memory address 'base'.

NOTE: If 'base' == nullptr, this method will do nothing.

<br>

# OPERATORS #

## Allocator& operator = ( const Allocator& copy ) noexcept ##

INFO: This is the copy & move assignment operator for the Allocator template class.

<br>

## bool operator == ( const Allocator& that ) const noexcept ##

INFO: This is the equivalency operator for the Allocator template class.

NOTE: This operator always returns true, because only an Allocator templated to the same typename can be passed to this operator.  For example, if one Allocator is templated to integers and another to characters, comparing the two using this operator would result in a compile-time error.  Therefore, if the Allocator being compared is templated to the same typename, then both Allocators are perfectly equal because this class contains no member variables.

<br>

## bool operator != ( const Allocator& that ) const noexcept ##

INFO: This is the non-equivalency operator for the Allocator template class.

NOTE: This operator always returns false, because only an Allocator templated to the same typename can be passed to this operator.  For example, if one Allocator is templated to integers and another to characters, comparing the two using this operator would result in a compile-time error.  Therefore, if the Allocator being compared is templated to the same typename, then both Allocators are perfectly equal because this class contains no member variables.
