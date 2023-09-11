# Modern OpenGL - Deferred Rending

![Screenshot 1](./doc/screenshot1.jpg)

Modern OpenGL deferred rendering example

This little project shall contain the tools to produce the following techniques and effects:
* deferred rendering
* deferred lighting
* shadows
* bloom

## Requirements

Development is done with
* Conan 2.x
* CMake 3.27.x
* Visual Studio 2022 Community Edition

## Building

Conan install for debug and release build types
```
conan install . --build=missing --settings=build_type=Debug && conan install . --build=missing --settings=build_type=Release
```

CMake project generation
```
cmake --preset conan-default
```

Build in release mode
```
cd build
cmake --build . --config Release
```
