Using `Catch2` turns a few seconds into a whole minute on the Chuwi minibook under Cygwin:

```
g++ -std=c++17 -Wall -I../Catch2/single_include -o test.exe *.cpp
est.exe
===============================================================================
All tests passed (3 assertions in 1 test case)


real    1m31.106s
user    1m26.824s
sys     0m2.433s
```
