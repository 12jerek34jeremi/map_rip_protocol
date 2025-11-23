.RECIPEPREFIX := >
SRC_DIR := src
OBJ_DIR := build
BIN := $(SRC_DIR)/program

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I$(SRC_DIR)/include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
>$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
>$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
>@mkdir -p $@

run: $(BIN)
>cd $(SRC_DIR) && ./$(notdir $(BIN))

clean:
>rm -rf $(OBJ_DIR) $(BIN)
