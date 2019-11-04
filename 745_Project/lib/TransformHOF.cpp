#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constant.h"



using namespace llvm;


class TransformHOF: public ModulePass {
private:

    // Module that we're currently optimizing
    Module * M;
    
    // Run on function call
    bool CollectEnvironmentVariables (Function &F);
    //bool ReplaceFunctionPointer(Function &F);

    std::vector<Type* > m_EnvironmentTypes;

    StructType * m_st;
    StructType * m_fpwrappert;
    unsigned m_i;
    
    

public:
    static char ID;
    
    TransformHOF(): ModulePass(ID),m_i(0){} 

    virtual bool runOnModule(Module &Mod);    
};

char TransformHOF::ID = 0; 
RegisterPass<TransformHOF>  X ("transformhof", "Support for higher order function");

bool TransformHOF::runOnModule(Module &Mod){
    M = &Mod;
    
    bool modified = false;


    // Loop through the function
    for (auto &F : Mod) {

        // Continue if F is declaration 
        if (F.isDeclaration() ) continue;

        if (F.hasFnAttribute("function_root") ) {
            m_EnvironmentTypes.clear();
            LLVMContext &ctx = F.getContext();
            CollectEnvironmentVariables (F);
            
            // Create global variable environment
            m_st= StructType::create(ctx, ArrayRef<Type*>(m_EnvironmentTypes), "EnvironmentVar");
            
            M->getOrInsertGlobal("environmentvar", m_st);
            GlobalVariable * gVar = M->getNamedGlobal("environmentvar");
            gVar->setLinkage(GlobalValue::ExternalLinkage);
            gVar->setInitializer(Constant::getNullValue(m_st));            
#if 0
            std::vector<Type* > fpWrapperType;
            fpWrapperType.push_back(F.getReturnType());
            fpWrapperType.push_back(m_st);
            
            m_fpwrappert = StructType::create(ctx, ArrayRef<Type*>(fpWrapperType), "FunctionPointerWrapper");
            M->getOrInsertGlobal("fpwrapper", m_fpwrappert);
            GlobalVariable * gFPwrapper = M->getNamedGlobal("fpwrapper");
            gFPwrapper->setLinkage(GlobalValue::ExternalLinkage);
            gFPwrapper->setInitializer(Constant::getNullValue(m_fpwrappert));            
#endif
            

            for(auto &F2 : Mod){
                if (F2.isDeclaration() ) continue;
                StringRef parentName = F2.getFnAttribute("function_parent").getValueAsString();
                if(parentName.compare(F.getName()) == 0){
                    //modified |= ReplaceFunctionPointer(F2);
                }
            } 
        } 
    }

#if 0
    outs() << "=====================================\n";
    for (auto &F : Mod){
        outs() << "------------------------\n";
        outs() << F.getName() << "\n";
        for (auto &B : F){
            for (auto &I: B){
                I.dump();   
            }
        }
    }
#endif
    

    return modified;
}

bool TransformHOF::CollectEnvironmentVariables(Function & F){
    bool modified = false;

    // Loop through the basic block 
    for (auto &B : F) {
        for (auto &I : B) {
            // Check if I is a local variable (by using alloca)
            AllocaInst *aI = dyn_cast<AllocaInst>(&I);
            if(aI){
                //m_map[aI->getName()] = m_i++;
                m_EnvironmentTypes.push_back(aI->getAllocatedType());
                continue;
            }
        }
    }

    return modified;
}



