#include "agent.h"

/**
  \file   agent.cpp
  \brief  All functions for the agent searching in the environment
  \date   20142202 - Adrian Alberdi
**/

int timeComplexity=0;
int shortestIteration=0;
int recursiveI=0;

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
	deleteFringe();
	deleteOpen();
	deleteClosed();
	environment=NULL;
	delete environment;
	goal=NULL;
	delete goal;
	totalCost=0;
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
	timeComplexity+=5;
	while(elist!=NULL){
		push(elist,0,true);
		elist = elist->getNext();
		timeComplexity+=2;
	}
	recursiveI++;
	recursive();
	printClosed();
	cout << "\nTime complexity: " << timeComplexity;
	cout << "\nRecusive iterations: " << recursiveI;
	cout << "\nShortest path iterations: " << shortestIteration;
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
		timeComplexity+=2;
	}
	timeComplexity+=2;
	shortestIteration++;
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
		timeComplexity+=5;
	}else{
		int distanceLeft=findShortest(position);//Check if he is in the right path
		if(distanceLeft==totalCost){
			cout << "\nI moved to the next node";
			Node* lastClosed=findLast();
			lastClosed->next=position;
			position->previous=lastClosed;
			position->next=NULL;
			Edge* elist=position->actual->getEStart();
			timeComplexity+=7;
			while(elist!=NULL){
				push(elist,position->cost,true);//pushes the edges to the open list
				elist=elist->getNext();
				timeComplexity+=2;
			}
		}
		recursiveI++;
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
	timeComplexity+=6;
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
		timeComplexity+=8;
	}else{
		Node* x,* y;
		y=NULL;
		if(!mode)x=fringe;
		else x=open;
		timeComplexity+=8;
		while (x!=NULL && cost>x->cost){
			y=x;
			x=x->next;
			timeComplexity+=4;
		}
		pushed->previous=y;
		if(y==NULL){
			if(!mode)fringe=pushed;
			else open=pushed;
			timeComplexity+=4;
		}else{
			y->next=pushed;
			timeComplexity+=2;
		}
		pushed->next=x;
		if(x!=NULL){
			x->previous=pushed;
			timeComplexity+=3;
		}else	timeComplexity+=2;
	}
}

Node* Agent::findLast(){
	Node* last=closed;
	timeComplexity++;
	while(last->next!=NULL){
		last=last->next;
		timeComplexity+=2;
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

void Agent::deleteFringe(){
	Node* foo;
	while (fringe!=NULL){
		fringe->actual=NULL;
		delete fringe->actual;
		fringe->cost=0;
		foo=fringe;
		fringe=fringe->next;
		foo->previous=NULL;
		delete foo->previous;
		foo->next=NULL;
		delete foo->next;
		delete foo;
	}
	delete fringe;
}

void Agent::deleteOpen(){
	Node* foo;
	while (open!=NULL){
		open->actual=NULL;
		delete open->actual;
		open->cost=0;
		foo=open;
		open=open->next;
		foo->previous=NULL;
		delete foo->previous;
		foo->next=NULL;
		delete foo->next;
		delete foo;
	}
	delete open;
}

void Agent::deleteClosed(){
	Node* foo;
	while (closed!=NULL){
		closed->actual=NULL;
		delete closed->actual;
		closed->cost=0;
		foo=closed;
		closed=closed->next;
		foo->previous=NULL;
		delete foo->previous;
		foo->next=NULL;
		delete foo->next;
		delete foo;
	}
}
