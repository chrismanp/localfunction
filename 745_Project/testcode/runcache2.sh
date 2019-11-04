#!/bin/bash

if [ ! -e lambda2_d ]; then
    mkdir -p lambda2_d
fi

if [ ! -e basepointer2_d ]; then
    mkdir -p basepointer2_d
fi

if [ ! -e basepointer2_bp_d ]; then
    mkdir -p basepointer2_bp_d
fi

if [ ! -e bp2_od ]; then
    mkdir -p bp2_od
fi

if [ ! -e bp2_bp_od ]; then
    mkdir -p bp2_bp_od
fi

if [ ! -e ld2_od ]; then
    mkdir -p ld2_od
fi 

for iter in 4 8 16 32 64 128 256 512 1024 2048 4096 8192
do

    python generate_vara.py ${iter}  > avar.h

    #touch cacheld2.cpp
    #touch cachebp2.c
    #touch cachebp2_bp.c

    make cacheld2
    make cachebp2
    make cachebp2_bp

    echo -n "" > lambda2_d/ld${iter}.res
    echo -n "" > basepointer2_d/bp${iter}.res
    echo -n "" > basepointer2_bp_d/bp${iter}.res

    echo "running cachld"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cacheld2 >> lambda2_d/ld${iter}.res
    done

    echo "running cachebp"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cachebp2 >> basepointer2_d/bp${iter}.res
    done

    echo "running cachebp_bp"
    for i in {1..4096}
    do
        #echo "${i}"
        ./cachebp2_bp >> basepointer2_bp_d/bp${iter}.res
    done

done

echo "Generate CDF lambda"
python generate_cdf.py lambda2_d ld2_od
echo "Generate CDF Base pointer"
python generate_cdf.py basepointer2_d bp2_od
echo "Generate CDF Base pointer with getBP"
python generate_cdf.py basepointer2_bp_d bp2_bp_od

echo "Done"
