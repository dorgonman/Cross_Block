#include "hge.h"
#include <string>
#include "vector"
#include "math.h"
#include "GameParameter.h"
#include "iostream"
#include "PersonalData.h"
#include "Statistic.h"
#include "GameControl.h"
using namespace std;


#ifndef SIMULATIONANNEALING
#define SIMULATIONANNEALING

class SimulationAnnealing{
public:
	SimulationAnnealing(PersonalData* _samples);
	~SimulationAnnealing();


	void begin(GameParameter* p);
private:
	float sigmoid(float x, float a, float b);
	float schedule(float t);
	float Boltzman(float deltaE, float Tk);
	float energy(GameParameter* p, vector<ScoreData*> sample);
	bool isAccept(GameParameter* oldP, GameParameter* newP);
private:
	float error;//該iteration的total difficulty error
	float T; //目前的溫度，從最高開始降低
	float v;//毎次調整時的亂數間隔(-v, v)


	GameParameter* parameter;
	PersonalData* personalData;//samples


};


#endif