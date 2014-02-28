#include "agent.h"

/**
  \file   agent.cpp
  \brief  All functions for the agent searching in the environment
  \date   20142202 - Adrian Alberdi
**/

/**
	Variables:

	Node* fringe;                           //Fringe for shortest path algorithm
        Node* open;                             //Fringe for A* algorithm
        Node* closed;                           //Closed list for the A*
        Vertice* goal;
        Vertice* environment;
        int totalCost;                          //Total cost of the path from the begging to the goal
**/

/**
  \brief Constructor that sets the environment and the goal of the agent
  \date  20142202 - Adrian Alberdi
	\Param Vertice* env environment where to move
**/

Agent::Agent(Vertice* env){
	environment=env;
	fringe=NULL;
	open=NULL;
	cout << "\nAgent created";
}

/**
  \brief Deconstructor
**/

Agent::~Agent(){
}

/**
  \brief Main function of the agent. Finds the shortest path to the destination.
  \date  20142202 - Adrian Alberdi
	\Param Vertice* first Where the agent starts it's journey
	\Param Vertice* goal  Where the user wants to go
**/

Node* Agent::findAStar(Vertice* first, Vertice* last){
	goal=last;
	closed = new Node();
	closed->actual=first;
	closed->cost=0;
	totalCost=findShortest(closed);
	Edge* elist=first->getEStart();
	while(elist!=NULL){
		push(elist,0,true);
		elist = elist->getNext();
	}
	recursive();
	printClosed();
	return closed;
}

/**
 * Private functions
**/

/**
  \brief Function that finds the cost to of the shortest path from the current position to the goal
  \date  20142202 - Adrian Alberdi
	\param Node* first current position of the algorithm in the graph
**/

int Agent::findShortest(Node* first){
	if(first->actual == goal){
		return first->cost;
	}
	Edge* elist=first->actual->getEStart();
	while(elist != NULL){
		push(elist, first->cost, false);
		elist = elist->getNext();
	}
	return findShortest(pop(false));
}

/**
  \brief recursive function for running A* algorithm
  \date  20142502 - Adrian Alberdi
**/

void Agent::recursive(){
	Node* position=pop(true);			//pop the first element of the open list
	if(position->actual==goal){			//Check if is the goal node
		Node* lastClosed=findLast();		//Saves the last node in the closed list and returns
		lastClosed->next=position;
		position->previous=lastClosed;
		position->next=NULL;
		cout << "\nI've found the goal node The path I followed is: ";
	}else{
		int distanceLeft=findShortest(position);//Check if he is in the right path
		if(distanceLeft==totalCost){
			cout << "\nI moved to the next node";
			Node* lastClosed=findLast();
			lastClosed->next=position;
			position->previous=lastClosed;
			position->next=NULL;
			Edge* elist=position->actual->getEStart();
			while(elist!=NULL){
				push(elist,position->cost,true);//pushes the edges to the open list
				elist=elist->getNext();
			}

		}
		recursive();
	}
}

/**
  \brief Function that pops an element out of the stack
  \date  20142202 - Adrian Alberdi
	\Param bool mode, tells which list to pop from, if true fringe if false open list
**/

Node* Agent::pop(bool mode){
	Node* ret;
	if(!mode){
		ret=fringe;
		fringe=fringe->next;
		if(fringe!=NULL)
		fringe->previous=NULL;
	}else{
		ret=open;
		open=open->next;
		if(open!=NULL)
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
	Node* pushed = new Node();
	pushed->actual = elist->getVertice();
	int cost=pushed->cost=previousCost+elist->getCost();
	if ((fringe==NULL && !mode) || (open==NULL && mode)){
		pushed->next=NULL;
		if(mode)open=pushed;
		else fringe=pushed;
	}else{
		Node* x,* y;
		y=NULL;
		if(!mode)x=fringe;
		else x=open;
		while (x!=NULL && cost>x->cost){
			y=x;
			x=x->next;
		}
		pushed->previous=y;
		if(y==NULL){
			if(!mode)fringe=pushed;
			else open=pushed;
		}else{
			y->next=pushed;
		}
		pushed->next=x;
		if(x!=NULL){
			x->previous=pushed;
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

void Agent::printClosed(){
	Node* foo = closed;
	while(foo!=NULL){
		cout << "\nCost: " << foo->cost;
		foo->actual->display();
		foo=foo->next;
	}
}
