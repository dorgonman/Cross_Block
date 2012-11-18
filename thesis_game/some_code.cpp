
	/*PersonalData* personalData = new PersonalData(".\\data\\gameboard10\\db_release10_phaseA.dat");
	char folderPath[] = ".\\statistic\\"; // 指定工作路經（可以是相對路經）
	char fileType[] = "*.txt"; // 指定目標檔案格式
	personalData->loadScore(folderPath, fileType);
	
	//personalData->printAllScore();

	
	//db->buildDatabase(100, 40, 13);
	//db->loadGames(".\\data\\gameboard10\\db_release10_phaseB.dat");
	GameDB* db10 = new GameDB(10, 10);
	db10->loadGames(".\\data\\gameboard10\\db_release10_phaseB.dat"); //complexity各是多少？
	GameDB* dbA = new GameDB(10, 10);
	dbA->loadGames(".\\data\\gameboard10\\db_release10_phaseA.dat"); //complexity各是多少？

	Statistic ss;
	vector<GameState*> scoredPuzzle = ss.meanAndvariance(Statistic::DIFFICULTY, personalData);
	vector<GameState*> sortedScorePuzzle = GameControl::getInstance()->sortbyDifficulty(GameControl::ASCENT, scoredPuzzle);//排序好難度的



	
	
	//db10->states = GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, dbtemp->getStates(GameDB::COMPLEXITY_ABOVE, 0));
	db = new GameDB(10, 10);
	db->loadGames(".\\data\\gameboard10\\db_ALL_GAME_remove_same.dat");
	
	vector<GameState*> base = db->pickStates(db->states, personalData->puzzleDB->states);//db->getStates(GameDB::COMPLEXITY_ABOVE, 0);
	GameControl::getInstance()->states = db->getStates(GameDB::COMPLEXITY_ABOVE, 0);//db->getStates(s, GameDB::COMPLEXITY_BELOW, 0.25);


	ofstream out(".\\data\\gameboard10\\complexity_base_release10.txt", ios::out|ios::trunc);
	out << "Small base" << endl;
	out << "P     Complexity  Rank" << endl;
	//ss.calculateComplexity(db10->states);//重排時要重計算
	for(int i = 0; i < 10; i++){
		GameState* state = dbA->states[i];
		for(int j = 0; j < 10; j++){
			GameState* state2 = db10->states[j];
			if(state->isSame(state2)){
				out << "P" << i << "   " << db10->states[j]->complexity << "    " << j  << endl;
			}
		}
	}

	out << "Large base" << endl;
	out << "P     Complexity Rank" << endl;
	//ss.calculateComplexity(db10->states);//重排時要重計算
	for(int i = 0; i < 10; i++){
		GameState* state = dbA->states[i];
		for(int j = 0; j < 10; j++){
			GameState* state2 = base[j];
			if(state->isSame(state2)){
				out << "P" << i << "   " << base[j]->complexity << "    " << j << endl;
			}
		}
	}

	out << "P Human_Sorting Rank" << endl;
	for(int i = 0; i < 10; i++){
		GameState* state = scoredPuzzle[i];
		for(int j = 0; j < 10; j++){
			GameState* state2 =  sortedScorePuzzle[j];
			if(state->isSame(state2)){
				out << "LV" << i << "   " << sortedScorePuzzle[j]->difficulty << "    " << j << endl;
			}
		}
	}
	out.close();

	cout << "match:" << ss.matchOfRank(base, sortedScorePuzzle) << endl;//base不同的差別
	cout << "similarity:" << ss.similarityOfRank(base, sortedScorePuzzle) << endl;//base不同的差別

	ofstream fout(".\\data\\gameboard10\\Difficulty_Analysis_release10.txt", ios::out|ios::trunc);
	fout << "difficulty        variance" << endl;

	for(int i = 0; i < scoredPuzzle.size(); i ++){
		fout << scoredPuzzle[i]->difficulty / 100 << "   " <<  scoredPuzzle[i]->difficultyVariance / 100 << endl;
	}
	fout.close();
	


	//db->loadGames(".\\data\\gameboard10\\db_test.dat");


	//db->states = db->removeSamePuzzle(db->states);

	//db->saveGames(".\\data\\gameboard10\\db_ALL_GAME_remove_same.dat", db->states);

	

	//SearchTree st;
	//st.calculateBranchAndDeadEnds(db->getStates(GameDB::ALL, 2));

	//cout << "size = " << db->getStates(GameDB::ALL, 11).size() << endl;

	//db->sortbySolvedStep(GameDB::ASCENT);

	//Statistic ss;
	//ss.calculateComplexity(db->states);//重排時要重計算

	//db->states = GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, db->getStates(GameDB::COMPLEXITY_ABOVE, 0)); 
	
	//vector<GameState*> s = db->getStates(GameDB::COMPLEXITY_ABOVE, 0);
	

	//GameState* state = new GameState(10, 10);

	//for(int i = 1; i < 11; i++){
		//for(int j = 1; j < 11; j++){
			//state->board.at(i).at(j) = 1;
		//}
	//}
	//state->solvedStep = 50;
	//GameControl::getInstance()->states.push_back(state);
	//GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT);
	//db->saveGames(".\\data\\gameboard10\\db_ALL_GAME.dat", GameControl::getInstance()->states);
	//GameControl::getInstance()->states = db->states;
	//GameControl::getInstance()->states = db->getStates(GameDB::ALL, 2);
	//GameControl::getInstance()->states = db->getStates(GameDB::STEP_EQUAL,2);
*/

