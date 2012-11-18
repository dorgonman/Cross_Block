#include "PersonalData.h"





void PersonalData::printAllScore(){

	for(vector<vector<ScoreData*>>::iterator it = datas.begin(); it != datas.end(); it++ ){
		vector<ScoreData*> scoreDatas = *it;
		printScore(scoreDatas);
		
	}

}

void PersonalData::printScore(vector<ScoreData*> scoreDatas){
		cout << "file:"<< scoreDatas[0]->filePath << endl;
		int i = 0;
		cout << "LV" << "   "  << "id" << "    "  << "rank" << "   " <<  "difficulty" << "   " << "rescore difficulty" << endl;
		for(vector<ScoreData*>::iterator it2 = scoreDatas.begin(); it2 != scoreDatas.end(); it2++ ){
			ScoreData* scoreData = *it2;
			cout << "LV" << i << "   "  << scoreData->state->id << "   " <<  scoreData->rank << "   " << scoreData->difficulty << "   " << scoreData->rescoredDifficulty << endl;
			i++;
		}
		cout << endl;
}

void PersonalData::loadScore(char* folderPath, char* fileType){

	vector<string> files = getAllFile(folderPath, fileType);//����Ҧ��������ɸ��|
	for(vector<string>::iterator it = files.begin(); it != files.end(); it++ ){
	string filePath =  *it;
	vector<ScoreData*> scoreDatas;
	
		
	ifstream fin(filePath.c_str(), ios::in);
	if(!fin){//Ū�ɥ���
		cout << "fail to loading score files"<<endl; 
		return;
	}  
	
		//cout << "loading file:" << filePath << ", please waiting"  << endl;

		while(!fin.eof()){
			string tmpStr;
			getline(fin,tmpStr);
			if(tmpStr == "[score]"){
				int i = 0;
				while(true){
				
					getline(fin,tmpStr); 
					//cout << tmpStr << endl;
					if(tmpStr == "[/score]"){
						break;
					}
				
					char* token = strtok((char*)tmpStr.c_str()," \t");
					int id =  atoi(strtok(NULL," \t"));
					if(id >= puzzleDB->states.size()){
						cout << "error:id > db size, please check:" << filePath << endl;
					}
				
					ScoreData* score = new ScoreData(puzzleDB->states[id]);
					score->filePath = filePath;
					scoreDatas.push_back(score);

					score->difficulty = atof(strtok(NULL," \t"));
					score->rescoredDifficulty = atof(strtok(NULL," \t"));
					i++;
				}
			}
		}
		datas.push_back(scoreDatas);//�n�̭��맹�ȦA��i�h=>�]���Ocopy�@����i�h�A�ҥH������Ȫ��ܡA�~���������|�v�T�̭���(���O����) 
		fin.close();
	}
		
}