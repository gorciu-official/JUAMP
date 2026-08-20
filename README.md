# JUAMP - the living simulator

Gorciu's latest project that simulates life in colored console window.

**Features:**
- talking with family
- market hall
- money system
- hunger system
- save system
- parks

## Building JUAMP

Use `g++`, because it's cross-platform and does not suck on Windows (i'm watching clang++'s linker errors right now).

### Linux building

Just install `g++` from your distribution's package manager (if needed). Then you are good to run `make`.

### Windows building

DO NOT USE `mingw-32`! IT IS ARCHAIC SOFTWARE AND CAUSES PROBLEMS WITH BUILDING JUAMP! Instead, use `mingw-w64` from `winlibs.com`.

Here is how to check whether you are using `mingw-32`. Run this command:

```sh
g++ -dumpmachine
```

If the output looks like `<random shit>-w64-mingw32` you are good to build JUAMP. If it prints `mingw32`, UPGRADE RIGHT NOW! Download `mingw-w64` from `winlibs.com`, and add this to your system PATH.

Then you are good to run `python3 build.py`.

## Additional building tips

1. You can use `make` instead of `python3 build.py`. It runs the Python script under the hood
2. Building to MacOS/iOS/iPadOS/Android is **currently not possible** and the code is not optimized for supporting these platforms. I recommend not even trying to build for these platforms, unless you want to do a complete refactor (and/or you hate yourself).
3. Never compile with `mingw-32`, it'll cause problems with dependencies, so please - don't use it.