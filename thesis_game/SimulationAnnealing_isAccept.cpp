#include "SimulationAnnealing.h"
extern HGE* hge;

bool SimulationAnnealing::isAccept(GameParameter* oldP, GameParameter* newP){
	float newE = 0;
	float oldE = 0;

	for(int i = 0; i < personalData->datas.size(); i++){
		oldE += abs(energy(oldP, personalData->datas[i]));
	}

	oldE = 1 - (oldE /  personalData->datas.size());


	for(int i = 0; i < personalData->datas.size(); i++){
		newE += abs(energy(newP, personalData->datas[i]));
	}

	newE = 1 - (newE /  personalData->datas.size());

	float deltaE = newE - oldE; //��error��serror���t�Z

	if(deltaE <= 0){//������C�N���W���� 
		return true;
	}else{
		float r = hge->Random_Float(0, 1);
		float pt = Boltzman(deltaE, T);
		if(r <= pt){
			return true;
		}	
	}
	return false;
}



