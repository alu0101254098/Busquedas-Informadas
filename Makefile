CXX = g++
CXXFLAGS = -std=c++2a -g
LDFLAGS = -I.

all: A_Estrella

A_Estrella: src/main.cpp src/celda.cpp src/tablero.cpp
	rm -f bin/A_Estrella *.o
			$(CXX) $(CXXFLAGS) -o bin/A_Estrella src/main.cpp src/celda.cpp src/tablero.cpp $(LDFLAGS)

clean:
	rm -f A_Estrella *.o

run:
	./bin/A_Estrella