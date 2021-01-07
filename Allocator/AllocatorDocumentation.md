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

# THIS FILE NEEDS WORK - IT IS VERY MUCH OUT OF DATE

# TEMPLATE CLASS alt::Allocator<Datatype>

## ERRNO LIST

### Errno #0: no error

### Errno #1: [fatal] new returned nullptr

The new (std::nothrow) [] operator was called and returned nullptr.  This is a fatal error.

### Errno #2: invalid method parameters

A method was called and passed parameters which were invalid or unacceptable.

## ACCESSORS

### inline unsigned int errno(void);

Returns the current errno of this Allocator.

## METHODS

### Datatype* allocate(unsigned int size);

Uses the new (std::nothrow) [] operator to allocate an array of bytes whose length is sizeof(Datatype) * 'size'.  Therefore, this method returns a pointer to a block of raw memory on which a constructor has yet to be called.

### bool allocate(Datatype*& rtn, unsigned int size) noexcept;

Uses the new operator to allocate an array of bytes whose length is sizeof(Datatype) * 'size'.  Returns true if successful and false otherwise.  Saves the address of the allocated block of raw memory into 'rtn'.

### void deallocate(Datatype*& block);

Uses the delete [] operator to deallocate the array of bytes pointed to by 'block'.  Use this method to deallocate a block of memory allocated using allocate().  The pointer 'block' is passed by reference so that this method can set its value to nullptr after deallocation.

### void construct(Datatype* block, unsigned int size = 1);

Calls the default constructor on all the DataTypes starting at and including the one pointed to by 'block'.  This method can be used to call the default constructor on a single Datatype or an array of DataTypes of length 'size'.  Note that allocating memory using the allocate() method and then constructing that raw memory using this construct() method, requires that memory to be destructed using the destruct() method before it is deallocated using the deallocate() method.

### void destruct(Datatype* block, unsigned int size = 1);

Calls the destructor on all the DataTypes starting at and including the one pointed to by 'block'.  This method can be used to call the destructor on a single Datatype or an array of DataTypes of length 'size'.
