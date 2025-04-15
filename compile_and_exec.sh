#!/bin/bash

compiler="icx"
# Check if the Intel compiler is available
if [ -f "/opt/intel/oneapi/setvars.sh" ]; then
    source /opt/intel/oneapi/setvars.sh
else
    # If Intel compiler is not available, use GNU compiler
    compiler="gcc"
fi
echo "$compiler"
mkdir -p obj
mkdir -p bin
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/tables.c -o obj/tables.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/original_alg.c -o obj/original_alg.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/modified_alg.c -o obj/modified_alg.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/buffer_blocks.c -o obj/buffer_blocks.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/original_multi_block_alg.c -o obj/original_multi_block_alg.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/modified_multi_block_alg.c -o obj/modified_multi_block_alg.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -Wall -I./headers -c src/main.c -o obj/main.o
eval $compiler -Werror -Wextra -ansi -pedantic -Wuninitialized -Wall -I./headers obj/* -o bin/blocks
echo "Compilation completed"
time bin/blocks
