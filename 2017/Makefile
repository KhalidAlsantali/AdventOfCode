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
DAYS := $(subst \,/,$(wildcard day*))

# Find all .cpp files in day directories
CPP_FILES := $(subst \,/,$(wildcard $(DAYS:=/*.cpp)))

# Generate executable targets for all .cpp files
EXES := $(CPP_FILES:.cpp=.exe)

# Default target
all: $(EXES)

# Generic rule for compiling .cpp to .exe
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