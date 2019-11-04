#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constant.h"



using namespace llvm;


class SingleFramePointer: public ModulePass {
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
    StringMap<Instruction *> m_LocalVariables;
    StringMap<int> m_map;
    StringMap<StoreInst *> m_StoreInstList;
    StructType * m_st;
    unsigned m_i;
    
    

public:
    static char ID;
    
    SingleFramePointer(): ModulePass(ID),m_i(0){} 

    virtual bool runOnModule(Module &Mod);    
};

char SingleFramePointer::ID = 0; 
RegisterPass<SingleFramePointer>  X ("singleframepointer", "Single Frame Pointer transformation for nested function");

bool SingleFramePointer::runOnModule(Module &Mod){
    M = &Mod;
    
    bool modified = false;

    // First iteration, collect all the local variables from the nested loop

    // Loop through the function
    for (auto &F : Mod) {

        // Continue if F is declaration 
        if (F.isDeclaration() ) continue;

        if (F.hasFnAttribute("function_root")) {
            m_HoistedInst.clear();
            m_LocalVariables.clear();
            m_map.clear();
            m_StoreInstList.clear();
            
            CollectMainLocalVariables(F);
            
            for(auto &F2 : Mod){
                if (F2.isDeclaration() ) continue;
                StringRef parentName = F2.getFnAttribute("function_parent").getValueAsString();
                if(parentName.compare(F.getName()) == 0){
                    modified |= CollectLocalVariables(F2);
                }
            } 

            modified |= HoistLocalVariables(F);
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

bool SingleFramePointer::CollectMainLocalVariables(Function & F){
    bool modified = false;

    // Loop through the basic block 
    for (auto &B : F) {
        for (auto &I : B) {
            // Check if I is a local variable (by using alloca)
            AllocaInst *aI = dyn_cast<AllocaInst>(&I);
            if(aI){
                m_map[aI->getName()] = m_i++;
                continue;
            }
            // Check for store variables
#if 0
            StoreInst *sI = dyn_cast<StoreInst>(&I);
            if(sI){
                StringRef varName = sI->getOperand(1)->getName();
                if (m_StoreInstList.find(varName)
                    == m_StoreInstList.end() ) {
                    m_StoreInstList[varName] = sI; 
                }
            }
#endif

        }
    }

    return modified;
}

bool SingleFramePointer::CollectLocalVariables(Function & F){
    bool modified = false;
    
    //SmallVector<Instruction *,2> deleteInst;
    

    // Loop through the basic block
    int newVar = m_i;
    for (auto &B : F) {
        for (auto &I : B) {
            // Check if I is a local variable (by using alloca)
            AllocaInst *aI = dyn_cast<AllocaInst>(&I);
            StoreInst * sI = dyn_cast<StoreInst>(&I);
            if(aI){
                if(m_map.find(aI->getName()) != m_map.end())
                    continue;
                
                m_map[aI->getName()]=m_i++;
                Instruction * aIclone = aI->clone();
                aIclone->setName(aI->getName());
                //aIclone->dump();
                m_HoistedInst.push_back(aIclone);
                continue;
            } 
#if 1
            else if(sI) {
                // If exists in main
                StringRef varName = sI->getOperand(1)->getName();                
                
                if(m_map.find(varName) != m_map.end()) {
                    // Remove stores that should not exists
                    if (m_StoreInstList.find(varName)
                        != m_StoreInstList.end() ) {
                        StoreInst * parentSI = m_StoreInstList[varName];
                        outs()<<"------------------------\n";
                        outs()<<"Parent " << parentSI << "\n";
                        parentSI->dump();
                        outs() << "Child " << sI << "\n";
                        sI->dump();
                        continue;
                    }
                    //Instruction * sIclone =sI->clone();
                    if (m_map[varName] >= newVar) {
                        m_HoistedInst.push_back(sI);
                        //deleteInst.push_back(&I);
                    }
                    continue;
                }
            }
            //break;
#endif
        }
        // Only hoist instruction at the begining
        //break;
    }


    return modified;
}


bool SingleFramePointer::HoistLocalVariables(Function & F){
    bool modified = false;
    
    LLVMContext &ctx = F.getContext();
    IRBuilder<> builder(ctx);
   
    std::vector<Type* > myVec;
    SmallVector<Instruction *,2> deleteInst;
    
    //outs()<<"Hoist-------------------------\n";
    for (auto &B : F){
        for (auto &I: B){
            // Insert the new instruction after alloca
            if(AllocaInst * aI = dyn_cast<AllocaInst>(&I)){
                myVec.push_back(aI->getAllocatedType() );
                m_LocalVariables[aI->getName()]=aI;
                continue;
            }
            // Insert the instruction
            builder.SetInsertPoint(&I);
            
            for(auto I : m_HoistedInst){
                if (AllocaInst* aI = dyn_cast<AllocaInst>(I)) {                
                    builder.Insert(I, I->getName());
                    //outs() << *I << " Alloca Parent " << I->getParent()->getName() << "\n";
                    myVec.push_back( aI->getAllocatedType() );               
                    m_LocalVariables[aI->getName()]=aI;
                } 
#if 1                
                else if(StoreInst* sI = dyn_cast<StoreInst>(I)){
                    //builder.Insert(sI);
                    StringRef varName = sI->getOperand(1)->getName();
                    builder.CreateStore(Constant::getNullValue(sI->getOperand(0)->getType()), m_LocalVariables[varName]);
                    //outs() << *sI << " Store Parent " << sI->getParent()->getName() << "\n";
                    //deleteInst.push_back(sI);
                    
                }
#endif
                modified = true;
            }
            
            break;
        }
        break;
    }

    for (auto I : deleteInst){
        I->eraseFromParent();
    }
    
    return modified;
}


