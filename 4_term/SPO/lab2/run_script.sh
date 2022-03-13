#!/bin/bash

gcc -o child_app child/main.c
gcc -o parent_app parent/main.c parent/functions/functions.c


CHILD_PATH=./child_app ./parent_app
