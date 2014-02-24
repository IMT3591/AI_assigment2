//Magnus
#include "stdfx.h"
class Edge;
class Vertice;

#include "edge.h"
#include "vertice.h"

//	Fringes
struct Open{
	 int 			estCost;	//Estimated cost to reach this node
	 Vertice* vert;			//Vertice pointer to travel to
	 Open* 		nxt;			//Next item on the fringe
};

struct Closed{
	int 			totCost;
	Vertice*	vert;
	Closed*		nxt;
	Closed( int t, Vertice* v, Closed* n){
		totCost = t; vert = v; nxt = n;
	}
};

//	Variable declarations
Vertice*	vTail;		//	End element in list of Vertices
Vertice*	vStart;		//	Start element in list of Vertices
Open*			open;			//	Start element of global fringe
Closed*		closed;		//	Start element of global closed

//	Function declarations
void 	displayVert();
void	createEnv();
void	printOpen( Open* );
int 	shPath( Vertice* a, int b);
Open*	popOpen();
void pushOpen( Open*, int, Vertice* );

//	Main 
int main(){
	//Initiate starts and end elements
	vTail		= new Vertice(-1, NULL, NULL);
	vStart	=	new Vertice(-1, vTail, NULL);
	vTail->setNext( vTail );
	open 		= new Open();		open->estCost = -1;
													open->vert = NULL; 		open->nxt = NULL;

	createEnv();			//Generate graph environment
	displayVert();		//Print out all vertices with their connected edges
										//Test run for shortest path
	vStart->getNext();
	shPath( vStart->getNext(), 24 );
	cout << "\n\nExiting the program successfully\n";
	return 0;
}

	//Display all vertices
void displayVert(){
	Vertice* x = vStart->getNext();			//Vertice ptr set to first element
	while ( x != vTail ){								//While the ptr isn't at the Tail
		x->display();											//call the vertice display function
		x = x->getNext();									//go to next element in list
	}
}

Open* popOpen( Open* a ){
	int cost = -1;					//Variable to hold the currently lowest cost
	Open *x, *y;						//Pointers to Open elements

	while( a->nxt != NULL ){//Go through entire Fringe
		if( cost == -1 || a->nxt->estCost < cost ){//if el has the lowest cost
			cost = a->nxt->estCost;	//Update cost to the lowest value, yet
			x = a;									//Set ptr to the el before el with lowest cost
		}
		a = a->nxt;								//Skip to next element in Fringe
	}//end of while
	
	y = x->nxt;						// Y points to the lowest Open
	x->nxt = x->nxt->nxt;	// Hook out the element and move ptrs around
	y->nxt=NULL;					// NULL-out the Open elements nxt
	
	return y;						// Return vertice with lowest cost
}

	// Push element onto fringe
		//	z = fringe, e = estimated cost, v=vertice
void pushOpen( Open* z, int e, Vertice* v){
	Open* a = z;
	Open* t = new Open(); t->estCost = e; t->vert = v;
		//Go through the list until end or the vertice exists allready
	while( a->nxt != NULL && !a->nxt->vert->checkId( v->getId() )){
		a = a->nxt;	//Move to next element
	}
		//Check if the element existed in the fringe
	if( a->nxt != NULL && a->nxt->vert->checkId( v->getId() ) ){
			//If existing el is lower or equal don't update value
		if( a->estCost <= t->estCost ){	//Grab the existing element
			t = a->nxt;										
		}
		a->nxt = a->nxt->nxt;						//Remove el from fringe
	}
	a = z;		//Set element to initial item
	//Search fringe for correct position, descending order at back of equal el
	while( a->nxt != NULL && a->nxt->estCost >= t->estCost )
		a = a->nxt;
	t->nxt = a->nxt;	//Insert element
	a->nxt = t;				//In between the elements
}

void pushClosed( Closed* c, Vertice* v, int t ){
}

