#include <stdio.h>
#include <iostream>
#include <fstream>

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
	while( !in.eof() ){
		in >> str;
		cout << str;
	}
	in.close();
}

