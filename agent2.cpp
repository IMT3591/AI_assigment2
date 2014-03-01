
#include "agent2.h"

Agent::Agent(){				//Zero constructor
	location	= NULL;
	goalKey		= 0;
	travCost	= 0;
	execCount	= 0;
}

//Used for creating the agent with an initial locaiton, a goal node and zeroed
//travel cost
Agent::Agent( Vertice* x, int gKey ){
	location	= x;		
	goalKey		= gKey;
	travCost	= 0;
	execCount	= 0;
	cout << "\nBender: That's it we're boned.\n";
	cout << "\nBender: Don’t touch my stuff when I’m dead…its booby trapped!\n";
}

Agent::~Agent(){
	location	= NULL;
	goalKey		= 0;
	travCost	= 0;
	execCount	= 0;
	delete location;
}

void Agent::count( int c = 1 ){
	execCount += c;
}

int Agent::getCount( ){
	return execCount;
}

void Agent::upInfo( Vertice* x, int gKey ){ //Used to update location and goal
	location	= x;
	goalKey		= gKey;
	travCost	= 0;
}

/**	Finds the cost of the shortest path from vertice and to the goal node	**/
int Agent::shp( Vertice* v, int goal ){
	int bCost = -1;		//keeps the optimal score value
	int			 tmpC;		//keeps the current score value
	Fringe 	*tmpF;		//holds the current fringe element popped from list
	Fringe	*newF;		//used to create new fringe elements
	Vertice	*tmpV;		//Holds the current fringe elements vertice
	Edge		*tmpE;		//Holds the current edge at current vertice
	count( 8 );
	if( v->checkId( goal ) )		//If current node is the goal, cost is 0
		return 0;									// avoids extra traversal and cost

	Fringe* locFringe = new Fringe();	//The local fringe for algorithm
	tmpE 		= v->getEdge();						//Get edgestar from vertice
	tmpC 		= 0;											//resets the tmpC to 0
	count( 9 );
	while( tmpE->getNext() != NULL ){	//Traverse the edges of current vertice
		tmpE = tmpE->getNext();					//Set tmpE to next edge in list
																		//Create new fringe element
		newF = new Fringe( tmpE->getCost(), tmpE->getVert(), NULL );
		pushFringe( locFringe, newF );	//Push fringe element to fringe
		count( 13 );
	}

	while( locFringe->nxt != NULL ){	//Perform actions while fringe isn't empty
		tmpC = 0;												//Reset tmpC to 0
		tmpF = popFringe( locFringe );	//Set tmpF to cheapes option from fringe
		tmpC = tmpF->estCost;						//Grab estimated cost from fringe element
		tmpV = tmpF->vert;							//Grab link vertice form fringe element	
		tmpE = tmpV->getEdge();					//Grab edge start from the vertice
		
		count( 9 );

		if( tmpV->checkId( goal ) ){		//If current vertice is goal node
			if( bCost == -1 || bCost > tmpF->estCost ){ //Check if currently best path
				bCost = tmpF->estCost + tmpF->travCost;			//Update path cost
				count( 2 );
			}//End if current lowest path cost
		}//End goal node
		else{														//If not goal node
			while( tmpE->getNext() != NULL ){ //for all elements in current edge list
				tmpE = tmpE->getNext();			//set tmpE to next edge in list
				tmpV = tmpE->getVert();			//set tmpV to the edges vertice ptr
				tmpC = 0;										//zero out tmpC
				tmpC = tmpF->estCost + tmpE->getCost(); //Calculate new tmpC
				count( 13 );
				if( tmpC < bCost || bCost < 0 ){	//If tmpC is lower than optimal path
																					//Create new fringe element with newF
					newF = new Fringe( tmpC, tmpE->getVert(), NULL );
					pushFringe( locFringe, newF );	//Push newF onto fringe
					count( 9 );
				}//End pushing new elements to fringe
			}//End going through the vertice's edges
			//printFringe( locFringe );
		}//End not goal node
		delete tmpF;  //Delete unhooked and used Fringe element
		count( 9 );
	}//End fringe traversal
	delete locFringe;
	count( 9 );
	cout << "\nTIME (shp): "  << getCount() << "\n";
	return bCost;
}


/**	This A* Tree Traversal algorithm finds the optimal path from initial
 * locaiton to end.  It uses the traveld cost along with the estimated cost of
 * getting to the goal, The estimation function uses a shortest path algorithm
 * to calculate the heuristic.	**/
