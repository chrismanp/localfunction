FRAME_OPTION_OMIT_FP =-fomit-frame-pointer -mno-omit-leaf-frame-pointer
#INIT_VAR=-ftrivial-auto-var-init="zero"
#FRAME_OPTION_NOOMIT_FP = -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer

all: simple_nestedfunction-1 simple_nestedfunction2-1 simple_fo-1 b0ll b0bp b0sl b1sl b1bp b2sl
m2r : bpfa nldfa ldfa

# clang -S -fomit-frame-pointer -momit-leaf-frame-pointer  -o simple_fo.s -std=gnu99 -ggdb simple_fo.c

#simple_nestedfunction-1.ll : simple_nestedfunction.ll ../lib/SingleLink.so
#	opt -load ../lib/SingleLink.so -singlelink -strip-debug $< -S -o $@

testlambdacpp.ll : testlambda.cpp
	clang -S -emit-llvm -std=c++11 -o $@ $<

testlambdacpp.s : testlambdacpp.ll
	llc -o $@ $<

testlambdacpp : testlambdacpp.s
	clang -O0 -o $@ $<

b0ll.ll : b0ll.c
	clang -S -emit-llvm -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b0ll.s : b0ll.ll
	llc -o $@ $<

b0ll.bc : b0ll.ll
	llvm-as -o $@ $<

b0ll : b0ll.s
	clang -O0 -o $@ $<

b0sl.ll : b0sl.c
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b0sl.s : b0sl.ll
	llc -O0 -o $@ $<

b0sl.bc : b0sl.ll
	llvm-as -o $@ $<

b0sl : b0sl.s
	clang -O0 -o $@ $<


b1sl.ll : b1sl.c
	clang -S -emit-llvm -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b1sl.s : b1sl.ll
	llc -o $@ $<

b1sl.bc : b1sl.ll
	llvm-as -o $@ $<

b1sl : b1sl.s
	clang -O0 -o $@ $<


b2sl.ll : b2sl.c
	clang -S -emit-llvm -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b2sl.s : b2sl.ll
	llc -o $@ $<

b2sl.bc : b2sl.ll
	llvm-as -o $@ $<

b2sl : b2sl.s
	clang -O0 -o $@ $<



simple_nestedfunction.ll : simple_nestedfunction.c 
	clang -S -emit-llvm -fno-omit-frame-pointer -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

simple_nestedfunction2.ll : simple_nestedfunction2.c 
	clang -S -emit-llvm   -fmove-parentlocal -fuse-bp  -mllvm  -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

#simple_fo.ll : simple_fo.c 
#	clang -S -emit-llvm  ${FRAME_OPTION} -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

simple_fo.ll : simple_fo.c 
	clang -S -emit-llvm ${INIT_VAR}  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b0bp.ll : b0bp.c 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b1bp.ll : b1bp.c 
	clang -S -emit-llvm ${INIT_VAR}  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

b2bp.ll : b2bp.c 
	clang -O0 -S -emit-llvm ${INIT_VAR}  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

testlambdac.ll : testlambda.c 
	clang -S -emit-llvm ${INIT_VAR}  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

../lib/SingleFramePointer.so : ../lib/SingleFramePointer.cpp
	cd ../lib && make && cd ../testcode


../lib/TransformHOF.so : ../lib/TransformHOF.cpp
	cd ../lib && make && cd ../testcode

simple_nestedfunction-1.ll : simple_nestedfunction.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer -strip-debug $< -S -o $@

simple_nestedfunction2-1.ll : simple_nestedfunction2.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer -strip-debug $< -S -o $@

simple_fo-1.ll : simple_fo.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

b0bp-1.ll : b0bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

b1bp-1.ll : b1bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

b2bp-0.ll : b2bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

b2bp-1.ll : b2bp-0.ll ../lib/TransformHOF.so
	opt -load ../lib/TransformHOF.so -transformhof $< -S -o $@

testlambdac-1.ll : testlambdac.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

#simple_nestedfunction-1.s : simple_nestedfunction-1.ll 
#	llc -O0  -enable-single-link -o $@ $<

simple_fo-1.s : simple_fo-1.ll
	llc -o $@ $<

testlambdac-1.s : testlambdac-1.ll
	llc -o $@ $<


b0bp-1.s : b0bp-1.ll
	llc -O0 -o $@ $<

b1bp-1.s : b1bp-1.ll
	llc -o $@ $<

b2bp-1.s : b2bp-1.ll
	llc -O0 -o $@ $<

simple_nestedfunction-1.s : simple_nestedfunction-1.ll 
	llc -o $@ $<

simple_nestedfunction2-1.s : simple_nestedfunction2-1.ll 
	llc -enable-single-link -o $@ $<

b0bp : b0bp-1.s
	clang -O0 -o $@ $<

b1bp : b1bp-1.s
	clang -O0 -o $@ $<

