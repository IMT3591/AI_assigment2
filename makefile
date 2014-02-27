
compile:
	g++ -Wall -o run.exe vertice.cpp edge.cpp agent2.cpp main.cpp
alt:
	g++ -Wall -o run.exe vertice.cpp edge.cpp main.cpp agent2.cpp

clean:
	rm -f run.exe

