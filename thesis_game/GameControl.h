#include "GameState.h"
#include "hgeresource.h"
#include "hge.h"
#include "hgegui.h"
#include "hgefont.h"
#include "hgeguictrls.h"
#include "SearchTree.h"
#ifndef GAME_CONTROL
#define GAME_CONTROL

#define SQUARE 50//������j�p



class GameControl{
private:
	GameControl();
	~GameControl();
public:
	static GameControl* getInstance();

public:
	//�S���ǤJstate���ܡA�N�N��ϥ�currentState�Ӷi��ާ@
	bool isGoal();//�ˬdstate�ѽL�W������O�_�w���������A�O���ܴN�OĹ
	bool isDead();
	bool isDead(GameState* state);
public:
	bool operation(Grid g1, Grid g2);
	bool operation(GameState* state, Grid g1, Grid g2);//�������
public:
	void setGameBoard(GameState* state);
	
public:
	void render();
	void setStateIndex(int index);
	int getStateIndex();
	GameState* getCurrentState();
	void printTwoDimDynamicArray();
	void printTwoDimDynamicArray(vector<vector<int>> board);
	void printSolvedSequence();
	void printComplexity(vector<GameState*> states);

public:
	vector<GameState*> sortbyComplexity(int sortMode);
	vector<GameState*> sortbyComplexity(int sortMode, vector<GameState*> s);
	vector<GameState*> sortbyDifficulty(int sortMode, vector<GameState*> s);
	vector<GameState*> sortSolvedSequence();
	vector<GameState*> sortbySolvedStep(int sortMode);
	enum eSort{//�n�ƧǪ��覡
		ASCENT = 0,
		DESCENT = 1,
	};
private:
	bool isValidOperation(GameState* state, Grid& g1, Grid& g2);//g1��grid���_�I�Ag2��grid�����I
	void generalizeOperation(Grid& g1, Grid& g2);//�N�ƭ��`�X������operation�վ㶶�Ǥ@�U(�����Og1�A�C���Og2)

public:
		hgeResourceManager* rm;
		hgeSprite* squareSpr;
		vector<GameState*> states;
		GameState* currentState;
		int stateIndex;
		//vector<vector<int>> board;//�ѽL�A����K�{���B�z�A0��0�C���ϥ�
		ofstream file;

private:
	static GameControl* instance;

	//GameState* currentState;;

	




};

#endif
