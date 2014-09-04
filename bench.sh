#!/usr/bin/env bash

if [ $# -lt 2 ]; then
    echo usage: $0 [DATADIR] [LOGFILE]
    exit
fi
DATADIR=$1
LOG=$2

echo Running test suite with binary trees
echo BINARY TREE >> $LOG
for file in $( ls -a $DATADIR*.txt );
do

    echo Running on $file
    echo $file >> $LOG
    for i in `seq 1 5`;
    do
        ./set_btree -p -q $file >> $LOG
    done
    echo >> $LOG
done

echo Running test suite with hash tables
echo HASH TABLE >> $LOG
for file in $( ls -a $DATADIR*.txt );
do

    echo Running on $file
    echo $file >> $LOG
    for i in `seq 1 5`;
    do
        ./set_hash -p -q $file >> $LOG
    done
    echo >> $LOG
done

echo Running test suite with dynamic arrays
echo ARRAY >> $LOG
for file in $( ls -a $DATADIR*.txt );
do

    echo Running on $file
    echo $file >> $LOG
    for i in `seq 1 5`;
    do
        ./set_array -p -q $file >> $LOG
    done
    echo >> $LOG
done

echo Running test suite with link lists
echo LINK LIST >> $LOG
for file in $( ls -a $DATADIR*.txt );
do

    echo Running on $file
    echo $file >> $LOG
    for i in `seq 1 5`;
    do
        ./set_llist -p -q $file >> $LOG
    done
    echo >> $LOG
done

echo All over, Red Rover.