CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Isrc
LDFLAGS = 
SRC_DIR = src
BUILD_DIR = build
BIN_NAME = program

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/club.cpp \
       $(SRC_DIR)/event.cpp \
       $(SRC_DIR)/table.cpp \
       $(SRC_DIR)/utils.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

$(shell mkdir -p $(BUILD_DIR))

.PHONY: all clean

all: $(BIN_NAME)

$(BIN_NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)  # Создаем подпапки внутри build (если нужно)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_NAME)

DEPFLAGS = -MMD -MP
-include $(DEPS)