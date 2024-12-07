# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Find all day directories
DAYS := $(wildcard day*)

# Find all .cpp files in day directories
CPP_FILES := $(wildcard $(DAYS:=/*.cpp))

# Generate executable targets for all .cpp files
EXES := $(CPP_FILES:.cpp=.exe)

# Default target
all: $(EXES)

# Generic rule for compiling .cpp to .exe
%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean up executable files
clean:
	del /S /Q *.exe

# List all targets
list:
	@echo Available executables:
	@for %%i in ($(EXES)) do @echo   %%i

.PHONY: all clean list