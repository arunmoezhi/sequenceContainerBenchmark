#!/bin/bash
date=`date +"%Y-%m-%d--%H-%M"`
fileType=".csv"
NUM_OF_TRIALS=100;
echo "ContainerType;OpType;#OfElements;ObjectSize;time;" >> out-$date$fileType
for CONTAINER_TYPE in "l" "v" "d"
do
	for OPERATION in "a" "i" "s" "c"
	do
    for NUM_OF_ELEMENTS in 16 64 256 1024 4096
		do
			./sequenceContainerBenchmark.o $NUM_OF_ELEMENTS $CONTAINER_TYPE $OPERATION $NUM_OF_TRIALS >> out-$date$fileType
		done
	done
done
