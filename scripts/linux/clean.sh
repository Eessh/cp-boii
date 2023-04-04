#!/bin/bash

echo Cleaning executables ...
rm ./bin/Debug/** > /dev/null 2>&1
rm ./bin/Release/** > /dev/null 2>&1

echo Cleaning object files ...
rm ./obj/Debug/** > /dev/null 2>&1
rm ./obj/Release/** > /dev/null 2>&1

echo Cleaning misc files ...
rm *.make > /dev/null 2>&1
rm Makefile > /dev/null 2>&1

echo Done.
