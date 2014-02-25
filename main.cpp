
#include "stdfx.h"
class Edge;
class Vertice;

#include "edge.h"
#include "vertice.h"
#include "agent.h"

struct Open{
	 int 			estCost;
	 int			curCost;
	 Vertice* vert;
	 Open 	*	nxt;
};

struct Closed{
	Vertice* 	vert;
	Closed	*	next;
};

//Variable declarations
Vertice*	vTail;
Vertice*	vStart;

Open*			open;
Closed*		closed;
Agent* bender;

//	Function declarations
void 	displayVert();
void	createEnv();
void shPath(int a,int b);

//	Main 
int main(){
	vTail		= new Vertice(-1, NULL, NULL);
	vStart	=	new Vertice(-1, vTail, NULL);
	vTail->setNext( vTail );
	open 		= new Open();		open->estCost = -1;		open->curCost = -1;
													open->vert = NULL; 		open->nxt = NULL;
	createEnv();
	displayVert();
	bender = new Agent(vStart);
	shPath(1,24);
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

/**
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

**/

void shPath(int a, int b){
	Vertice * A, * B;
	int i;
	A=vStart->getNext();
	for(i=1;i<a;i++){
		A=A->getNext();
	}
	B=vStart->getNext();
	for(i=1;i<b;i++){
		B=B->getNext();
	}
	bender->findAStar(A,B);
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

