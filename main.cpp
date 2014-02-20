#include <stdio.h>
#include <iostream>
#include <fstream>
#include "vertice.h"
#include "edge.h"

using namespace std;

void createEnvironment();

int main(){
	createEnvironment();
	return 0;
}

void createEnvironment(){
	ifstream in;
	char str[100];
	in.open("vertice.lst");
	if(in.is_open()){
		while( !in.eof() ){
			in >> str;
			cout << str;
		}
	}
	in.close();
}

