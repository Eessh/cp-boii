@echo off

premake5 export-compile-commands

copy .\compile_commands\debug.json .\compile_commands.json

exit