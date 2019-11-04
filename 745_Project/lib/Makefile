all: SingleLink.so SingleFramePointer.so TransformHOF.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0 -std=c++11 -DCMAKE_BUILD_TYPE=Debug -I /afs/ece.cmu.edu/usr/cpakha/Private/uli/src/compiler/llvm/include

#dataflow.o: dataflow.cpp dataflow.h
#available-support.o: available-support.cpp available-support.h
#%.so: %.o dataflow.o available-support.o
#    $(CXX) -dylib -shared $^ -o $@

%.so: %.o 
	$(CXX) -dylib -shared $^ -o $@ 


clean:
	rm -f *.o *~ *.so

.PHONY: clean all
