#include "PersonalData.h"



bool ascentDifficulty(ScoreData* s1, ScoreData* s2){

	return  s1->difficulty < s2->difficulty;
}
bool ascentReDifficulty(ScoreData* s1, ScoreData* s2){
	return   s1->rescoredDifficulty < s2->rescoredDifficulty;
}



vector<ScoreData*> PersonalData::sortbyDifficulty(int sortMode, std::vector<ScoreData*> s){

	
	switch(sortMode){
		case DIFFICULTY:
			sort(s.begin(), s.end(), ascentDifficulty); 
			break;
		case RESCORED_DIFFICULTY:
			sort(s.begin(), s.end(), ascentReDifficulty); 
			break;
	}



	float score = - 1;
	for(int i = 0; i < s.size(); i++){
		if(score < s[i]->difficulty){
			s[i]->rank = i;
			score = s[i]->difficulty;
		}else{
			s[i]->rank = s[i - 1]->rank;
		}
	}
	return s;
}

