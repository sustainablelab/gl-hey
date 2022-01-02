EXE = bob

SOURCES = main.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS += -g -Wall -Wformat

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += `pkg-config --libs-only-l glfw3 glew`
	LIBS += -lopengl32
endif

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)


.PHONY: what-uname
what-uname:
	@echo $(UNAME_S)
.PHONY: what-os
what-os:
	@echo $(OS)
.PHONY: what-compiler
what-compiler:
	@echo $(CXX)
.PHONY: what-libs
what-libs:
	@echo $(LIBS)
.PHONY: what-cflags
what-cflags:
	@echo $(CXXFLAGS)
.PHONY: print-libs
print-libs: main.cpp
	$(CXX) $(CXXFLAGS) $< -M > libs.txt
.PHONY: tags
tags: main.cpp
	ctags --c-kinds=+l --exclude=Makefile -R .
.PHONY: lib-tags
lib-tags: main.cpp
	$(CXX) $(CXXFLAGS) $< -M > headers-windows.txt
	python.exe parse-lib-tags.py
	rm -f headers-windows.txt
	ctags -f lib-tags --c-kinds=+p -L headers-posix.txt
	rm -f headers-posix.txt
.PHONY: clean
clean:
	rm -f $(EXE) $(OBJS)
	rm -f libs.txt
