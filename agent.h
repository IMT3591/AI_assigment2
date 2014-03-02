#ifndef AGENT_H
#define AGENT_H

#include "stdfx.h"
#include "edge.h"
#include "vertice.h"

struct Node{						//structure used for lists
	Vertice* actual;
	Node* previous;
	Node* next;
	int cost;
};

class Agent{
	private:
		Node* fringe;				//Fringe for shortest path algorithm
		Node* open;				//Fringe for A* algorithm
		Node* closed;				//Closed list for the A*
		Vertice* goal;
		Vertice* environment;
		int totalCost;				//Total cost of the path from the begging to the goal

		int findShortest(Node* first);
		void recursive();
		Node* pop(bool mode);
		void push(Edge* elist, int previousCost, bool mode);
		Node* findLast();
		void printClosed();
		void deleteFringe();
		void deleteOpen();
		void deleteClosed();
	public:
		Agent();
		Agent(Vertice* environment);
		~Agent();
		Node* findAStar(Vertice* first, Vertice* last);
};

#endif
