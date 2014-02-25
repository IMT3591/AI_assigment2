
#include "stdfx.h"
class Edge;
class Vertice;

#include "edge.h"
#include "vertice.h"
#include "agent.h"

//Variable declarations
Vertice*	vTail;
Vertice*	vStart;

Agent* bender;

//	Function declarations
void 	displayVert();
void	createEnv();
void    shPath(int a,int b);

//	Main 
int main(){
	vTail	= new Vertice(-1, NULL, NULL);
	vStart	= new Vertice(-1, vTail, NULL);
	vTail->setNext( vTail );
	createEnv();
	displayVert();
	bender = new Agent(vStart);
	shPath(1,24);
	cout << "\n\nExiting the program successfully\n";
	return 0;
}

void displayVert(){
	Vertice* x = vStart->getNext();			//Vertice ptr set to first element
	while ( x != vTail ){				//While the ptr isn't at the Tail
		x->display();				//call the vertice display function
		x = x->getNext();			//go to next element in list
	}
}

void shPath(int a, int b){
	Vertice * A, * B;
	int i;
	A=vStart->getNext();
	for(i=1;i<a;i++){
		A=A->getNext();				//saves the node with id a in *A
	}
	B=vStart->getNext();
	for(i=1;i<b;i++){
		B=B->getNext();				//saves the node with id b in *B
	}
	bender->findAStar(A,B);				//call to the algorithm A*
}

void createEnv(){
	int verts = 0;					//number of vertices in graph
	int start, end, cost;				//tmp values
	Vertice	*x = vStart,				//Vertice ptrs for searching
		*z = vStart;
	ifstream in;					//Input file
	in.open("vertice.lst");
	if( in.is_open() ){
		in >> verts;				//Read number of vertices in graph
		for( int i=1; i<=verts; i++){		//Create vertices in list with unique keys
			while( x->getNext() != vTail ){ //Traverse to last position
				x = x->getNext();
			}//while
							//Create vertice in last position
			Vertice* y = new Vertice( i, vTail, NULL );
			x->setNext( y ); 		//Move pointer for 2nd last vertice to the
							//new node
		}//for
		while( !in.eof() ){			//To read the Edge list
			x = z = vStart;			//Initialize search location
			start = end = cost = -1;	//Initialize values;
			in >> start >> end >> cost;	//Read values from file
							//Traverse list until vertice is found/end
			while( !x->checkId( start ) && x->getNext() != vTail )	x = x->getNext();
			while( !z->checkId( end ) && z->getNext() != vTail )	z = z->getNext();
			x->createEdge( cost, z );	//Create edge from vertice A to vertice B
			z->createEdge( cost, x );	//Create edge from vertice B to vertice A
		}//while
	}//is_open
	in.close();					//Close file handle
}

