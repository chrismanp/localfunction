import os;
import sys;


def gena(nIter):
    print "#define genA \\"
    
    for i in range(0,nIter):
        print "\tlong a" + str(i) + " = 0; \\";

    print ""
        

    print "#define assignA \\"
        
    for i in range(0,nIter):
        print "\ta" + str(i) + " = 1; \\";
        
    print ""


if __name__ == "__main__":
    nIter = int(sys.argv[1]);
    gena(nIter);
