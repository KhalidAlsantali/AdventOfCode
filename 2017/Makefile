# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /S /Q
    LIST_CMD = @for %%i in ($(EXES)) do @echo   %%i
else
    RM = rm -f
    LIST_CMD = @for exe in $(EXES); do echo "  $$exe"; done
endif

# Find all day directories and normalize paths
DAYS := $(subst \,/,$(wildcard [Dd]ay*))

# Find all .cpp files in day directories
CPP_FILES := $(subst \,/,$(wildcard $(DAYS:=/*.cpp)))

# Generate executable targets for all .cpp files
EXES := $(CPP_FILES:.cpp=.exe)

# Default target
all: $(EXES)

# Special rule for Day09.exe
Day09/day9.exe: Day09/day9.cpp
	$(CXX) $(CXXFLAGS) -o "$@" "$<" -IC:\Boost\boost_1_87_0 -LC:\Boost\boost_1_87_0\stage\lib

# Generic rule for compiling .cpp to .exe (excluding Day09.cpp)
%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o "$@" "$<"

# Clean up executable files
clean:
	$(RM) *.exe

# List all targets
list:
	@echo Available executables:
	$(LIST_CMD)

.PHONY: all clean list