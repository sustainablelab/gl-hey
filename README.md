Make a window with GLFW and draw something in it with OpenGL.

Doing this on Windows.

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

