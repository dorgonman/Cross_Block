#include "SimulationAnnealing.h"



extern HGE* hge;


void SimulationAnnealing::begin(GameParameter* p){

	parameter = p;
	GameParameter* oldP;
	GameParameter* newP;


	float threshold = 0.1f;

	int inf = 99999999999999999;
	float minError = 999;

	v = 1;
	for(int t = 0; t < inf; t++){
		T = schedule(t);
		//cout << T << endl;

		//cool down
		if(T == 0){
			//t = 0;
			//return;
		}
		float error = 0;
		

		for(int i = 0; i < personalData->datas.size(); i++){
			error += energy(parameter, personalData->datas[i]);
		}

		error = 1 - (error /  personalData->datas.size());

		if( error < minError){
			minError = error;
			cout << "iter:" << t << endl;
			cout << "error:" << minError << endl;
			cout << "parameter B:" << parameter->B << "  parameter D:" << parameter->D << endl;

		}

		oldP = parameter;
		newP = parameter->clone();
		newP->B = abs(parameter->B + hge->Random_Float(-v, v));

		if(isAccept(oldP, newP)){
			parameter = newP;
			delete oldP;
			oldP = NULL;
		}else{
			delete newP;
			newP = NULL;
		}



		
		oldP = parameter;
		newP = parameter->clone();
		newP->D = abs(parameter->D + hge->Random_Float(-v, v));

		if(isAccept(oldP, newP)){
			parameter = newP;
			delete oldP;
			oldP = NULL;
		}else{
			delete newP;
			newP = NULL;
		}

		
	}

}