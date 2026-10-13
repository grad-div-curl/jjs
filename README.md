WIP assembler to convert between my little jjs assembly language (also called jjsasm) and jjs skill builder code

i wouldnt recommend using this BULLSHIT without first conversing with me on discord (grad_div_curl)

this entire project is under MIT license, if a copy isn't present under a file named LICENSE see it [here](https://opensource.org/license/mit) (Copyright (c) 2026 grad-div-curl); i *personally* dont gaf as long as you dont outright steal it and claim it as yours but still follow that ig

this is the first time i've ever built something as grandiose as this (the fact that i call *this* grandiose should be telling enough) so if anything seems wonky just know i've never done this :sob:


# Running jjsasm
(ONCE ITS DONE BRO NOT YET :pray:)

## Building Requirements
- CMake (3.20? Entirely arbitrary go mess with it if you want this shit uses C11)

## Running out of the box
If a `.exe` file is present (i.e. `main.exe`), I will have probably built it on x86_64 Windows 11. If you are on a different OS (non-Windows, i.e. Mac or anything Linux-derived) or architecture (i.e. ARM or anything 32-bit), you will probably have to build it from source.

If, for some reason, there is a `.out` file (i.e. `main.out`), then I probably decided to build it on my laptop which runs x86_64 Linux (arch btw). Likewise, if you don't have that architecture and OS either, you'll have to build from source.

## Building from source (CMake)
For those new to CMake and on Windows, you'll either have to get Visual Studio or replace `nmake` with something else for your Makefile generator. Visual Studio is like 10 bazillion gigabytes, so I personally use `ninja`.

### Instructions
1. Create a build directory in your project folder for the assembler if you haven't already, then navigate to it:
```
mkdir build
cd build
```
2. Run CMake on the project folder to generate your build files, then build the project:
```
cmake ..
cmake --build .
```
3. The assembler should be under `build/main.exe` or `build/main.out` or whatever. You should be good to run it on a text file.