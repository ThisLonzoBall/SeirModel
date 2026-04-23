CC = g++
CFLAGS= -O2 -Wall -std=c++17

SRC = src/main.cpp src/p2_simulation.cpp src/lattice.cpp src/agent.cpp src/p1_simulation.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = seir_sim

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(EXEC) $(OBJ) 
	rm -rf results/