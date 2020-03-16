@echo off
echo %TIME%
cl /EHsc /std:c++17 /I..\Catch2\single_include /c test.cpp
echo %TIME%