void Agent::aStar( ){
	Fringe 	*tmpF;				//Holds the current fringe element in use
	Vertice	*tmpV;				//Holds the current fringe elements vertice
	Edge		*tmpE;				//Hodls the tmpV's edge start item
	int			tmpC 	= 0;		//Holds the current cost
	int			tmpT	= 0;		//Holds the current travel cost
	int			oCost = -1;		//Holds the cost of the optimal path
	count( 9 );

	if( location->checkId( goalKey ) ){
		cout << "\n\nBender: \"Game's over, losers! I'm allready at the solution, "
				 <<	goalKey << "[" << 0 << "]. Compare your solution to "
				 <<	"mine and then kill yourselves.\"";
		cout << "\nTIME (shp): "  << getCount() << "\n";
		return;
	}

												//Create the element for initial position with 0 cost
												//	and 0 estimation cost since it doesn't matter
	Fringe* x 		= new Fringe( 0, 0, location, NULL );
	Fringe* open	= new Fringe();		//Create the fringe list to hold the elements
	pushFringe( open, x );								//Push initial element onto fringe

	count( 11 );

	while( open->nxt != NULL ){						//While the fringe isn't empty
		tmpF	= popFringe( open );					//Pop lowest element from fringe
		tmpV	= tmpF->vert;									//Grab vertice from fringe element
		tmpE	= tmpV->getEdge();						//Grab start of edges from vertice

		count( 5 );
		if( tmpV->checkId( goalKey ) ){			//If current item is the goal node
																				//Check if it is the optimal path
			if( oCost < 0 || oCost > tmpF->travCost+tmpF->estCost ){
				cout << "\n\nBender: \"Game's over, losers! I have found the solution, "
						 <<	goalKey << "[" << tmpF->travCost+tmpF->estCost << "]. Compare your solutions to "
						 <<	"mine and then kill yourselves.\"";
				oCost = tmpF->travCost;					//Print message and update oCost
				count( 4 );
				cout << "\nTIME (shp): "  << getCount() << "\n";
			}	//End new best score check
			cout << "\n";
			count( 2 );
		}//End goal check
		else if( oCost < 0 || tmpF->travCost+tmpF->estCost < oCost ){
			cout << "\n\nAt: " << tmpV->getId();
		
			while( tmpE->getNext() != NULL ){	//While not end of edge list
				tmpE	= tmpE->getNext();				//traverse to next edge
				tmpT 	= tmpF->travCost + tmpE->getCost();	//Travel cost
				tmpC	= shp( tmpE->getVert(), goalKey );	//cost estimate
																				//Create new fringe element
				x 		= new Fringe( tmpC, tmpT, tmpE->getVert(), NULL );
				pushFringe( open, x );					//Push element to fringe
				cout << "\t" << x->vert->getId() << "[" << tmpC + tmpT << "] ";
				count( 20 );
			}//End pushing new edges to fringe
		}//End check if current fringe element has a lower optimal score

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
	int 		tmpC = -1;									//Current lowest cost value
	int			estC = 0;										//Combined value of estCost and travCost
	Fringe	*tmpF1,											//Traverses the fringe
					*tmpF2;											//Holds element prior to real element
	tmpF1 = fringe;											//Set tmpF1 to head of fringe
	while( tmpF1->nxt != NULL ){				//While not end of list
		estC 			= tmpF1->nxt->estCost + tmpF1->nxt->travCost;
		if( tmpC == -1 || estC <= tmpC ){	//If best/equal cost
			tmpC 		= estC;									//Update cost value to lowest/equal
			tmpF2		= tmpF1;								//Element prior to real element
			count( 2 );
		}
		tmpF1 		= tmpF1->nxt;						//Traverse to next element
		count( 4 );
	}
	tmpF1	   		= tmpF2->nxt;						//Unlink element from list
	tmpF2->nxt	= tmpF1->nxt;						//And link list back together
	tmpF1->nxt	= NULL;									//Remove nxt link for return element
	count( 9 );
	return tmpF1;
}

void Agent::pushFringe( Fringe* fringe, Fringe* el ){
	Fringe* a = fringe;
	int estC1 = el->estCost + el->travCost;
	int estC2 = 0;
	count( 3 );
																	//find element prior to real element
	while( a->nxt != NULL && !a->nxt->vert->checkId( el->vert->getId() ) ){
		a = a->nxt;										//Move to next element
		count( 5 );
	}
																	//If real element == the current element
	if( a->nxt != NULL && a->nxt->vert->checkId( el->vert->getId() ) ){
		estC2 = a->nxt->estCost + a->nxt->travCost;
		if( estC2 <= estC1 ){					//If real element is better or equal 
																	//	to new element
			el = a->nxt;								//Set new element pointer to real element
			estC1 = estC2;
			count( 3 );
		}
		a->nxt = a->nxt->nxt; 				//Unlink real element
		count( 6 );
	}
	a = fringe;											//Set a to point to head of node
	count( 2 );
																	//Find position prior to the new elements 
	while( a->nxt != NULL && ( a->nxt->estCost + a->nxt->travCost) >= estC1 ){ // position
		a = a->nxt;										//Move to next element
		count( 3 );
	}
	el->nxt = a->nxt;								//Link new element to list	
	a->nxt = el;	
	count( 2 );
}

