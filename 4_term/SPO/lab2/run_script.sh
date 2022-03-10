#!/bin/bash

gcc -o parent_app parent/main.c parent/functions/functions.c
gcc -o child_app child/main.c

CHILD_PATH=~/BSUiR_labs/4_term/SPO/lab2/child/cmake-build-debug/child ./parent_app
