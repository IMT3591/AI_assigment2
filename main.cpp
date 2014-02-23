
#include "stdfx.h"
class Edge;
class Vertice;

#include "edge.h"
#include "vertice.h"

struct Open{
	 int 			estCost;
	 int			curCost;
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
void pushOpen( int, int, Vertice* );

//	Main 
int main(){
	vTail		= new Vertice(-1, NULL, NULL);
	vStart	=	new Vertice(-1, vTail, NULL);
	vTail->setNext( vTail );
	open 		= new Open();		open->estCost = -1;		open->curCost = -1;
													open->vert = NULL; 		open->nxt = NULL;

	createEnv();
	displayVert();

	shPath( vStart->getNext(), 4 );
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
	if( a->nxt != NULL ){			//If x isn't NULL
		ret = a->nxt->vert;			//set ret to retrieved el's vertice
		a->nxt = a->nxt->nxt;		//move open's nxt pointer to the second element
	}
	return ret;						// Return vertice
}

void pushOpen( Open* z, int e, int c, Vertice* v){
	Open* a = z;
	
	Open* t = new Open(); t->estCost = e; t->vert = v; t->curCost = c;
	while( a->nxt != NULL && !a->nxt->vert->checkId( v->getId() ))
		a = a->nxt;

			//Remove element if exists
	if( a->nxt != NULL && a->nxt->vert->checkId( v->getId() ) ){
			//If existing element is better match
		if( (a->estCost+a->curCost) <= (t->curCost+t->estCost) )	//Grab item
			t = a->nxt;
		a->nxt = a->nxt->nxt;			//Remove from fringe
	}

	a = z;		//Find position
	while( a->nxt != NULL && !a->nxt->estCost >= e )
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
		f->vert->printId(); cout << " ";
	}
}

//Current position + id of goal node
int shPath( Vertice* a, int goal){
	int bCost = -1;
	Open* x;
	Open* locFringe = new Open();	//Start of local fringe
	locFringe->nxt = NULL; locFringe->estCost = locFringe->curCost = 0;
	Vertice* cur;
	Edge* trav;
	
	trav = a->getEdge();
	while( trav->getNext() != NULL ){
		trav = trav->getNext();
		pushOpen( locFringe, trav->getCost(), 0, trav->getVert() );
	}
	
	printOpen( locFringe );

	while( locFringe->nxt != NULL ){
		x			= locFringe->nxt;						//Grab 1st element of list
		cur 	= popOpen( locFringe );			//Pop vertice from PQ Fringe
		cout << "\nRetrieve: "; cur->printId();
		if( cur->checkId(goal) ){
			if( bCost == -1 || bCost > x->estCost )	bCost = x->estCost;
		}else{
			trav 	= cur->getEdge();						//Grab start-edge
			while( trav->getNext() != NULL ){	//For all edges in list
				trav	= trav->getNext();				//Goto next element in list
																				//Push vertice onto fringe - (PQ)
				pushOpen( locFringe, 			 x->estCost + trav->getCost(), 	0, 
									trav->getVert() );
			}
			printOpen( locFringe );
		}
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

