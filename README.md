# JUAMP - the living simulator

Latest Gorciu's project that simulates the life in colored console window.

**Features:**
- talking with family
- market hall
- money system
- hunger system
- save system
- parks

## Building JUAMP

Use `g++`, because is cross-platform and does not suck on Windows (i'm watching errors on clang++ linker right now).

### Linux building

Just install `g++` from your distribution's package manager (if needed). Then you are good to run `python3 build.py`.

### Windows building

***First of all, do not use windows, but if you must:***

DO NOT USE `mingw-32`! IT IS AN ARCHAIC SOFTWARE AND CAUSES PROBLEMS WITH BUILDING JUAMP! Instead, use `mingw-w64` from `winlibs.com`.

Here is how to check are you using `mingw-32`. Run this command:

```g++ -dumpmachine```

If your version looks like `<random shit moment>-w64-mingw32` you are good to build JUAMP. If it prints `mingw32`, UPGRADE RIGHT NOW! Download `mingw-w64` from `winlibs.com`, and add this to your path.

Then you are good to run `python3 build.py`.