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

# TEMPLATE CLASS alt::Vector<Datatype, Allocator = alt::Allocator<Datatype>>

## ERRNO LIST

### Errno #0: no error

### Errno #1: [fatal] allocate returned nullptr

At some point, the allocate() method from the Allocator aggregate class returned a nullptr.  This is a fatal error.

### Errno #2: TODO: come up with more error numbers

## TEMPLATE PARAMETERS

### Datatype: the datatype this Vector will handle

Datatype is the datatype this Vector will be compiled to contain.  This could be a primitive datatype such as int or float, or it could be a user defined struct or class.  Note that if a user defined struct or class is used, the following operator must be overloaded:
- TODO: figure out the requirements for a user defined template parameter class

### Allocator: the aggregate class this Vector will use to allocate memory

Allocator will default to the template class alt::Allocator.  If a user defined allocator class is preferred, one can easily be defined and used instead of alt::Allocator.  However the custom allocator class must meet the following requirements:
- TODO: figure out the requirments for a user defined Allocator class

## CONSTRUCTOR PARAMETERS

### allocator: Allocator class for Datatype

Allocator will be the instantiation of the Allocator class template parameter that this Vector will use to allocate memory.  This parameter must be the same type as the template parameter.  Use this constructor parameter if you want to have a single allocator instantiation for multiple Vector instantiations.

### count: unsigned int

Count will be the initial number of elements in the array when this Vector is constructed.  Use this constructor parameter if you are also passing an already constructed array into the constructor alongside this parameter.  It is totally valid to create an array on the stack, pass it into this Vector's constructor, and then add/remove some elements.  This would be a good idea if you want the functionality of the push/insert/enqueue methods while avoiding heap allocation.  However, it is crucial to note that if you do this, you must absolutely set the growth parameter to 0.

### length: unsigned int

Length will be the initial size of the array when this Vector is constructed.  Use this constructor parameter if you want to create a vector with an initial array size which is larger than the default value of 1.

### growth: unsigned short int

Growth will be the percent growth factor used during amortized growth events.  Growth's default value is 100 (a 100% growth rate).  In this case, whenever an amortized growth event is triggered, the length of this Vectors array will increase by 100%, thereby doubling in size.  Use this constructor parameter if you want to control the amortized growth rate of this Vector.  Note that it is perfectly valid to set this value to 0 (a 0% growth rate) if you don't want this Vector's array to have a static memory size.  Also note that if growth is set to 0, adding an element when this Vector is full will result in this Vector's errno being set.

### array: Datatype*

Array will be the array this Vector uses to store its data.  Use this constructor parameter if you want to construct a Vector with an already populated array.  If the array you pass exists on the stack, you must absolutely set growth equal to 0.  Otherwise, the delete [] operator will be called on that memory.

## CONSTRUCTORS & DESTRUCTORS

### Vector(); // default constructor

Constructs a Vector with an instantiated aggregate Allocator, no elements, an array of size 1, and a percent growth factor of 100%.

### ~Vector(); // destructor

Deallocates the array of this Vector and sets its pointer to nullptr.

## ASSIGNMENT

### Vector(const Vector& that); // copy constructor

Constructs a Vector which is a deep copy of 'that'.  The only two attributes of this Vector which will not be identical to 'that' Vector will be the memory address of this Vector and this Vector's array member.

### Vector& operator = (const Vector& that);

If this is not equal to 'that', calls the destructor, sets all member fields of this equal to the corresponding member fields of that, allocates a new array, and copies the contents of 'that' array into this array.  This operator redefines this Vector to be a deep copy of 'that'.

## CAPACITY & SIZE ACCESSORS

### inline unsigned int size(void);

Returns the number of elements currently in this Vector.

### inline unsigned int capacity(void);

Returns the current length of this Vector's array.  Returns the number of elements that can be added to this Vector before an amortized growth event occurs.

### inline bool empty(void);

Returns a bool signifying if there are any elements currently in this Vector.  Returns whether this Vector is empty or not.

### inline bool full(void);

Returns a bool signifying if this Vector's size is equal to its capacity.  Returns whether this Vector is full or not.  If this Vector is full, adding another element will trigger an amortized growth event.

