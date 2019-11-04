#!/bin/bash

if [ ! -e lambda0_d ]; then
    mkdir -p lambda0_d
fi

if [ ! -e basepointer0_d ]; then
    mkdir -p basepointer0_d
fi

if [ ! -e basepointer0_bp_d ]; then
    mkdir -p basepointer0_bp_d
fi

if [ ! -e bp0_od ]; then
    mkdir -p bp0_od
fi

if [ ! -e bp0_bp_od ]; then
    mkdir -p bp0_bp_od
fi

if [ ! -e ld0_od ]; then
    mkdir -p ld0_od
fi 


for iter in 256 512 1024 2048 4096 8192
do

    python generate_vara.py ${iter}  > avar.h

    #touch cacheld0.cpp
    #touch cachebp0.c
    #touch cachebp0_bp.c

    make cacheld0
    make cachebp0
    make cachebp0_bp

    echo -n "" > lambda0_d/ld${iter}.res
    echo -n "" > basepointer0_d/bp${iter}.res
    echo -n "" > basepointer0_bp_d/bp${iter}.res

    echo "running cachld"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cacheld0 >> lambda0_d/ld${iter}.res
    done

    echo "running cachebp"
    for i in {1..4096}
    do
        :
        #echo "${i}"
        ./cachebp0 >> basepointer0_d/bp${iter}.res
    done

    echo "running cachebp_bp"
    for i in {1..4096}
    do
        #echo "${i}"
        ./cachebp0_bp >> basepointer0_bp_d/bp${iter}.res
    done


done


echo "Generate CDF lambda"
python generate_cdf.py lambda0_d ld0_od

echo "Generate CDF Base pointer"
python generate_cdf.py basepointer0_d bp0_od

echo "Generate CDF with Set/Get Base pointer"
python generate_cdf.py basepointer0_bp_d bp0_bp_od

echo "Done"
