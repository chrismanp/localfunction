import os;
import sys;

# To run : 
# $python raw_to_cdf "inputfolder" "outputfolder"

def raw_to_cdf(iDir, oDir):
    """ 
    $python raw_to_cdf "inputfolder" "outputfolder"
    """
    myfiles = [f for f in os.listdir(iDir) if os.path.isfile(os.path.join(iDir, f))]

    for f in myfiles:
        iFileName = os.path.join(iDir, f);
        oFileName = os.path.join(oDir, f);

        iFile = open(iFileName, "r");
        oFile = open(oFileName, "w");

        print ("Processing %s >> %s" % (iFileName, oFileName))
        create_cdf(iFile, oFile);

        oFile.close();
        iFile.close();


def create_cdf(iFile, oFile):
    latencyList = []
    for lines in iFile.readlines():
        lines = lines.strip()
        latency = int(lines.split()[0]);
        latencyList.append(latency);

    latencyList.sort();
    targetLines = 15000 
    lenData = len(latencyList);

    res = int(lenData/targetLines) + 1; # Avoid 0
    res = 1;
    for i in range(0, lenData-1, res):
        if (i + res < lenData):
            if (latencyList[i] == latencyList[i+res]):
                continue;
        
        oFile.write(str(latencyList[i]))
        oFile.write("\t")
        oFile.write(str(int(i+1)/float(lenData)));
        oFile.write("\n");

    oFile.write(str(latencyList[lenData-1]));
    oFile.write("\t");
    oFile.write("1");
    oFile.write("\n");

if __name__ == "__main__":
    iDir = sys.argv[1];
    oDir = sys.argv[2];
    raw_to_cdf(iDir, oDir);
