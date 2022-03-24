#!/bin/bash

g++ -o my_app -Wall -Wextra main.cpp -Lopenssl/openssl-0.9.8k/ -lssl -lcrypto -Iopenssl/openssl-0.9.8k/include
./my_app
