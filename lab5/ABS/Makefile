CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files directory
SRC_DIR = abs
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=%.o)

# Executable name
TARGET = abs_program

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
