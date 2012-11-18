#include "GameDB.h"



bool GameDB::loadGames(string filePath){
	ifstream fin(filePath.c_str(), ios::in);
	if(!fin){    // �ˬdŪ�ɦ��\�P�_ 
		return false;
	}  

	cout << "loading file:" << filePath << ", please waiting"  << endl;

	GameState* newState;

	while(!fin.eof()){
		string tmpStr;

		//fin>> s ;
		getline(fin,tmpStr); 
		//cout << tmpStr << endl;

		if(tmpStr == "[cross number]" || tmpStr == "[cross out]"){  //�e��������r�K�K
			int crossOut = 0;
			int sizex = 0;
			int sizey = 0;
			fin >> crossOut;  fin >> tmpStr;   fin >> sizex;  fin >> tmpStr;  fin >> sizey;

			newState = new GameState(sizex, sizey);
			newState->crossOut = crossOut;
			
			newState->solvedSequence.resize(0);
			states.push_back(newState);
			//cout << "crossOut:" << newState->crossOut << endl;
			//cout << "sizex, sizey:" << newState->sizex << newState->sizey << endl;
		}


		//����sequence
		int j = 0;//�ثe�O�ĴX�B��
		if(tmpStr == "[game state]"){
			while(true){
				  getline(fin,tmpStr);
				
				  if(tmpStr == "[solved step]"){//Ū��o��tag ��ܤl�w�g��Ū��
					  fin >> newState->solvedStep;
					  break;
				  }else{
					  newState->solvedSequence.resize(newState->solvedSequence.size() + 1);//�[���@��(�@�B��)
				  }
				  int mode = 0;//x, y
				  int x = 0;//mode 0
				  int y = 0;// mode 1
				  char* token = strtok((char*)tmpStr.c_str(),"(,)");
			
				  while (token != NULL){//�N�Ӧ�Ū������
					  // printf("The token is:  %d\n", atoi(token));
					   if(mode == 0){
						   x = atoi(token);
					   }
					   if(mode == 1){
			
	
						   y = atoi(token);
						   newState->solvedSequence[j].push_back(Grid(x, y));
						   newState->board[y][x] = true;//��l
					   }
					   mode = (mode + 1) % 2;
					   token = strtok(NULL,"(,)");
				   } 
				   j++;
			
		
			}


		}


		if(tmpStr == "[nBranch]"){
			fin >> newState->nBranch;
		}
		if(tmpStr == "[nLiveRoad]"){
			fin >> newState->nLiveRoad;
		}

		if(tmpStr == "[nDeadEnd]"){
			fin >> newState->nDeadEnd;
		}

		if(tmpStr == "[nNode]"){
			fin >> newState->nNode;
		
		}
		if(tmpStr == "[nbacktrace]"){
			fin >> newState->nbacktrace;
		}

		if(tmpStr == "[complexity]"){
			fin >> newState->complexity;
		}
		if(tmpStr == "[id]"){
			fin >> newState->id;
		}
	}
	fin.close();   // �����ɮ�
	return true;
}


void GameDB::saveGames(string filePath){
	saveGames(filePath, states);
}
void GameDB::saveGames(string filePath, vector<GameState*> s){
	ofstream fout(filePath.c_str(), ios::out|ios::trunc);
	for(vector<GameState*>::iterator it = s.begin(); it != s.end(); it++){
		GameState* state = *it;
		fout << "[cross out]" << endl;
		fout <<  state->crossOut <<  endl;

		fout << "[sizex]" << endl;
		fout <<  state->sizex <<  endl;

		fout << "[sizey]" << endl;
		fout <<  state->sizey <<  endl;

		fout << "[game state]" << endl;

		for(int j = 0; j < state->solvedStep ;j++){
			for(int i = 0; i < state->crossOut; i++){
				fout << "(" << state->solvedSequence[j][i].x << "," << state->solvedSequence[j][i].y << ")";
			}
			fout << endl;
		}
		
		fout << "[solved step]" << endl;
		fout << state->solvedStep << endl;

		fout << "[nDeadEnd]" << endl;
		fout << state->nDeadEnd << endl;

		fout << "[nBranch]" << endl;
		fout << state->nBranch << endl;

		fout << "[complexity]" << endl;
		fout << state->complexity << endl;
		
		fout << "[id]" << endl;
		fout << state->id << endl;
	}

	fout.close();


}




