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
		Node* closed;
		Vertice* goal;
		Vertice* environment;
		Node* pop();
		void push(Edge* elist, int previousCost);
	public:
		Agent();
		Agent(Vertice* environment, Vertice* last);
		~Agent();
		int findShortest(Vertice* first);
}

#endif
