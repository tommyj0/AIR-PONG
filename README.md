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

populate submodule ext/CSFML, then build shared objects as usual:

```bash
cd ext/CSFML
cmake -B build -S .
cmake --build build
```

Main project is just a makefile:

```bash
make run
```


