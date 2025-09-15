PROJECT=GAME
IDIR=headers/
CXX=g++
CXXFLAGS =-I$(IDIR) -Wall -Wpedantic -Werror -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lgtest -lgtest_main -lpthread


TEST_DIR=tests
SRC_DIR=src

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES=$(wildcard $(TEST_DIR)/test*.cpp)

OBJ_FILES=$(SRC_FILES:.cpp=.o)
TEST_OBJ_FILES=$(TEST_FILES:.cpp=.o)
OBJ_FILES_WITHOUT_MAIN = $(filter-out src/main.o, $(OBJ_FILES))
TARGET = main
TEST_TARGET = run_test

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES)


$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES_WITHOUT_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ_FILES) $(OBJ_FILES_WITHOUT_MAIN) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJ_FILES) $(TEST_OBJ_FILES)

format:
	find $(SRC_DIR) $(TEST_DIR) -name '*.cpp' -o -name '*.h' | xargs clang-format -i

.PHONY: all clean test format
