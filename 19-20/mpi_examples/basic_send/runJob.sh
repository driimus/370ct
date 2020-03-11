#!/bin/bash

if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile /etc/pdsh/machines -np 11 $1 

fi
