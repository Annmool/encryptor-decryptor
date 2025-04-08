CXX = g++
# Using -O2 for optimization, added -pthread for thread support, C++17 standard
CXXFLAGS = -std=c++17 -g -Wall -O2 -pthread -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes

# Define the final executable target name
MAIN_TARGET = file_processor

# Source files for the main application
MAIN_SRC = main.cpp \
           src/app/processes/ProcessManagement.cpp \
           src/app/fileHandling/IO.cpp \
           src/app/fileHandling/ReadEnv.cpp \
           src/app/encryptDecrypt/Cryption.cpp

# Object files derived from source files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

# Default target: build the main application
all: $(MAIN_TARGET)

# Link the main application
# Added -lstdc++fs for linking the C++ filesystem library (needed on MinGW)
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++fs

# Compile source files into object files
# Corrected rule: use $< for the prerequisite (the .cpp file)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(MAIN_OBJ) $(MAIN_TARGET)

# Phony targets (not actual files)
.PHONY: clean all
