#include "GameDB.h"
#include "GameControl.h"
#include "GameState.h"

GameDB::GameDB(int _sizex, int _sizey){
//	db.reset();
	/*dbSize = _dbSize;
	cout << "create support database size = " << dbSize << ", please waiting" << endl;
	  LARGE_INTEGER m_liPerfFreq={0};
    QueryPerformanceFrequency(&m_liPerfFreq); 
     
    LARGE_INTEGER m_liPerfStart={0};
    QueryPerformanceCounter(&m_liPerfStart);


	buildSupportDatabase();
	LARGE_INTEGER liPerfNow={0};
    QueryPerformanceCounter(&liPerfNow);

    int time=( ((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)/m_liPerfFreq.QuadPart);

    cout<<"執行時間:"<<time<< "ms"<<endl;*/
	sizex = _sizex;
	sizey = _sizey;
	nGame = 1;
	maxStep = 10;
}

GameDB::~GameDB(){
	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
		GameState* state = *it;
		delete state;
	}


}



void GameDB::buildAllDatabase(int _nGame, int _maxStep){

	int maxSize = max(sizex, sizey);
	nGame = _nGame;
	maxStep = _maxStep;
	for(int crossOut = 2; crossOut < maxSize; crossOut++){
		cout << "generate crossOut:" << crossOut << endl;
		//buildDatabase(crossOut, (sizex*sizey) / crossOut);
		buildDatabase(nGame, maxStep, crossOut);
	}




	


}

void GameDB::buildDatabase(int nGame, int maxStep, int crossOut){

	for(int step = 2; step <= maxStep; step++){
		for(int i = 0; i < nGame ; i++){
			GameState* state = new GameState(sizex, sizey);
			state->randomGenerate(crossOut, step);
			states.push_back(state);
		}
	}
}






//http://www.computing.dcu.ie/~humphrys/Notes/Neural/sigmoid.html

//a是斜率，b是位移
float GameDB::sigmoid(float x, float a = 1, float b = 0){
	float E = 2.71828182845904523536f;
	float f = 1 / (1 + pow(E, -a * x  + b));
	return f;
}


//貝式定理=>以因導果不好求，轉成以果導因=>利用Gaussian分佈來求pdf
float GameDB::Gaussian1D(float x, float mean, float std){
	float E = 2.71828182845904523536;
	float PI = 3.14159;

	//用train的
	float pdf = pow(E, (-1 / (2 * pow(std, 2))) * pow(x - mean, 2));

	return pdf;
}



vector<GameState*> GameDB::removeSamePuzzle(std::vector<GameState*> s){

	vector<GameState*> result;
	for(int i = 0; i < s.size(); i++){
		GameState* state = s[i];
		int bRepeat = false; //這個repeat了幾次，有重覆就要移除

		for(vector<GameState*>::iterator it = result.begin(); it != result.end(); it++){
			GameState* state2 = *it;
			if(state->isSame(state2)){
				bRepeat = true;
			}
		}
		if(!bRepeat){
			result.push_back(state);
		}
	}

	return result;
}