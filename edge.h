//
#ifndef EDGE_H
#define EDGE_H

class Edge{
	private:
		bool 			status;
		int				cost;
		int				vert;
		Edge*			nxt;
	public:
		Edge( int, int, Edge* );
		Edge* getNext();
		void	setNext( Edge* );
};

Edge::Edge( int c, int v, Edge* n ){
	status	= false;
	cost		= c;
	vert		= v;
	nxt			= n;
}

//retrieve the next Edge
Edge* Edge::getNext(){
	return nxt;
}

//set the next edge
void Edge::setNext( Edge* x){
	nxt = x;
}


#endif

