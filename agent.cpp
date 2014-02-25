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
int iteration=0;
/**
  \brief Constructor that sets the environment and the goal of the agent
  \date  20142202 - Adrian Alberdi
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
**/

Node* Agent::findAStar(Vertice* first, Vertice* last){
	first->display(); last->display();
	goal=last;
	closed = new Node();
	closed->actual=first;
	closed->cost=0;
	cout << "\nlooking for total cost";
	totalCost=findShortest(closed);
	Edge* elist=first->getEStart();
	cout << "\npushing from first vertice total cost " << totalCost;
	cout << "\n number of iterations: " << iteration;
	while(elist!=NULL){
		push(elist,0,true);
		elist = elist->getNext();
	}
	printOpen();
	recursive();
	cout << &goal;
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
	Edge* elist=first->actual->getEStart();
	while(elist != NULL){
		push(elist, first->cost, false);
		elist = elist->getNext();
	}
	//iteration++;
	return findShortest(pop(false));
}

/**
 * Private functions.
**/

void Agent::recursive(){
	iteration++;
	cout << "\nrecursion number: " << iteration;
	Node* position=pop(true);
	if(position->actual==goal){
		Node* lastClosed=findLast();
		lastClosed->next=position;
		position->previous=lastClosed;
		position->next=NULL;
		cout << "\nI've found the goal node The path I followed is: ";
		printOpen();
	}else{
		int distanceLeft=findShortest(position);
		if(distanceLeft==totalCost){
			cout << "\nI moved to the next node";
			Node* lastClosed=findLast();
			lastClosed->next=position;
			position->previous=lastClosed;
			position->next=NULL;
			Edge* elist=position->actual->getEStart();
			while(elist!=NULL){
				push(elist,position->cost,true);
				elist=elist->getNext();
			}

		}
		recursive();
	}
}

/**
  \brief Function that pops an element out of the stack
  \date  20142202 - Adrian Alberdi
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

void Agent::printOpen(){
	Node* foo = closed;
	while(foo!=NULL){
		cout << "\nCost: " << foo->cost;
		foo->actual->display();
		foo=foo->next;
	}
}
