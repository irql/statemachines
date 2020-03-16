@echo off
echo %TIME%
cl /EHsc /std:c++17 /I..\Catch2\single_include test.cpp test_*.cpp
test.exe
echo %TIME%
