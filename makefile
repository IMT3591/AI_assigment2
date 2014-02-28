
tree:
	g++ -Wall -o run.exe vertice.cpp edge.cpp agent2.cpp main.cpp
graph:
	g++ -Wall -o run.exe vertice.cpp edge.cpp agent.cpp graphSearch.cpp
clean:
	rm -f run.exe

