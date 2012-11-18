#include "SimulationAnnealing.h"

//a�O�ײv�Ab�O�첾
float SimulationAnnealing::sigmoid(float x, float a = 1, float b = 0){
	float e = 2.71828182845904523536f;
	float f = 1 / (1 + pow(e, -a * x  + b));
	return f;
}

//mapping from time to "temperature"=>temperature decrese function
float SimulationAnnealing::schedule(float t){
    float alpha = 0.95;//�ū׭��C�t��
    float Tmax = 600;//��l�ū�

	return Tmax * pow(alpha,t-1);
}




//�i���Ҩ��
float SimulationAnnealing::Boltzman(float deltaE, float Tk){
	float e = 2.71828182845904523536f;
	return min(1, pow(e, -deltaE / Tk));
}

