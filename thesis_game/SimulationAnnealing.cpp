#include "SimulationAnnealing.h"



SimulationAnnealing::SimulationAnnealing(PersonalData* _samples){
	T = 999999999999;
	v = 1;
	error = 0;
	personalData = _samples;

}


SimulationAnnealing::~SimulationAnnealing(){

}




//SA�ݪ��Oenergy=>�w�q��similarity
float SimulationAnnealing::energy(GameParameter *p, std::vector<ScoreData*> s){
	Statistic ss;
	vector<GameState*> states = personalData->getState(s);
	ss.calculateComplexity(p, states);
	GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, states);

	return ss.similarityOfRank(states, s);//�q���ƪ���H�ƪ����P
}