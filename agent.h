#ifndef AGENT_H
#define AGENT_H

#include "edge.h"
#include "vertice.h"

struct Node{
	Vertice* actual;
	Node* previous;
	Node* next;
	int cost;
}

class Agent{
	private:
		Node* fringe;

		Node* open;
		Node* closed;
		Vertice* goal;
		Vertice* environment;
		int totalCost;

		void recursive;
		Node* pop(bool mode);
		void push(Edge* elist, int previousCost, bool mode);
		Node* findLast();
	public:
		Agent();
		Agent(Vertice* environment);
		~Agent();
		int findShortest(Node* first);
		Node* findAStar(Vertice* first, Vertice* last);
}

#endif
