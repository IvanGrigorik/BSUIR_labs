#!/bin/bash

h_str='How to use:
		./run.sh X, where X - threads number'
mpic++ -std=c++20 Matrix.cpp Matrix.hpp matrix_test.cpp  -o out.exe
[[ -z ${1} ]] && echo ${h_str} || mpirun -n ${1} ./out.exe
