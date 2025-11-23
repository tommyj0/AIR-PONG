# AIR PONG

## Overview

Entity Component System (ECS) game implementation with a simple pong game as an example.

Will add ToF input eventually.


## Requirements

- SFML 

- CC

- mesa-utils

- Linux only

## Run

populate submodule ext/CSFML:

```bash
git submodule update --init
```

Run CMake as usual:
```bash
cmake -B build -S .
cmake --build build
./build/PONG
```