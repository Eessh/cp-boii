@echo off

echo Formatting ...

clang-format -i -style=file include\*.hpp src\*.cpp

echo Done.

exit