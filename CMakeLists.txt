### Copyright (C) 2021 Maximilian S Puglielli (MSP)
### 
### The full copyright license belonging to this repository may be found in the
### parent directory in the file named 'LICENSE'.
###
### This program is free software: you can redistribute it and/or modify it
### under the terms of the GNU General Public License as published by the Free
### Software Foundation, either version 3 of the License, or (at your option)
### any later version.
###
### This program is distributed in the hope that it will be useful, but WITHOUT
### ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
### FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
### more details.
###
### You should have received a copy of the GNU General Public License along with
### this program.  If not, see <https://www.gnu.org/licenses/>.
###
### AUTHOR:  Maximilian S Puglielli (MSP)
### CREATED: 2021.01.06

cmake_minimum_required( VERSION 3.19.2 )

project( AlternateLibrary VERSION 1.0.0 )

include_directories( Keywords )
include_directories( Types )

include_directories( Exceptions )

include_directories( Allocator )

include_directories( Vector )

include_directories( UniquePointer )
include_directories( SharedPointer )
include_directories( UniqueArray )
include_directories( SharedArray )

add_subdirectory( u128 )

add_subdirectory( Main )
