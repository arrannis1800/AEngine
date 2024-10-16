# AEngine
## Overview

A small project to understand more clearly how game engines work
This is functional code for game development without a graphic editor

For now, it works on Windows (but it should also work on Linux and MacOS because of GLFW) and uses OpenGL 3 as a graphic API

## How to use

You need to have installed OpenGL SDK and recursively clone this repo

Firstly, you need to clone it as submodule of your project

```
git submodule add git@github.com:arrannis1800/AEngine.git {yourIncludeFolder}/AEngine
git submodule update --init --recursive
```

Next, you need to move outside `configure.cpp` script
build it and run with `path={yourIncludeFolder}` parameter

```
g++ configure.cpp -o configure
./configure.exe path={yourIncludeFolder}
```

After you should execute the following commands

```
mkdir build
cd build
cmake ..
cmake --build .
```
