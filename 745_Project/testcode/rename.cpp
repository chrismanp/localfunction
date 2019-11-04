

class myClass{
public: 
    int m_a;

    myClass():m_a(2){
        m_b=20;
    }

    int mySum(int c){
        int ret = 0;
        ret = m_a + c;
        return ret;
    }

    static int m_b;

    static int myMul(int d){
        int ret = 0;
        ret = m_b * d;
        return ret;
    }
};

//typedef  int (myClass::*MethodPointer)(int d); 

//void wrapper_func(MethodPointer mp){
//    mp(20);
//}

int main(int argc, char ** argv) {
    myClass myC;
    
    //myC.mySum(10);
    
    //MethodPointer  methodpointer = myClass::myM;

    //methodpointer(20);
    

    //wrapper_func(methodpointer);

    return 0;
}


