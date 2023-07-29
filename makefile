OBJS = main.cpp dbPedestrian.cpp dbLink.cpp dbNode.cpp node.cpp link.cpp pedestrian.cpp transLinks.cpp transLink.cpp
SOURCES = $(wildcard src/*.cpp)
all:
	g++ $(SOURCES) 