b2bp : b2bp-1.s
	clang -O0 -o $@ $<

testlambdac : testlambdac-1.s
	clang -O0 -o $@ $<


simple_fo-1 : simple_fo-1.s
	clang -O0 -o $@ $<

simple_nestedfunction-1 : simple_nestedfunction-1.s 
	clang -O0 -o $@ $<

simple_nestedfunction2-1 : simple_nestedfunction2-1.s 
	clang -O0 -o $@ $<


bpfa.ll : bpfa.c
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -fuse-bp -o $@ -std=gnu99 $<

bpfa-m2r.ll : bpfa.ll
	opt -O0 -S $< -o $@

bpfa.s : bpfa-m2r.ll 
	llc -O0 -o $@ $<

bpfa : bpfa.s
	clang -O0 -o $@ $<

ldfa.ll : ldfa.cpp
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

ldfa-m2r.ll : ldfa.ll
	opt -O0 -S $< -o $@

ldfa.s : ldfa-m2r.ll 
	llc -O0 -o $@ $<

ldfa : ldfa.s
	clang -O0 -o $@ $<

b0ld.ll : b0ld.cpp
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

b0ld.s : b0ld.ll 
	llc -O0 -o $@ $<

b0ld : b0ld.s
	clang -O0 -o $@ $<



nldfa.ll : nldfa.cpp
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

nldfa-m2r.ll : nldfa.ll
	opt -S $< -mem2reg -dce -o $@

nldfa.s : nldfa-m2r.ll 
	llc -O0 -o $@ $<

nldfa : nldfa.s
	clang -O0 -o $@ $<

bsc.ll : bs.c 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 -ggdb $<

bsc-1.ll : bsc.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

bsc.s : bsc-1.ll
	llc -O0 -o $@ $<

bsc : bsc.s
	clang -O0  -o $@ $<

cachebp0.ll : cachebp0.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp0-1.ll : cachebp0.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp0.s : cachebp0-1.ll
	llc -O0 -o $@ $<

cachebp0 : cachebp0.s
	clang -O0  -o $@ $<

cachebp0_bp.ll : cachebp0_bp.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp0_bp-1.ll : cachebp0_bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp0_bp.s : cachebp0_bp-1.ll
	llc -O0 -o $@ $<

cachebp0_bp : cachebp0_bp.s
	clang -O0  -o $@ $<


cachebp1.ll : cachebp1.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp1-1.ll : cachebp1.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp1.s : cachebp1-1.ll
	llc -O0 -o $@ $<

cachebp1 : cachebp1.s
	clang -O0  -o $@ $<

cachebp2.ll : cachebp2.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp2-1.ll : cachebp2.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp2.s : cachebp2-1.ll
	llc -O0 -o $@ $<

cachebp2 : cachebp2.s
	clang -O0  -o $@ $<


cachebp1_bp.ll : cachebp1_bp.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp1-1_bp.ll : cachebp1_bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp1_bp.s : cachebp1-1_bp.ll
	llc -O0 -o $@ $<

cachebp1_bp : cachebp1_bp.s
	clang -O0  -o $@ $<


cachebp2_bp.ll : cachebp2_bp.c avar.h 
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm  -fmove-parentlocal -fuse-bp -mllvm -enable-npm-uli-transform -fexperimental-new-pass-manager -o $@ -std=gnu99 $<

cachebp2-1_bp.ll : cachebp2_bp.ll ../lib/SingleFramePointer.so
	opt -load ../lib/SingleFramePointer.so -singleframepointer $< -S -o $@

cachebp2_bp.s : cachebp2-1_bp.ll
	llc -O0 -o $@ $<

cachebp2_bp : cachebp2_bp.s
	clang -O0  -o $@ $<

bscpp.ll : bs.cpp
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

bscpp.s : bscpp.ll 
	llc -O0 -o $@ $<

bscpp : bscpp.s
	clang  -o $@ $<

cacheld0.ll : cacheld0.cpp avar.h
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

cacheld0.s : cacheld0.ll 
	llc -O0 -o $@ $<

cacheld0 : cacheld0.s
	clang -O0 -o $@ $<

cacheld1.ll : cacheld1.cpp avar.h
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

cacheld1.s : cacheld1.ll 
	llc -O0 -o $@ $<

cacheld1 : cacheld1.s
	clang -O0 -o $@ $<

cacheld2.ll : cacheld2.cpp avar.h
	clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm -std=c++11 -o $@ $<

cacheld2.s : cacheld2.ll 
	llc -O0 -o $@ $<

cacheld2 : cacheld2.s
	clang -O0 -o $@ $<



clean:
	rm -f *.o *~ *.so *.bc *-1.ll *-1.s *.s *.ll simple_nestedfunction-1 simple_nestedfunction2-1 simple_foo-1 b0ll b0sl b0bp b1bp b1sl b2sl testlambdacpp testlambdac b0ld bscpp bsc

.PHONY: clean all