void printOpen( Open* f ){
	cout << "\nPQ: "; 					//Print a Priority Qeue
	while( f->nxt != NULL ){		//Go through the 
		f = f->nxt;								//go to next element
		f->vert->printId();				//Print the vertice's key
		cout << "(" << f->estCost << ")\t";//Print cost
	}
}

//Current position + id of goal node
int shPath( Vertice* a, int goal){
	int bCost = -1;		//Initial lowest cost for getting to goal
	Open* x;					//tmpEl for holding an el from the list
	Open* locFringe = new Open();	//Start of local fringe
	locFringe->nxt = NULL; locFringe->estCost = 0;
	Vertice* cur;			//Holds the current vertice
	Edge* trav;				//Holds the edge to travel
	trav = a->getEdge();//Set it to the first of the current node edge

		//Push edges from initial vertice to list
	while( trav->getNext() != NULL ){
		trav = trav->getNext();	//Go to next element
		cout << "\n" << "TR " << trav->getCost() << "\n";
		pushOpen( locFringe, trav->getCost(), trav->getVert() );//Push to fringe
	}
	
	while( locFringe->nxt != NULL ){
		x		= popOpen( locFringe );						//Grab 1st element of list
		cur 	= x->vert; 			//Pop vertice from PQ Fringe
		trav 	= cur->getEdge();						//Grab start-edge from vertice
		int cost = x->estCost;
		cout << "\nRetrieved: ";		// Print which edge is selected for expansion
		cur->printId();							// Print vertice id
		if( cur->checkId( goal ) ){	// Check if vertice is the goal node
			cout << "\nFound goal: "; // Print that it found the goal
			if( bCost == -1 || bCost > x->estCost ) //Update low cost if lower
				bCost = x->estCost;			
		}//end goal state
		else{
			while( trav->getNext() != NULL ){	//For all edges in list
																				//Push vertice onto fringe - (PQ)
				trav	= trav->getNext();				//Goto next element in list
				cost = 0;
				cost = x->estCost + trav->getCost();	//Current + edge cost
				//cout << "\n"; trav->getVert()->printId();
				//cout << "\tcost = estCost + travCost\t\t" << cost << "= " << x->estCost << " + " <<
				//	trav->getCost();
				if( cost < bCost || bCost < 0) //If cost is lower than the currently
																				//	optimal route
					pushOpen(locFringe, cost, trav->getVert());//Push element to fringe
			}//end pushing edges to stack
		}//end non-goal-state
		printOpen( locFringe );//Print the fringe
	}
	delete locFringe;//Delete the fringe - free up ram
	return bCost;
}

void createEnv(){
	int verts = 0;											//number of vertices in graph
	int start, end, cost;								//tmp values
	Vertice		*x = vStart,							//Vertice ptrs for searching
						*z = vStart;
	ifstream 	in;												//Input file
	in.open("../vertice.lst");
	
	if( in.is_open() ){
		in >> verts;											//Read number of vertices in graph
		for( int i=1; i<=verts; i++){			//Create vertices in list with unique keys
			while( x->getNext() != vTail ){ //Traverse to last position
				x = x->getNext();
			}//while
																			//Create vertice in last position
			Vertice* y = new Vertice( i, vTail, NULL );
			x->setNext( y ); 								//Move pointer for 2nd last vertice to the
																				//new node
		}//for
		
		while( !in.eof() ){								//To read the Edge list
			x = z = vStart;									//Initialize search location
			start = end = cost = -1;				//Initialize values;
			in >> start >> end >> cost;			//Read values from file
																			//Traverse list until vertice is found/end
			while( !x->checkId( start ) && x->getNext() != vTail )	x = x->getNext();
			while( !z->checkId( end 	) && z->getNext() != vTail )	z = z->getNext();
			x->createEdge( cost, z );				//Create edge from vertice A to vertice B
			z->createEdge( cost, x );				//Create edge from vertice B to vertice A
		}//while
	}//is_open
	in.close();													//Close file handle
}

