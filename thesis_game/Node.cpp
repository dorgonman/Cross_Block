#include "Node.h"




Node::Node(GameState* _state){
	state = _state;
	g = 0;
	h = 0;
	f = g + h;



}


Node::~Node(){
	if(state){
		delete state;
		state = NULL;
	}

}
