

class Edge{
	private:
		bool 			status;
		int				cost;
		Vertice*	vert;
		Edge*			nxt;
	public:

};

//retrieve the next Edge
Edge* Edge::next(){
	return next;
}

//set the next edge
void Edge::next( Edge* x){
	nxt = x;
}

