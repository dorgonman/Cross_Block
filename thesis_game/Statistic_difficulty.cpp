#include "Statistic.h"

/*
vector<GameState*> Statistic::meanAndvariance(int filter, PersonalData *personalData){

	 vector<GameState*> m = mean(filter, personalData);


	for(int i = 0; i < personalData->datas.size(); i++){
		vector<ScoreData*> scoreDatas = personalData->datas[i];

		switch(filter){
			case DIFFICULTY:
				for(int j = 0; j < scoreDatas.size(); j++){//�C�ӤH������j���d���ơA�n�`�N���O�A�o�̪��ƧǤ�����
					ScoreData* scoreData = scoreDatas[j];
					GameState* state = personalData->puzzleDB->states[j];
					state->difficultyVariance = state->difficultyVariance + 
						                        (scoreData->difficulty - m[j]->difficulty) *  
												(scoreData->difficulty - m[j]->difficulty);

				}
			break;
			case RESCORED_DIFFICULTY:
				for(int j = 0; j < scoreDatas.size(); j++){//�C�ӤH�������d���ơA�n�`�N���O�A�o�̪��ƧǤ�����
					ScoreData* scoreData = scoreDatas[j];
					GameState* state = personalData->puzzleDB->states[j];
					//state->rescoredDifficultyVariance +=  (scoreData->rescoredDifficulty - m[j]) * (scoreData->rescoredDifficulty - m[j]);
				}
				break;
		}

	}
	for(int i = 0; i < personalData->puzzleDB->states.size(); i++){
		GameState* state = personalData->puzzleDB->states[i];
		switch(filter){
			case DIFFICULTY:
				state->difficultyVariance = state->difficultyVariance / (personalData->puzzleDB->states.size() - 1) ; //����
					state->difficulty = m[i]->difficulty;
			break;
			case RESCORED_DIFFICULTY:
				//state->rescoredDifficultyVariance = state->rescoredDifficultyVariance / (personalData->puzzleDB->states.size() - 1) ; //����
				state->rescoredDifficulty = m[i]->rescoredDifficulty;
			break;
		}
	

	}

	return personalData->puzzleDB->states;//�^�Ǥ@�պ�n���ץ�����puzzle

}


vector<GameState*> Statistic::mean(int filter, PersonalData* personalData){


	for(int i = 0; i < personalData->datas.size(); i++){
		vector<ScoreData*> scoreDatas = personalData->datas[i];

		switch(filter){
			case DIFFICULTY:
				for(int j = 0; j < scoreDatas.size(); j++){//�C�ӤH�������d���ơA�n�`�N���O�A�o�̪��ƧǤ�����
					ScoreData* scoreData = scoreDatas[j];
					personalData->puzzleDB->states[j]->difficulty += scoreData->difficulty;

				}
			break;
			case RESCORED_DIFFICULTY:
				for(int j = 0; j < scoreDatas.size(); j++){//�C�ӤH�������d���ơA�n�`�N���O�A�o�̪��ƧǤ�����
					ScoreData* scoreData = scoreDatas[j];
					personalData->puzzleDB->states[j]->rescoredDifficulty += scoreData->rescoredDifficulty;

				}
				break;
		}

	}
	for(int i = 0; i < personalData->puzzleDB->states.size(); i++){
		GameState* state = personalData->puzzleDB->states[i];
		state->difficulty = state->difficulty / personalData->puzzleDB->states.size(); //����
	}

	return personalData->puzzleDB->states;//�^�Ǥ@�պ�n���ץ�����puzzle
}*/