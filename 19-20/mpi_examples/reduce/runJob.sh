#!/bin/bash

if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile /etc/pdsh/machines -np 12 --map-by ppr:4:node $1 

fi
