The code provides an experimental implementation of the two classes:
   1. counting_semaphore
   2. latch

We can use CMake to make a build:
   on Windows: I run:
      1) mkdir winbuild
      2) cd winbuild
      3) cmake -G "Visual Studio 16 2019" -A X64 ..
      4) cmake --build . --config Release
   on Ubuntu: I run:
      1) mkdir build
      2) cd build
      3) cmake ..
      4) make
