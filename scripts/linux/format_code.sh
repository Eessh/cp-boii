#!/bin/bash

echo Formatting code ...
clang-format -i -style=file include/*.h src/*.c *.c microui/*.h microui/*.c

echo Done.
