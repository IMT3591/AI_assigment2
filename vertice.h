// 
#ifndef	VERTICE_H
#define VERTICE_H

#include "edge.h"

class Vertice{
	private:
		int 			key;
		bool			visited;
		Vertice*	nxtVert;
		Edge*			eStart;
	public:
		Vertice();
		Vertice( int, Vertice* );
		~Vertice();

		bool checkId( int );
		void createEdge();
};

Vertice::Vertice( int, Vertice* ){};

bool Vertice::checkId( int k ){	
	if( key == k )	return true;
	return false;
}

void Vertice::createEdge( int c, Vertice* v ){
	Edge* x = new Edge( c, v );
	Edge* y = eStart;
	while( y->next != eTail ){
		y = y->next;
	}
	x->next( y->next() );
	y->next( x );
}

#endif
