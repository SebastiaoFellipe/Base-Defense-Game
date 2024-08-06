FLAGS = -Wall -pedantic -O0 -g -Iinclude -I/usr/local/include

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = BaseDefenseGame

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	g++ $(FLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

re: clean all

.PHONY: all clean re