#include "GameParameter.h"
extern HGE* hge;

GameParameter::GameParameter(){
		B = hge->Random_Float(-1, 1);
		D = hge->Random_Float(-1, 1);
}


GameParameter* GameParameter::clone(){
		GameParameter* p = new GameParameter();	
		p->B = B;
		p->D = D;
		return p;
}




GameParameter::GameParameter(float a){
		B = a;	
		D = a;
}