/*
		vector<GameState*> veryEasyStates = db->getStates(db->states, db->COMPLEXITY_BELOW, 0.125);

	
	vector<GameState*> easyStates = db->getStates(db->states, db->COMPLEXITY_ABOVE, 0.125);
	easyStates = db->getStates(easyStates, db->COMPLEXITY_BELOW, 0.25);


	vector<GameState*> normalStates = db->getStates(db->states, db->COMPLEXITY_ABOVE, 0.25);
	normalStates = db->getStates(normalStates, db->COMPLEXITY_BELOW, 0.5);

	vector<GameState*> hardStates = db->getStates(db->states, db->COMPLEXITY_ABOVE, 0.5);
	hardStates = db->getStates(hardStates, db->COMPLEXITY_BELOW, 0.75);

	vector<GameState*> veryHardStates = db->getStates(db->states, db->COMPLEXITY_ABOVE, 0.75);
	veryHardStates = db->getStates(veryHardStates, db->COMPLEXITY_BELOW, 1.0);

	db->saveGames(".\\data\\gameboard10\\db_e2_Easy.dat", veryEasyStates);
	db->saveGames(".\\data\\gameboard10\\db_e2_Easy.dat", easyStates);
	db->saveGames(".\\data\\gameboard10\\db_e2_Normal.dat", normalStates);
	db->saveGames(".\\data\\gameboard10\\db_e2_Hard.dat", hardStates);
	db->saveGames(".\\data\\gameboard10\\db_e2_VeryHard.dat", veryHardStates);*/


/*
	GameDB* easyDB = new GameDB();
	easyDB->loadGames(".\\data\\gameboard10\\db_e2_Easy.dat");

	GameDB* normalDB = new GameDB();
	normalDB->loadGames(".\\data\\gameboard10\\db_e2_Normal.dat");

	GameDB* hardDB = new GameDB();
	hardDB->loadGames(".\\data\\gameboard10\\db_e2_Hard.dat");

	GameDB* veryHardDB = new GameDB();
	veryHardDB->loadGames(".\\data\\gameboard10\\db_e2_VeryHard.dat");


	vector<GameState*> pickEasyStates = easyDB->getRandomStates(7);
	vector<GameState*> pickNormalStates = normalDB->getRandomStates(7);
	vector<GameState*> pickHardStates = hardDB->getRandomStates(4);
	vector<GameState*> pickVeryHardStates = veryHardDB->getRandomStates(2);

	vector<GameState*> releaseStates = easyDB->merge(pickEasyStates, pickNormalStates);
	releaseStates = easyDB->merge(releaseStates, pickHardStates);
	releaseStates = easyDB->merge(releaseStates, pickVeryHardStates);

	easyDB->saveGames(".\\data\\gameboard10\\db_e2_release20.dat", releaseStates);




	
	GameDB* veryEasyDB = new GameDB();
	veryEasyDB->loadGames(".\\data\\gameboard10\\db_e2_VeryEasy.dat");

	GameDB* easyDB = new GameDB();
	easyDB->loadGames(".\\data\\gameboard10\\db_e2_Easy.dat");

	GameDB* normalDB = new GameDB();
	normalDB->loadGames(".\\data\\gameboard10\\db_e2_Normal.dat");

	GameDB* hardDB = new GameDB();
	hardDB->loadGames(".\\data\\gameboard10\\db_e2_Hard.dat");

	GameDB* veryHardDB = new GameDB();
	veryHardDB->loadGames(".\\data\\gameboard10\\db_e2_VeryHard.dat");

	vector<GameState*> pickVeryEasyStates = veryEasyDB->getRandomStates(2);
	vector<GameState*> pickEasyStates = easyDB->getRandomStates(5);
	vector<GameState*> pickNormalStates = normalDB->getRandomStates(10);
	vector<GameState*> pickHardStates = hardDB->getRandomStates(5);
	vector<GameState*> pickVeryHardStates = veryHardDB->getRandomStates(2);

	vector<GameState*> releaseStates = easyDB->merge(pickVeryEasyStates, pickEasyStates);
	releaseStates = easyDB->merge(releaseStates, pickNormalStates);
	releaseStates = easyDB->merge(releaseStates, pickHardStates);
	releaseStates = easyDB->merge(releaseStates, pickVeryHardStates);

	releaseStates = GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, releaseStates);

	easyDB->saveGames(".\\data\\gameboard10\\db_e2_release20.dat", releaseStates);
*/