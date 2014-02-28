
#include "agent2.h"

Agent::Agent(){
	location	= NULL;
	goalKey		= 0;
	travCost	= 0;
}

Agent::Agent( Vertice* x, int gKey ){
	location	= x;
	goalKey		= gKey;
	travCost	= 0;
}

Agent::~Agent(){
}

void Agent::upInfo( Vertice* x, int gKey ){
	location	= x;
	goalKey		= gKey;
	travCost	= 0;
}

int Agent::shp( Vertice* v, int goal ){
	int bCost = -1;
	Fringe 	*tmpF;		Vertice	*tmpV;
	Edge		*tmpE;		int			 tmpC;
	Fringe	*newF;
	Fringe* locFringe = new Fringe();
	tmpE 		= v->getEdge();
	tmpC 		= 0;
	
	while( tmpE->getNext() != NULL ){
		tmpE = tmpE->getNext();
		newF = new Fringe( tmpE->getCost(), tmpE->getVert(), NULL );
		pushFringe( locFringe, newF );
	}

	while( locFringe->nxt != NULL ){
		tmpC = 0;
		tmpF = popFringe( locFringe );
		tmpC = tmpF->estCost;
		tmpV = tmpF->vert;
		tmpE = tmpV->getEdge();

		//cout << "\nRetrieved: "; 	tmpV->printId();
		if( tmpV->checkId( goal ) ){	//If current vertice is goal node
			//cout << "\n\tSHP: " << goal << " at cost " << tmpF->estCost;
			if( bCost == -1 || bCost > tmpF->estCost ){ //Check if currently best path
				bCost = tmpF->estCost;	//Update path cost
			}//End if current lowest path cost
		}//End goal node
		else{
			while( tmpE->getNext() != NULL ){
				tmpE = tmpE->getNext();
				tmpV = tmpE->getVert();
				tmpC = 0;
				tmpC = tmpF->estCost + tmpE->getCost();
			//	cout << "\n: "; tmpE->getVert()->printId();
			//	cout << ":\t" << tmpC << "=" << tmpF->estCost << "+" << tmpE->getCost(); 
				if( tmpC < bCost || bCost < 0 ){
					newF = new Fringe( tmpC, tmpE->getVert(), NULL );
					pushFringe( locFringe, newF );
				}//End pushing new elements to fringe
			}//End going through the vertice's edges
			//printFringe( locFringe );
		}//End not goal node
		//delete tmpF;  //Delete unhooked and used Fringe element
	}//End fringe traversal
	//delete locFringe;
	return bCost;
}

void Agent::aStar( ){
	Fringe 	*tmpF;		Vertice	*tmpV;
	Edge		*tmpE;		int			tmpC 	= 0;
	int			tmpT = 0;	int			oCost = -1;
	Fringe* x 		= new Fringe( 0, 0, location, NULL );
	Fringe* open	= new Fringe();
	pushFringe( open, x );

	while( open->nxt != NULL ){
		tmpF	= popFringe( open );				//Pop lowest element from fringe
		tmpV	= tmpF->vert;								//Grab vertice from fringe element
		tmpE	= tmpV->getEdge();					//Grab start of edges from vertice
		if( tmpV->checkId( goalKey ) ){
			cout << "\n\nFOUND GOAL WITH A* AT " << tmpF->travCost+tmpF->estCost << " COST";
			if( oCost < 0 || oCost > tmpF->travCost+tmpF->estCost ){
				cout << "\nNEW OPTIMAL PATH AT " << tmpF->travCost+tmpF->estCost << " COST";
				oCost = tmpF->travCost;
			}
			cout << "\n\n";
		}
		else if( oCost < 0 || tmpF->travCost+tmpF->estCost < oCost ){
			cout << "\nAt: " << tmpV->getId() << "\t\tPushing: ";
			while( tmpE->getNext() != NULL ){	//While not end of edge list
				tmpE	= tmpE->getNext();				//traverse to next edge
				tmpT 	= tmpF->travCost + tmpE->getCost();	//Travel cost
				tmpC	= shp( tmpE->getVert(), goalKey );	//cost estimate
																				//Create new fringe element
				x 		= new Fringe( tmpC, tmpT, tmpE->getVert(), NULL );
				pushFringe( open, x );					//Push element to fringe
				cout << x->vert->getId() << " [" << tmpC+tmpT << "] ";
			}
			cout << " to open list";
		}
		printFringe( open );	//Print fringe
		//delete tmpF;
	}//End open fringe
}

void Agent::printFringe( Fringe* lst ){
	cout << "\nPQ: ";	
	Fringe* el = lst;											// Set el to start of list
	while( el->nxt != NULL ){							// While next isnt't end of list
		el = el->nxt;												// traverse to next element
		el->vert->printId();								// print id of elements vertice link
		cout << "[" << el->travCost + el->estCost << "]  ";//Print estimated cost
	}
}

Fringe* Agent::popFringe( Fringe* fringe ){
	int 		tmpC = -1;					//Current lowest cost value
	int			estC = 0;				//Combined value of estCost and travCost
	Fringe	*tmpF1,						//Traverses the fringe
					*tmpF2;						//Holds element prior to real element
	tmpF1 = fringe;						//Set tmpF1 to head of fringe
	while( tmpF1->nxt != NULL ){	//While not end of list
		estC = tmpF1->nxt->estCost + tmpF1->nxt->travCost;
		if( tmpC == -1 || estC <= tmpC ){//If best/equal cost
			tmpC 	= estC;	//Update cost value to lowest/equal
			tmpF2	= tmpF1;								//Element prior to real element
		}
		tmpF1 = tmpF1->nxt;			//Traverse to next element
	}
	tmpF1	   = tmpF2->nxt;				//Unlink element from list
	tmpF2->nxt = tmpF1->nxt;	//And link list back together
	tmpF1->nxt = NULL;				//Remove nxt link for return element
	return tmpF1;
}

void Agent::pushFringe( Fringe* fringe, Fringe* el ){
	Fringe* a = fringe;
	int estC1 = el->estCost + el->travCost;
	int estC2 = 0;
		//find element prior to real element
	while( a->nxt != NULL && !a->nxt->vert->checkId( el->vert->getId() ) ){
		a = a->nxt;		//Move to next element
	}
		//If real element == the current element
	if( a->nxt != NULL && a->nxt->vert->checkId( el->vert->getId() ) ){
		estC2 = a->nxt->estCost + a->nxt->travCost;
		if( estC2 <= estC1 ){	//If real element is better or equal 
																					//	to new element
			el = a->nxt;										//Set new element pointer to real element
			estC1 = estC2;
		}
		a->nxt = a->nxt->nxt; 						//Unlink real element
	}
	a = fringe;													//Set a to point to head of node
																			//Find position prior to the new elements 
	while( a->nxt != NULL && ( a->nxt->estCost + a->nxt->travCost) >= estC1 ){ // position
		a = a->nxt;		//Move to next element
	}
	el->nxt = a->nxt;	//Link new element to list	
	a->nxt = el;				
}

