SOURCES = $(wildcard src/*.cpp)
BIN_DIR = bin

all: $(BIN_DIR)/sarsa

$(BIN_DIR)/sarsa: $(SOURCES) | $(BIN_DIR)
	g++ -std=c++17 $^ -o $@

node:
	g++ -std=c++17 src/main.cpp src/nodes.cpp src/node.cpp src/link.cpp src/links.cpp src/pedestrian.cpp src/pedestrians.cpp src/tiempo.cpp src/dictionary.cpp src/io.cpp src/vector2D.cpp src/vector2DVelocidad.cpp src/Q.cpp -o bin/sarsa
debug:
	g++ -std=c++17 -g $(SOURCES) -o bin/sarsa

# Regla para crear la carpeta bin si no existe
$(BIN_DIR):
	mkdir -p $@
