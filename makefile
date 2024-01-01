SOURCES = $(wildcard src/*.cpp)
all:
	g++ $(SOURCES) -o bin/sarsa
node:
	g++ src/main.cpp src/nodes.cpp src/node.cpp src/link.cpp src/links.cpp src/stateMatrixs.cpp src/stateMatrix.cpp src/stateActionQ.cpp src/action.cpp src/state.cpp src/subLink.cpp src/vector2D.cpp src/nodeEvacution.cpp src/tiempo.cpp -o bin/sarsa
debug:

	g++ -g $(SOURCES) -o bin/sarsa
