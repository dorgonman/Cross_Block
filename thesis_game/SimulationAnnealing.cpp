#include "SimulationAnnealing.h"



SimulationAnnealing::SimulationAnnealing(PersonalData* _samples){
	T = 999999999999;
	v = 1;
	error = 0;
	personalData = _samples;

}


SimulationAnnealing::~SimulationAnnealing(){

}




//SA看的是energy=>定義為similarity
float SimulationAnnealing::energy(GameParameter *p, std::vector<ScoreData*> s){
	Statistic ss;
	vector<GameState*> states = personalData->getState(s);
	ss.calculateComplexity(p, states);
	GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, states);

	return ss.similarityOfRank(states, s);//電腦排的跟人排的不同
}