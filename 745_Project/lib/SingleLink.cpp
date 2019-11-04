#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constant.h"



using namespace llvm;


class SingleLink: public ModulePass {
private:

    // Module that we're currently optimizing
    Module * M;
    
    // Run on function call
    bool CollectLocalVariables (Function &F);
    bool CollectMainLocalVariables (Function &F);
    bool HoistLocalVariables(Function &F);
    bool ReplaceLocalVariables(Function &F);
    
    // Local variables declared in nested function
    SmallVector<Instruction *,2> m_HoistedInst;
    StringMap<int> m_map;
    StructType * m_st;

    unsigned m_i;
public:
    static char ID;
    
    SingleLink(): ModulePass(ID),m_i(0){} 

    virtual bool runOnModule(Module &Mod);    
};

char SingleLink::ID = 0; 
RegisterPass<SingleLink>  X ("singlelink", "Single Link transformation for nested function");

bool SingleLink::runOnModule(Module &Mod){
    M = &Mod;
    
    bool modified = false;

    // First iteration, collect all the local variables from the nested loop

    // Loop through the function
    for (auto &F : Mod) {
        
        // Continue if F is declaration 
        if (F.isDeclaration() ) continue;
        // If function is main   HACK!
        if (F.getName().compare("main") == 0) {
            CollectMainLocalVariables(F);
            continue;
        } else {
            modified |= CollectLocalVariables(F);        
        }

    }

    // Second iteration, place those collected local variables to the main loop
    for (auto &F : Mod) {
        if (F.isDeclaration() ) continue;
        
        // Hoist instruction on main HACK!
        if (F.getName().compare("main") == 0) 
            modified |= HoistLocalVariables(F);
    
    }
    
    // Third iteration replace all local variable uses with the static link
    for (auto &F : Mod){
        if (F.isDeclaration() ) continue;
        
        modified |= ReplaceLocalVariables(F);
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

bool SingleLink::CollectMainLocalVariables(Function & F){
    bool modified = false;

    // Loop through the basic block 
    for (auto &B : F) {
        for (auto &I : B) {
            // Check if I is a local variable (by using alloca)
            AllocaInst *aI = dyn_cast<AllocaInst>(&I);
            if(aI){
                m_map[aI->getName()] = m_i++;
            }
        }
    }

    return modified;
}

bool SingleLink::CollectLocalVariables(Function & F){
    bool modified = false;

    // Loop through the basic block 
    for (auto &B : F) {
        for (auto &I : B) {
            // Check if I is a local variable (by using alloca)
            AllocaInst *aI = dyn_cast<AllocaInst>(&I);
            if(aI){
                if(m_map.find(aI->getName()) != m_map.end())
                    continue;
                
                m_map[aI->getName()]=m_i++;
                Instruction * aIclone = aI->clone();
                aIclone->setName(aI->getName());
                //aIclone->dump();
                m_HoistedInst.push_back(aIclone);
            }
        }
    }

    return modified;
}


bool SingleLink::HoistLocalVariables(Function & F){
    bool modified = false;
    
    LLVMContext &ctx = F.getContext();
    IRBuilder<> builder(ctx);
   
    std::vector<Type* > myVec;
     
    for (auto &B : F){
        for (auto &I: B){
            // Insert the new instruction after alloca
            if(AllocaInst * aI = dyn_cast<AllocaInst>(&I)){
                myVec.push_back(aI->getAllocatedType() );
                continue;
            }
            // Insert the instruction
            builder.SetInsertPoint(&I);
            
            for(auto I : m_HoistedInst){
                if (AllocaInst* aI = dyn_cast<AllocaInst>(I)) {                
                    builder.Insert(I, I->getName());
                    myVec.push_back( aI->getAllocatedType() );               
                }

                modified = true;
            }
            
            // Create global structure (or the single link)
            m_st= StructType::create(ctx, ArrayRef<Type*>(myVec), "Mystruct");
            
            M->getOrInsertGlobal("mystruct", m_st);
            GlobalVariable * gVar = M->getNamedGlobal("mystruct");
            gVar->setLinkage(GlobalValue::ExternalLinkage);
            gVar->setInitializer(Constant::getNullValue(m_st));            
            break;
            
        }
        break;
    }
    return modified;
}


bool SingleLink::ReplaceLocalVariables(Function &F){
    bool modified = false;
    if(!m_st)
        assert(false);
#if 1        
    LLVMContext &ctx = F.getContext();
    IRBuilder<> builder(ctx);
   
    GlobalVariable * gVar = M->getNamedGlobal("mystruct");
    SmallVector<Instruction *,2> deleteInst;
    
    for (auto &B : F){
        for (auto &I: B){
            if(dyn_cast<AllocaInst>(&I)){
                modified = true;
                Value *tmp =  builder.CreateStructGEP(m_st, gVar, m_map[I.getName()]);
                //itmp->dump();
                I.replaceAllUsesWith(tmp);
                if (F.getName().compare("main") == 0) continue;
                deleteInst.push_back(&I);
                continue;
            }
            break;                     
        }
    }

    for (auto I : deleteInst){
        I->eraseFromParent();
    }

#endif
    return modified;
}
