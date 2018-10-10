The BeFrank is Belgian cryptocurrency, just like Bitcoin but more anonymous and privacy centric with an opaque and more analysis resistant blockchain. It is the democratised money, by the people and for the people of Belgium and anyone who feels part of our community.

## Building BeFrank 

### On *nix and Mac OS X

Dependencies: GCC 4.7.3 or later, CMake 3.0.0 or later, and Boost 1.58

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/

Alternatively, it may be possible to install them using a package manager:

* apt on Linux
* homebrew on Mac OS X

To build, change to a directory where this file is located and run these commands:
```
mkdir build
cd build
cmake ..
make
```

### On *nix

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows
Dependencies: MSVC 2017 or later, CMake 3.0.0 or later, and Boost 1.58. You may download them from:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

To build, change to a directory where this file is located, and run theas commands: 
```
mkdir build
cd build
cmake -G "Visual Studio 15 Win64" ..
```

And then do Build.
Good luck!
