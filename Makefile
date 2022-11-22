ifndef VERBOSE
MAKEFLAGS += --silent
endif

SRC = .
TARGET = project
BUILD_DIR = ./build

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,$(BUILD_DIR)/%.d,$(SOURCES))

# linkage options, excluding library (-l) options
LDFLAGS = -export-dynamic

# libraries or library (-l) options for linkage
LDLIBS = `pkg-config --cflags glfw3` `pkg-config --libs glew glfw3 gl`

# include path
IFLAGS = -I./include/someMath/

# if compilation using g++ fails
#CXX = clang++

# more warnings and explicit use of c++11 standard
#WARNING := -Wall -Wextra -std=c++11

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(DEPENDS) $(TARGET) 

# execute target after compilation
exec: $(TARGET)
	./$(TARGET)

# execute target after compilation and clear terminal after programm is closed
exec_clear: $(TARGET)
	./$(TARGET)
	clear

# Linking the executable from the object files
$(TARGET): $(OBJECTS)
	$(LINK.cpp) $(WARNING) $^ $(LDLIBS) -o $@

# building object files
$(BUILD_DIR)/%.o: %.cpp Makefile
	mkdir -p ${dir $@}
	$(CXX) $(CXXFLAGS) $(WARNING) $(IFLAGS) -MMD -MP -c $< -o $@

# include dependencys to "convert" changes in header files into changes in the makefile
-include $(DEPENDS)