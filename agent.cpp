#include "agent.h"

/**
  \file   agent.cpp
  \brief  All functions for the agent searching in the environment
  \date   20142202 - Adrian Alberdi
**/

/**
	Variables:

	Node* fringe;
        Node* closed;
        Vertice* goal;
        Vertice* environment;
**/

/**
  \brief Constructor that sets the environment and the goal of the agent
  \date  20142202 - Adrian Alberdi
**/

Agent::Agent(Vertice* env, Vertice* goal){
	environment=env;
	this.goal=goal;
	fringe=NULL;
}

/**
  \brief Deconstructor
**/

Agent::~Agent(){
}

/**
  \brief Function that finds the cost to of the shortest path from the current position to the goal
  \date  20142202 - Adrian Alberdi
	\param Node* first current position of the algorithm in the graph
**/

int Agent::findShortest(Node* first){
	if(first->actual == goal){
		return first->cost;
	}
	Edge* elist=first->eStart;
	while(elist != NULL){
		push(elist, first->cost);
		elist = elist->getNext();
	}
	return findBest(pop());
}

/**
 * Private functions.
**/

/**
  \brief Function that pops an element out of the stack
  \date  20142202 - Adrian Alberdi
**/

Node* Agent::pop(){
	Node ret=fringe;
	fringe=fringe->next;
	fringe->previous=NULL;
	return ret;
}

/**
  \brief Function that pushes an element to the stack
  \date  20142202 - Adrian Alberdi
	\param Edge* elist edge to be pushed to the stack
	\param int priousCost cost of the path to the current location
**/

void Agent::push(Edge* elist, int previousCost){
	Node pushed;
	pushed.actual=elist->getVertice();
	int cost=pushed.cost=previousCost+elist->getCost();
	if (fringe==NULL){
		pushed.next=NULL;
		fringe=&pushed;
	}else{
		Node* x, y;
		x=fringe;
		while (x!=NULL && cost>x->cost){
			y=x;
			x=x->next
		}
		pushed.previous=y;
		if(y==NULL){
			fringe=&pushed;
		}else{
			y->next=&pushed;
		}
		pushed.next=x;
		if(x!=NULL){
			x.previous=&pushed;
		}
	}
}
