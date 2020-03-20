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

Abysmal performance under cygwin even when pre-compiling the Catch2 runner
```
real    0m59.469s
user    0m57.216s
sys     0m1.869s
```

But only takes a little under 8 seconds on the Chuwi minibook under VC++9.0
```
20:28:13.05
Microsoft (R) C/C++ Optimizing Compiler Version 19.24.28316 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

test2.cpp
Microsoft (R) Incremental Linker Version 14.24.28316.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:test2.exe
test2.obj
===============================================================================
All tests passed (3 assertions in 1 test case)

20:28:20.74
```

On the Chuwi under an Archlinux VM, takes 40 seconds initially
```
real    0m40.775s
user    0m35.329s
sys     0m2.938s
```

But once the test runner is built, takes 9.8s under Arch:
```
real    0m9.896s
user    0m8.237s
sys     0m1.110s
```

But only 26 seconds on the Dell XPS 15 under cygwin
```
real    0m26.322s
user    0m23.701s
sys     0m0.933s
```

A little over 8 seconds on the Dell XPS 15 under a CentOS VM running in virtualbox
```
real    0m8.665s
user    0m9.120s
sys     0m0.328s
```

Again around 8 seconds under the Dell XPS 15 running Arch linux
```
real    0m7.933s
user    0m7.548s
sys     0m0.342s
```

And under three seconds on Dell XPS 15 under VC++9.0
```
C:\Users\Bryan Concari\src\github.com\interruptrequestlevel\statemachines>make
 3:16:15.56
Microsoft (R) C/C++ Optimizing Compiler Version 19.22.27905 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

test2.cpp
Microsoft (R) Incremental Linker Version 14.22.27905.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:test2.exe
test2.obj
===============================================================================
All tests passed (3 assertions in 1 test case)

 3:16:18.31
```
