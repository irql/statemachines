@echo off
echo %TIME%
cl /EHsc /std:c++17 /I..\Catch2\single_include test2.cpp
test2.exe
echo %TIME%
