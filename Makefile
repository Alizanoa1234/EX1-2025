CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
INCLUDES = -Iinclude
SRC = src/Graph.cpp src/Algorithms.cpp
TEST = test/test.cpp
MAIN = main.cpp
OBJS = $(SRC:.cpp=.o)
EXEC = Main
TEST_EXEC = TestRun

all: Main

Main: $(SRC) $(MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXEC) $(SRC) $(MAIN)

test: $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TEST_EXEC) $(SRC) $(TEST)

valgrind: Main
	valgrind --leak-check=full ./Main

clean:
	rm -f $(EXEC) $(TEST_EXEC)
