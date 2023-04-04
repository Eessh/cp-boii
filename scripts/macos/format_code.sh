#!/bin/bash

echo Formatting code ...
clang-format -i -style=file include/*.h src/*.c MarkdownViewer.c

echo Done.
