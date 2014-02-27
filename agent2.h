#ifndef AGENT2_H
#define AGENT2_H

#include "edge.h"
#include "vertice.h"


struct Fringe{
	int				travCost;	//Used by A*, not shp
	int 			estCost;	//Used by A* and shp
	Vertice*	vert;			//The vertice it links to
	Fringe*		nxt;			//Nxt Fringe element
	Fringe( ){					//Used for setting header elements
		estCost = -1;	vert= NULL; nxt = NULL; travCost = -1;
	}
											//Used for creating elements in shp
	Fringe( int e, Vertice* v, Fringe* n ){
		estCost = e;	vert= v; nxt = n; travCost = -1;
	}
											//Used for creating elements in A*
	Fringe( int e, int t, Vertice* v, Fringe* n ){
		estCost = e;	travCost = t;	vert= v; nxt = n;
	}
};

class Agent{
	private:
		int 			goalKey;
		Vertice*	location;
		int 			travCost;

	public:
		Agent();
		Agent( Vertice*, int );
		~Agent();
		void			upInfo( Vertice*, int );
		int				shp( Vertice*, int );
		void			aStar( );
		void			pushFringe( Fringe*, Fringe* );
		Fringe*		popFringe( Fringe* );
		void 			printFringe( Fringe* );
};

#endif
