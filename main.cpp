#include <stdio.h>
#include <iostream>
#include <fstream>
#include "vertice.h"
#include "edge.h"

using namespace std;

Vertice* vTail 	= new Vertice(-1, NULL, NULL);
Vertice* vStart =	new Vertice(-1, vTail, NULL);

void createEnvironment();

int main(){
	vTail->setNext( vTail );
	createEnvironment();
	return 0;
}

void createEnvironment(){
	ifstream in;
	Vertice* x = vStart;
	Vertice* z = vStart;
	int verts = 0;
	in.open("vertice.lst");
	if( in.is_open() ){
		in >> verts;
		for( int i=1; i<=verts; i++){
			while( x->getNext() != vTail ){
				x = x->getNext();
			}
			Vertice* y = new Vertice( i, vTail, NULL );
			x->setNext( y ); 
		}
		int start, end, cost;
		while( !in.eof() ){
			x = vStart;
			z = vStart;
			start = end = cost = -1;
			in >> start >> end >> cost;
			while( !x->checkID( start ) && x->getNext() != vTail )	x = x->getNext();
			x->createEdge( cost, end );
			while( !z->checkID( end 	) && z->getNext() != vTail )	z = z->getNext();
			z->createEdge( cost, start );
		}
	}
	in.close();
}

