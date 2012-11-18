#include "SimulationAnnealing.h"

//a是斜率，b是位移
float SimulationAnnealing::sigmoid(float x, float a = 1, float b = 0){
	float e = 2.71828182845904523536f;
	float f = 1 / (1 + pow(e, -a * x  + b));
	return f;
}

//mapping from time to "temperature"=>temperature decrese function
float SimulationAnnealing::schedule(float t){
    float alpha = 0.95;//溫度降低速度
    float Tmax = 600;//初始溫度

	return Tmax * pow(alpha,t-1);
}




//波茲曼函數
float SimulationAnnealing::Boltzman(float deltaE, float Tk){
	float e = 2.71828182845904523536f;
	return min(1, pow(e, -deltaE / Tk));
}

