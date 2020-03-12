#!/bin/bash
# This script can take multiple parameters
# The first is the executable (required) any others would be passed as paremeter# to that executable

if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile /etc/pdsh/machines -np 44 --map-by ppr:4:node $4 $2 $3

fi
