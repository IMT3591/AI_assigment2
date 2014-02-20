// 
#ifndef	VERTICE_H
#define VERTICE_H

#include "edge.h"
using namespace std;

Edge* 	eTail = new Edge( 1, -1, NULL );

class Vertice{
	private:
		int 			key;
		char*			name;
		bool			visited;
		Vertice*	nxtVert;
		Edge*			eStart;
	public:
		Vertice();
		Vertice( int, Vertice*, char* );
		~Vertice();
		Vertice*	getNext();
		void			setNext( Vertice* );
		void 			createEdge( int, int );
		bool 			checkId( int );
		void			display();
};

Vertice::Vertice( int k, Vertice* v, char* n ){
	key			= k;
	nxtVert = v;
	visited = false;
	name		= n;
	eStart 	= new Edge( -1, -1, eTail );
};

Vertice* Vertice::getNext(){
	return nxtVert;
}

void Vertice::setNext( Vertice* x ){
	nxtVert = x;
}

bool Vertice::checkId( int k ){	
	if( key == k )	return true;
	return false;
}

void Vertice::createEdge( int c, int v ){
	Edge* x = new Edge( c, v, eTail );
	Edge* y = eStart;
	while( y->getNext() != eTail ){
		y = y->getNext();
	}
	x->setNext( y->getNext() );
	y->setNext( x );
}

void Vertice::display(){
	cout << "\nID:\t" << key;
	Edge* x = eStart;
	while( x != eTail ){
		x = x->getNext();
	}
}

#endif
