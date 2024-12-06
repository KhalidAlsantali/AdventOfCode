# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Find all day directories
DAYS := $(wildcard day*)

# Generate executable targets
EXES := $(foreach day,$(DAYS),\
    $(if $(wildcard $(day)/part1.cpp),$(day)/part1.exe)\
    $(if $(wildcard $(day)/part2.cpp),$(day)/part2.exe)\
    $(if $(wildcard $(day)/main.cpp),$(day)/main.exe))

# Default target
all: $(EXES)

# Generic rule for compiling .cpp to .exe
%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $

# Clean up executable files
clean:
	del /S /Q *.exe

# List all targets
list:
	@echo Available executables:
	@for %%i in ($(EXES)) do @echo   %%i