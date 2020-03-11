#+BEGIN_SRC bash
#!/bin/bash
if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile /etc/pdsh/machines -np 44 --map-by ppr:1:node $1

fi
#+END_SRC
