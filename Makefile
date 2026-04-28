CC = g++
CFLAGS= -O2 -Wall -std=c++17

SRC = src/main.cpp src/p2_simulation.cpp src/lattice.cpp src/agent.cpp src/p1_simulation.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = seir_sim

TEST_SRC = src/testing.cpp src/p2_simulation.cpp src/lattice.cpp src/agent.cpp src/p1_simulation.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_EXEC = run_tests

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(TEST_EXEC): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean: 
	rm -f $(EXEC) $(OBJ) $(TEST_EXEC) $(TEST_OBJ)
	rm -rf results/ visualisations/