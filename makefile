SOURCES = $(wildcard src/*.cpp)
BIN_DIR = bin

all: $(BIN_DIR)/sarsa

$(BIN_DIR)/sarsa: $(SOURCES) | $(BIN_DIR)
	g++ $^ -fopenmp -o $@

debug:

	g++ -g $(SOURCES) -o bin/sarsa

# Regla para crear la carpeta bin si no existe
$(BIN_DIR):
	mkdir -p $@
