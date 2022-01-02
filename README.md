Make a window with GLFW and draw something in it with OpenGL.

Doing this on Windows.

## ToC
- setup
    - [environment](README.md#environment)
    - [dependencies](README.md#dependencies)
- do stuff
    - [make a window](README.md#make-a-window)

# Setup

## Environment

Follow my instructions to [set up
MSYS2](https://github.com/sustainablelab/msys). Install packages
in the `msys` subsystem and do yer coding and building in the
`mingw` subsystem.

Need these basic packages for doing anything:

```bash
pacman -S git make pkgconf gdb ctags python vim
```

And need these packages to build this thing I'm doing here:

```bash
pacman -S mingw-w64-x86_64-glfw
pacman -S mingw-w64-x86_64-glew
```

## Dependencies

Make a `main.cpp`.

Include these three headers:

```c
#include <cstdio>
#include <GL/glew.h> // OpenGL implementation
#include <GLFW/glfw3.h> // Give me windowing powers
```

- `cstdio` gives me `printf()` and `fflush()`
- `glew` is an *implementation* of the OpenGL spec
- `glfw3` is a windowing lib, like SDL2

Need to link against libs for GLEW, GLFW, and OpenGL.

The `Makefile` has this line to figure out the `-l` linker flags
for linking with the `glew` and `glfw3` libs:

```make
	LIBS += `pkg-config --libs-only-l glfw3 glew`
```

See those glfw3 and glew flags for yerself:

```bash
$ pkg-config --libs glfw3 glew
-LC:/msys64/mingw64/lib -lglfw3 -lglew32 
```

Or use my `make` recipe to see **all** the linker flags:

```bash
$ make what-libs
-lglfw3 -lglew32 -lopengl32
```

# Do stuff

## Make a window

Instead of me rambling here, future me should just look at the
version of `main.cpp` that does nothing but make a window.

Hey future me, take a look at `main.cpp` from the `v0.1` tag:

```bash
git show v0.1 main.cpp
```

To throw that `main.cpp v0.1` into a file to open in Vim:

- checkout the old commit
- copy the text into a new file (a file Git is not tracking)
- and go back to the latest commit (new file still be there)

Like this:

```bash-git
$git checkout v0.1
Note: switching to 'v0.1'.

You are in 'detached HEAD' state.
...
```

Don't worry about the 'detached HEAD' state.

Dump the old main.cpp into a new file:

```bash
$ cat main.cpp > main-v0.1.cpp
```

And get back to the latest commit (fixes the detached HEAD
thing):

```git-bash
$ git checkout master
Previous HEAD position was 22f8ded Make a window or go fullscreen
Switched to branch 'master'
```
