1. Modify prolog of parent's and child's by adding a getBP in parent and setBP in child. Use runOnMachineFunction? 
2. Find a better way to get offset of parent's variable in X86RegisterInfo.cpp when access by child instead of having to initialize child's local variable in parent. 
   Example : getOffset(parentslocalvariable) = ... 
3. Clean stack in the child since child's stack should be parent's stack hence no need to create a stack using alloca (should also be done in step 1)
4. Find a way to create a pointer to method (similar to C++ class's method) instead of pointer to function.  (Pointer to method have parent's RBP)
5. Evaluation? No need to use the compiler, implement it in C.
6. Refer to report