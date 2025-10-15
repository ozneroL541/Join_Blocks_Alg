<a href="https://github.com/ozneroL541/Join_Blocks_Alg/blob/master/LICENSE"><img src="https://img.shields.io/github/license/ozneroL541/Join_Blocks_Alg?color=2b9348" alt="License"/></a>

# Join_Blocks_Alg
Algorithms for the cartesian product between two tables.

## Index
 - [Description](#description)
 - [Download](#download)
 - [Configuration](#configuration)
 - [Compilation](#compilation)
 - [Execution](#execution)
 - [Documentation](#documentation)
 - [Author](#author)
 - [License](#license)

## Description
This program simulates different algorithms in order show how many steps they take to calculate the cartesian product between two tables.
The program is parametrical respect the tables, R and S and the size of the buffer.
The size of the buffer must be bigger then 3 and it's consider only to perform multi-block algorithms, 
for the others it's considered 3 block.

## Download
Download the source code from Github

    git clone https://github.com/ozneroL541/Join_Blocks_Alg.git

## Configuration
Change tables length modifing the macros in `include/tables.h`.
Change avaiable blocks in the buffer modifing the macro in `include/buffer_blocks`.

## Compilation
> It is suggested to use ICX Intel Compiler to compile this program, if it is not avaiable, GCC will be used.

To compile run:

    make

## Execution
To execute the program run
    bin/blocks <R table blocks> <S table blocks> <Buffer blocks>

## Documentation
To document this software use:

    doxygen docfile

## Author
- Radice Lorenzo @ozneroL541

## License
Join_Blocks_Alg is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Join_Blocks_Alg is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Join_Blocks_Alg. If not, see http://www.gnu.org/licenses/.
