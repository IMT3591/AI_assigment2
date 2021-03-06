//	Header file with basic includes
#include "stdfx.h"

//	Forward declaration of classes
class Edge;		
class Vertice;

//	Include external source code
#include "edge.h"
#include "vertice.h"
#include "agent.h" 		// 	Adrians Graph search algorithm

//	Variable declarations
Vertice*	vStart;			//	Start element in list of Vertices
Vertice*	vTail;			//	End element in list of Vertices
Agent* 		bender;			//Declare agent variable
char			graphFile[] = "vertice.lst";

//	Function declarations
void 	displayVert();
void	createEnv();
Vertice*	findVertice( int );
void shPath(int a, int b); 	//Adrians shortest path algorithm

//	Main 
int main(){
	
	//Initiate variables
	vTail		= new Vertice(-1, NULL, NULL);	//Initiate the end of vertice list
	vStart	=	new Vertice(-1, vTail, NULL);	//Initiate the start of vertice list
	vTail->setNext( vTail );								//Set vTail to point to itsself

	createEnv();												//Generate graph environment based on file

	bender = new Agent(vStart); 				//Adrians agent graph version
	
	int s=1, e=24;			//Id of start and end node
	do{
		cout << "\nRead in start and edge id between 1-24, \"0 0\" to quit:\t";
		cin  >> s >> e;				//Read in 2 integers form stdin
		if( (s >= 1 && s <= 24) && ( e >= 1 && e <= 24) ){//If integers in range
			cout << "\nBender: \"Traversing from \"" << s << " to " << e << ".\"";
			shPath(s, e); 			//Start algorithm
		}
	}while( (s >= 1 && s <= 24) && ( e >= 1 && e <= 24) );
	
	cout << "\n\nExiting the program successfully\n";
	bender->~Agent();
	return 0;
}

/** Display the vertices and their edges ascending **/
void displayVert(){
	Vertice* x = vStart->getNext();			//Vertice ptr set to first element
	while ( x != vTail ){								//While the ptr isn't at the Tail
		x->display();											//call the vertice display function
		x = x->getNext();									//go to next element in list
	}
}

/**	Search for and return the vertice with the key that equals k **/
Vertice* findVertice( int k ){
	Vertice* x = vStart->getNext();			//Set x to the first vertice in list
	while ( x != vTail ){								//While the ptr isn't at the Tail
		if( x->checkId( k ) )							//Return vertice if correct
			return x;
		x = x->getNext();									//go to next element in list
	}
	return NULL;												//Return NULL if not found
}

/**	Read number of vertices from file and populate the vertice list.
	Then read the edges from the file and create links between the vertices. **/
void createEnv(){
	int verts = 0;											//number of vertices in graph
	int start, end, cost;								//tmp values
	Vertice		*x = vStart,							//Vertice ptrs for searching when creating
						*z = vStart;							//	links between two nodes
	ifstream 	in;												//Input stream
	in.open( graphFile );								//open the file
	
	if( in.is_open() ){
		in >> verts;											//Read number of vertices in graph
		for( int i=1; i<=verts; i++){			//Create vertices in list with unique keys
			while( x->getNext() != vTail ){ //Traverse to last position
				x = x->getNext();							// move to next element in list
			}//while end
																			//Create vertice in last position
			Vertice* y = new Vertice( i, vTail, NULL );
			x->setNext( y ); 								//Move pointer for 2nd last vertice to the
																			//	new node
		}//for end
		while( !in.eof() ){								//To read the Edge list until end of file
			x = z = vStart;									//Initialize search ptrs to start of list
			start = end = cost = -1;				//Zero-out values;
			in >> start >> end >> cost;			//Read values from input stream
															//Traverse list until start & end vertice is found
			while( !x->checkId( start ) && x->getNext() != vTail )	x = x->getNext();
			while( !z->checkId( end ) 	&& z->getNext() != vTail )	z = z->getNext();
			x->createEdge( cost, z );				//Create edge from vertice A to vertice B
			z->createEdge( cost, x );				//Create edge from vertice B to vertice A
		}//while end
	}//is_open end
	in.close();					//Close handle to file
}

void shPath(int a, int b){
	Vertice *A, 
 					*B;
	int i;
	A = vStart->getNext();
	for( i=1; i<a; i++ ){
		A = A->getNext();                         //saves the node with id a in *A
	}
	B=vStart->getNext();
	for( i=1; i<b; i++ ){
		B = B->getNext();                         //saves the node with id b in *B
	}
	bender->findAStar( A, B );                         //call to the algorithm A*
}
