#include "GameState.h"


#ifndef NODE
#define NODE

class Node{
public:
	Node(GameState* state);
	~Node();
public:
	GameState* state;
	int f, g, h;
	//f = g + h
	//Node* parent;
};


#endif