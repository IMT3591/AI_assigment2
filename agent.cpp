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

Agent::Agent(Vertice* env){
	environment=env;
	fringe=NULL;
}

/**
  \brief Deconstructor
**/

Agent::~Agent(){
}

/**
  \brief Main function of the agent. Finds the shortest path to the destination.
  \date  20142202 - Adrian Alberdi
**/

Node* Agent::findAStar(Vertice* first, Vertice* last){
	goal=last;
	totalCost = findShortest(first);
	closed->actual=first;
	closed->cost=0;
	Edge* elist=first->eStart;
	while(elist!=NULL){
		push(elist,0,true);
		elist->getNext();
	}
	recursive();
	return closed;
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
		push(elist, first->cost, false);
		elist = elist->getNext();
	}
	return findBest(pop(false));
}

/**
 * Private functions.
**/

void Agent::recursive(){
	Node* position=pop(true);
	if(position->actual==goal){
		Node* lastClosed=findLast();
		lastClosed->next=position;
		position->previous=lastClosed;
		position->next=NULL;
		cout >> "I've found the goal node";
	}else{
		int distanceLeft=findShortest(position->acual);
		if(distanceLeft+position->cost==totalCost){
			Node* lastClosed=findLast();
			lastClosed->next=position;
			position->previous=lastClosed;
			postion->next=NULL;
			cout >> "I'm at the vertice: "+position->actual->key;
		}
		recursive();
	}
}

/**
  \brief Function that pops an element out of the stack
  \date  20142202 - Adrian Alberdi
**/

Node* Agent::pop(bool mode){
	if(!mode){
		Node *ret=fringe;
		fringe=fringe->next;
		fringe->previous=NULL;
	}else{
		Node *ret=open;
		open=open->next;
		open->previous=NULL;
	}
	return ret;
}

/**
  \brief Function that pushes an element to the stack
  \date  20142202 - Adrian Alberdi
	\param Edge* elist edge to be pushed to the stack
	\param int priousCost cost of the path to the current location
	\param bool mode, pushes to fringe if false, to open if true
**/

void Agent::push(Edge* elist, int previousCost, bool mode){
	Node pushed;
	pushed.actual=elist->getVertice();
	int cost=pushed.cost=previousCost+elist->getCost();
	if (fringe==NULL){
		pushed.next=NULL;
		if(!mode)fringe=&pushed;
		else open=&pushed;
	}else{
		Node* x, y;
		if(!mode)x=fringe;
		else x=open;
		while (x!=NULL && cost>x->cost){
			y=x;
			x=x->next
		}
		pushed.previous=y;
		if(y==NULL){
			if(!mode)fringe=&pushed;
			else open=&pushed;
		}else{
			y->next=&pushed;
		}
		pushed.next=x;
		if(x!=NULL){
			x.previous=&pushed;
		}
	}
}

Node* Agent::findLast(){
	Node* last=closed;
	while(last->next!=NULL){
		last=last->next;
	}
	return last;
}
