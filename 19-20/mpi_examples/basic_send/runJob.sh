#!/bin/bash

if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile /etc/pdsh/machines -np 11 --map-by ppr:11:node $1 

fi
