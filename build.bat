@echo off

echo Building %1...
mingw32-make -C %1 all
