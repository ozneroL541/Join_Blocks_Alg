#!/bin/bash

mkdir -p obj
mkdir -p bin
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/tables.c -o obj/tables.o
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/original_alg.c -o obj/original_alg.o
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/modified_alg.c -o obj/modified_alg.o
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/buffer_blocks.c -o obj/buffer_blocks.o
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/original_multi_block_alg.c -o obj/original_multi_block_alg.o
gcc -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/modified_multi_block_alg.c -o obj/modified_multi_block_alg.o
gcc -Wall -g -Wextra -ansi -pedantic -Wuninitialized -I./headers -c src/main.c -o obj/main.o
gcc -Wall -g -Wextra -ansi -pedantic -Wuninitialized -I./headers obj/* -o bin/blocks
echo "Compilation completed"
time bin/blocks
