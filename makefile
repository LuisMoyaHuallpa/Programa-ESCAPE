SOURCES = $(wildcard src/*.cpp)
BIN_DIR = bin

all: $(BIN_DIR)/sarsa

$(BIN_DIR)/sarsa: $(SOURCES) | $(BIN_DIR)
	g++ $^ -o $@

node:
	g++ src/main.cpp src/nodes.cpp src/node.cpp src/link.cpp src/links.cpp src/stateMatrixs.cpp src/stateMatrix.cpp src/stateActionQ.cpp src/action.cpp src/state.cpp src/subLink.cpp src/vector2D.cpp src/nodeEvacution.cpp src/tiempo.cpp -o bin/sarsa
debug:
	g++ -g $(SOURCES) -o bin/sarsa

profile:
	g++ -pg -g $(SOURCES) -o bin/sarsa


# Regla para crear la carpeta bin si no existe
$(BIN_DIR):
	mkdir -p $@
