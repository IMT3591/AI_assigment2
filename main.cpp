
#include "stdfx.h"
class Edge;
class Vertice;

#include "edge.h"
#include "vertice.h"

struct Open{
	 int 			estCost;
	 Vertice* vert;
	 Open* 		nxt;
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
Vertice*	vTail;
Vertice*	vStart;
Open*			open;
Closed*		closed;

//	Function declarations
void 	shPath( Vertice* );
void 	displayVert();
void	createEnv();
void	printOpen( Open* );
int 	shPath( Vertice* a, int b);

Vertice* popOpen();
void pushOpen( Open*, int, Vertice* );

//	Main 
int main(){
	vTail		= new Vertice(-1, NULL, NULL);
	vStart	=	new Vertice(-1, vTail, NULL);
	vTail->setNext( vTail );
	open 		= new Open();		open->estCost = -1;
													open->vert = NULL; 		open->nxt = NULL;

	createEnv();
	displayVert();
	shPath( vStart->getNext()->getNext()->getNext(), 4 );
	cout << "\n\nExiting the program successfully\n";
	return 0;
}

void displayVert(){
	Vertice* x = vStart->getNext();			//Vertice ptr set to first element
	while ( x != vTail ){								//While the ptr isn't at the Tail
		x->display();											//call the vertice display function
		x = x->getNext();									//go to next element in list
	}
}

			//Pop first el from fringe
Vertice* popOpen( Open* a ){
	Vertice* ret = NULL;
	int cost = -1;
	Open* x, *y;
	while( a->nxt != NULL ){
		if( cost == -1 || a->nxt->estCost < cost ){
			cost = a->nxt->estCost;
			ret = a->nxt->vert;
			x = a;	
		}
		a = a->nxt;
	}

	y = x->nxt;	x->nxt = x->nxt->nxt;	
	y->nxt=NULL;
	delete y;
	return ret;						// Return vertice
}

void pushOpen( Open* z, int e, Vertice* v){
	Open* a = z;
	Open* t = new Open(); t->estCost = e; t->vert = v;
		//cHECK IF IT IS ALREADY IN THE LIST	
	while( a->nxt != NULL && !a->nxt->vert->checkId( v->getId() )){
		a = a->nxt;
	}
			//Remove element if exists
	if( a->nxt != NULL && a->nxt->vert->checkId( v->getId() ) ){
			//If existing element is better match
		if( a->estCost < t->estCost ){	//Grab item
			t = a->nxt;
		}
		a->nxt = a->nxt->nxt;			//Remove from fringe
	}
	a = z;		//Find position
	while( a->nxt != NULL && a->nxt->estCost >= t->estCost )
		a = a->nxt;
	t->nxt = a->nxt;	//Insert element
	a->nxt = t;
}

void pushClosed( Closed* c, Vertice* v, int t ){
}

void printOpen( Open* f ){
	cout << "\nPQ: "; 
	while( f->nxt != NULL ){
		f = f->nxt;
		f->vert->printId();
		cout << "(" << f->estCost << ")\t";
	}
}

//Current position + id of goal node
int shPath( Vertice* a, int goal){
	int bCost = -1;
	Open* x;
	Open* locFringe = new Open();	//Start of local fringe
	locFringe->nxt = NULL; locFringe->estCost = 0;
	Vertice* cur;	
	Edge* trav;
	
	trav = a->getEdge();
		//Push edges from initial vertice to list
	while( trav->getNext() != NULL ){
		trav = trav->getNext();
		pushOpen( locFringe, trav->getCost(), trav->getVert() );
	}
	
	while( locFringe->nxt != NULL ){
		x			= locFringe->nxt;						//Grab 1st element of list
		cur 	= popOpen( locFringe );			//Pop vertice from PQ Fringe
		trav 	= cur->getEdge();						//Grab start-edge

		cout << "\nRetrieve: ";	cur->printId();
		if( cur->checkId( goal ) ){
			cout << "\nFound goal: "; 
			if( bCost == -1 || bCost > x->estCost )
				bCost = x->estCost;
		}
		else{
			while( trav->getNext() != NULL ){	//For all edges in list
																				//Push vertice onto fringe - (PQ)
				trav	= trav->getNext();				//Goto next element in list
				int cost = x->estCost+trav->getCost();	//Current + edge cost
				if( cost < bCost || bCost < 0)
					pushOpen(locFringe, cost, trav->getVert());
			}
		}
		printOpen( locFringe );
	}
	return bCost;
}

void createEnv(){
	int verts = 0;											//number of vertices in graph
	int start, end, cost;								//tmp values
	Vertice		*x = vStart,							//Vertice ptrs for searching
						*z = vStart;
	ifstream 	in;												//Input file
	in.open("vertice.lst");
	
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

