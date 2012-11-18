#include "PersonalData.h"


PersonalData::PersonalData(std::string _dbFilePath){
	dbFilePath = _dbFilePath;
	puzzleDB = new GameDB(10, 10);
	puzzleDB->loadGames(dbFilePath);
	currentDirectory();
}





vector<GameState*> PersonalData::getState(vector<ScoreData*> scoreDatas){
	vector<GameState*> result;
	for(int i = 0 ; i < scoreDatas.size(); i++){
		result.push_back(scoreDatas[i]->state);
	}
	return result;
}