@echo off
echo %TIME%
cl /EHsc /std:c++17 /I..\Catch2\single_include test.obj test_*.cpp && test.exe
echo %TIME%
