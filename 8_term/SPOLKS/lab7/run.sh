#!/bin/bash

# source /etc/profile.d/modules.sh
# module load mpi/openmpi-x86_64

executable="${2}.out"

# Check if the executable file already exists and is up-to-date
if [ ! -f "$executable" ] || [ "main.cpp" -nt "$executable" ]; then
    echo "Compiling..."
    mpic++ -std=c++23 -Wall -Wpedantic main.cpp -o "$executable"
fi

echo "Running..."
mpirun -n "$1" ./"$executable"