## CAPACITY & SIZE MODIFIERS

### inline void grow(void);

Triggers an amortized growth event, increasing the capacity of this Vector based on its percent growth factor.

### inline void grow(unsigned int newCapacity);

Triggers an amortized growth event, increasing the capacity of this Vector up to 'newCapacity'.

### inline void shrink(void);

Decreases the capacity of this Vector down to the number of elements currently in this Vector.  Decreases this Vector's capacity down to this Vector's size.

### inline void shrink(unsigned int newCapacity);

Decreases the capacity of this Vector down to 'newCapacity'.

### inline void truncate(unsigned int newCapacity);

Decreases the capacity of this Vector down to 'newCapacity'.  Extra truncated elements will be destructed and deallocated.

### void resize(unsigned int newCapacity);

Resizes the capacity of this Vector to 'newCapacity'.  If 'newCapacity' is less than this Vector's current number elements, extra truncated elements will be destructed and deallocated.

## MEMORY ACCESSORS & MODIFIERS

### inline bool at(unsigned int index, Datatype& rtn);

Copies the element at 'index' into 'rtn'.  Returns true if successful and false if unsuccessful.  This method retrieves the element at 'index' with bounds checking.  If 'index' is out of bounds, this method does not copy anything into 'rtn' and returns false.

### inline Datatype& operator [] (unsigned int index);

Returns the element at 'index' without bounds checking.  Note that this is the cowboy way of doing things.  If you pass an index into this operator which is out of bounds of this Vectors memory, you just shot yourself in the foot.

## SEARCH METHODS

### bool contains(const Datatype& x);

Returns true if this Vector contains 'x' and false otherwise.

### bool indexOf(const Datatype& x, unsigned int& index);

Copies the lowest index of any instances of 'x' into 'index' and returns true if there exists at least one instance of 'x' in this Vector.  Otherwise, this method does not copy anything into 'index' and returns false.

### bool lastIndexOf(const Datatype& x, unsigned int& index);

Copies the highest index of any instances of 'x' into 'index' and returns true if there exists at least one instance of 'x' in this Vector.  Otherwise, this method does not copy anything into 'index' and returns false.

## CONTAINER METHODS

### void push(const Datatype& x);

Inserts 'x' at the front of this Vector.

### bool pop(Datatype& rtn);

Copies the first element of this Vector into 'rtn' and returns true if this Vector is populated with at least one element.  Otherwise, this method does not copy anything into 'rtn' and returns false.  Returns true if successful and false if unsuccessful.

### void insert(unsigned int index, const Datatype& x);

Inserts 'x' at 'index' in this Vector.

### bool get(unsigned int index, Datatype& rtn);

Copies the element in this Vector at 'index' into 'rtn' and returns true if 'index' is within the bounds of this Vector's array.  Otherwise, this method does not copy anything into 'rtn' and returns false.  Returns true if successful and false if unsuccessful.

### void enqueue(const Datatype& x);

Inserts 'x' at the end of this Vector.

### bool dequeue(Datatype& rtn);

Copies the last element of this Vector into 'rtn' and returns true if this Vector is populated with at least one element.  Otherwise, this method does not copy anything into 'rtn' and returns false.

### void remove(unsigned int index);

Calls the destructor on the element in this Vector at 'index' and decrements the number of elements currently in this Vector.

### void erase(void);

Calls the destructor on all the elements in this Vector and sets the number of elements currently in this Vector to zero.

## VECTOR OPERATION METHODS

### void append(const Vector& that);

Appends the contents of that Vector to this Vector.

### inline void operator += (const Vector& that);

Calls the append() method.

### bool equals(const Vector& that);

Returns true if this Vector and that Vector are equivalent lists, otherwise returns false.  If both Vectors have an equivalent number of elements currently in their arrays and all those elements are equivalent and in the same order, then this method returns true.

### bool operator == (const Vector& that);

Returns true if this Vector and that Vector are identical / deep copies of each other.  The only two attributes which do not necessarily need to be identical in order for this operator to return true are the addresses of the Vectors themselves and the addresses of the arrays they encapsulate.  Every other attribute / member must be equivalent.

### bool inline operator != (const Vector& that);

Calls the == operator and returns the opposite boolean value.
