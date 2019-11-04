#!/bin/bash

if [ ! -e lambda1_d ]; then
    mkdir -p lambda1_d
fi

if [ ! -e basepointer1_d ]; then
    mkdir -p basepointer1_d
fi

if [ ! -e basepointer1_bp_d ]; then
    mkdir -p basepointer1_bp_d
fi

if [ ! -e bp1_od ]; then
    mkdir -p bp1_od
fi

if [ ! -e bp1_bp_od ]; then
    mkdir -p bp1_bp_od
fi

if [ ! -e ld1_od ]; then
    mkdir -p ld1_od
fi 

for iter in 256 512 1024 2048 4096 8192
do

    python generate_vara.py ${iter}  > avar.h

    #touch cacheld1.cpp
    #touch cachebp1.c
    #touch cachebp1_bp.c

    make cacheld1
    make cachebp1
    make cachebp1_bp

    echo -n "" > lambda1_d/ld${iter}.res
    echo -n "" > basepointer1_d/bp${iter}.res
    echo -n "" > basepointer1_bp_d/bp${iter}.res

    echo "running cachld"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cacheld1 >> lambda1_d/ld${iter}.res
    done

    echo "running cachebp"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cachebp1 >> basepointer1_d/bp${iter}.res
    done

    echo "running cachebp_bp"
    for i in {1..4096}
    do
        #echo "${i}"
        ./cachebp1_bp >> basepointer1_bp_d/bp${iter}.res
    done

done

echo "Generate CDF lambda"
python generate_cdf.py lambda1_d ld1_od
echo "Generate CDF Base pointer"
python generate_cdf.py basepointer1_d bp1_od
echo "Generate CDF Base pointer with getBP"
python generate_cdf.py basepointer1_bp_d bp1_bp_od

echo "Done"
