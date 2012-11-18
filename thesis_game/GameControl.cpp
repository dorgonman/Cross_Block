#include "GameControl.h"

//設定讀取檔案為當前的目錄
#include "windows.h"
#include <shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")


extern HGE* hge;

GameControl::GameControl(){
	rm = new hgeResourceManager();
	squareSpr = new hgeSprite(rm->GetTexture("square.png"), 0, 0, SQUARE, SQUARE);
	stateIndex = 0;
	//board.resize(5, vector<bool>(5));
	hge->Random_Seed();//3
	//file.open("..\\data\\db.dat",ios::out|ios::trunc);
	currentState = NULL;

	//設定檔案為當前的目錄
	const int nBufSize = 512;
    wchar_t chBuf[nBufSize];
    ZeroMemory(chBuf,nBufSize);
    GetModuleFileNameW(NULL,chBuf,nBufSize);
    LPWSTR lpStrPath = chBuf;
    PathRemoveFileSpecW(lpStrPath);
	SetCurrentDirectoryW(lpStrPath);
}


GameControl::~GameControl(){
	file.close();

	delete instance;

}


GameControl* GameControl::instance = NULL;

GameControl* GameControl::getInstance(){
	if(instance == NULL){
		instance = new GameControl();
	}
	return instance;
}



void GameControl::render(){
  for(int y = 1; y !=  currentState->board.size(); ++y) {
    for(int x = 1; x != currentState->board[0].size(); ++x) {
		if(currentState->board[y][x]){//有子
			squareSpr->Render(x * SQUARE, y * SQUARE);
		}
    }
  }

}





void GameControl::printTwoDimDynamicArray(){
	printTwoDimDynamicArray(currentState->board);
}



void GameControl::printTwoDimDynamicArray(std::vector<vector<int> > arr){
  for(int y = 0; y !=  arr.size(); ++y) {
		for(int x = 0; x != arr[0].size(); ++x) {
		  cout << (int)arr[y][x] << "     ";
		}
		cout << endl;
  }


  cout << endl;

}

void GameControl::printSolvedSequence(){

	for(int j = 0; j < currentState->solvedSequence.size(); j++){
		for(int i = 0; i < currentState->solvedSequence[j].size(); i++){
			cout << "(" << currentState->solvedSequence[j][i].x << "," << currentState->solvedSequence[j][i].y << ")";
		}
		cout << endl;
	}

	for(vector<vector<Grid>>::iterator it = currentState->solvedSequence.begin(); it != currentState->solvedSequence.end(); it++){

	}
}


bool GameControl::isDead(){
	return currentState->isDead();
}



void GameControl::printComplexity(vector<GameState*> states){
		int i = 0;
		cout << "LV" << "   "  << "id" << "    "  << "rank" << "   " <<  "complexity" << endl;
		for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++ ){
			GameState* state = *it;
			cout << "LV" << i << "   "  << state->id << "   " <<  state->rank << "   " << state->complexity << endl;
			i++;
		}
		cout << endl;
}