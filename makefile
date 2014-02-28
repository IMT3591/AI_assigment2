
compile:
	g++ -Wall -o run.exe vertice.cpp edge.cpp agent2.cpp main.cpp
alt:
	g++ -Wall -o run.exe vertice.cpp edge.cpp agent.cpp main.cpp
clean:
	rm -f run.exe

