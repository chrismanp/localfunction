#!/bin/sh

clang -S -emit-llvm -fomit-frame-pointer -mno-omit-leaf-frame-pointer -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $1.ll -std=gnu99 -ggdb $1.c

#llc $1.ll -o $1.s


