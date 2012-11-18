#include "GameControl.h"
#include "GameDB.h"
#include "SearchTree.h" 
#include "Statistic.h"
#include <shlwapi.h> 
#include "PersonalData.h"
#include "SimulationAnnealing.h"
#pragma comment(lib, "shlwapi.lib")

bool FrameFunc();
void redirectIOToConsole();
void winCondition();

HGE *hge = 0;
hgeGUI* gui;
hgeFont* fnt;
hgeSprite* boardSpr;

float timePast = 0;

bool bstart = false;
bool bdeath = false;
bool FrameFunc();
void winCondition();
void startGame();
void GUIFunction();
void render();
void loadResource();
void autoGenerateGames();
vector<string> getAllFile(char* fileType, char* workPath);
void currentDirectory();


//先做base只有10個的比較，再做base大一點的


//層次
void experimentWorkSpace(){

	//A是產生完 B是計算完branch and dead ends
	//phase A
	GameControl* gameControl = GameControl::getInstance();

	//gameControl->file.open(".\\data\\gameboard20\\db_13.dat");//設定自動產生的關卡要存在哪邊
	//db_release = new GameDB(10, 10);
	//db_release->loadGames(".\\data\\gameboard10\\db_release10_phaseA.dat");
	//loadScore();
	/*GameDB* db = new GameDB(10, 10);
	db->loadGames(".\\data\\gameboard10\\db_release10_phaseB.dat");



	PersonalData* personalData = new PersonalData(".\\data\\gameboard10\\db_ALL_GAME_remove_same.dat");

	personalData->loadScore(".\\statistic\\");
	//personalData->printAllScore();

	Statistic ss;

	for(int i = 0; i < personalData->datas.size(); i ++){
		vector<ScoreData*> sortedScore = 
			personalData->sortbyDifficulty(PersonalData::DIFFICULTY, 
			                               personalData->datas[i]);
		vector<GameState*> complexState = GameControl::getInstance()->
			                              sortbyComplexity(GameControl::ASCENT, 
			                              personalData->getState(sortedScore));


	}*/

	//SimulationAnnealing sa(personalData);
	//GameParameter* p = new GameParameter(1);
	//sa.begin(p);
	
	
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
	vector<GameState*> pickEasyStates = easyDB->getRandomStates(3);
	vector<GameState*> pickNormalStates = normalDB->getRandomStates(3);
	vector<GameState*> pickHardStates = hardDB->getRandomStates(1);
	vector<GameState*> pickVeryHardStates = veryHardDB->getRandomStates(1);

	vector<GameState*> releaseStates = easyDB->merge(pickVeryEasyStates, pickEasyStates);
	releaseStates = easyDB->merge(releaseStates, pickNormalStates);
	releaseStates = easyDB->merge(releaseStates, pickHardStates);
	releaseStates = easyDB->merge(releaseStates, pickVeryHardStates);

	releaseStates = GameControl::getInstance()->sortbyComplexity(GameControl::ASCENT, releaseStates);

	easyDB->saveGames(".\\data\\gameboard10\\db_e2_release_random10.dat", releaseStates);

	Statistic ss;
	cout << ss.mean(Statistic::BRANCH, veryEasyDB->states) << endl;
	cout << ss.mean(Statistic::BRANCH, easyDB->states) << endl;
	cout << ss.mean(Statistic::BRANCH, normalDB->states) << endl;
	cout << ss.mean(Statistic::BRANCH, hardDB->states) << endl;
	cout << ss.mean(Statistic::BRANCH, veryHardDB->states) << endl;


	cout << "==============" << endl;
	cout << ss.mean(Statistic::DEADEND, veryEasyDB->states) << endl;
	cout << ss.mean(Statistic::DEADEND, easyDB->states) << endl;
	cout << ss.mean(Statistic::DEADEND, normalDB->states) << endl;
	cout << ss.mean(Statistic::DEADEND, hardDB->states) << endl;
	cout << ss.mean(Statistic::DEADEND, veryHardDB->states) << endl;
	cout << "==============" << endl;

	cout << ss.mean(Statistic::COMPLEXITY, veryEasyDB->states) << endl;
	cout << ss.mean(Statistic::COMPLEXITY, easyDB->states) << endl;
	cout << ss.mean(Statistic::COMPLEXITY, normalDB->states) << endl;
	cout << ss.mean(Statistic::COMPLEXITY, hardDB->states) << endl;
	cout << ss.mean(Statistic::COMPLEXITY, veryHardDB->states) << endl;

	//vector<GameState*> states = db->pickStates(personalData->puzzleDB->states, db->states);
	GameControl::getInstance()->states = veryEasyDB->states;
	gameControl->setStateIndex(0);
	//GameControl::getInstance()->sortSolvedSequence();
	//db->saveGames(".\\data\\gameboard10\\db_ALL_GAME_remove_same.dat", db->states);
	//system("pause");

}
         

void loadResource(){
	GameControl* gameControl = GameControl::getInstance();
	experimentWorkSpace();

	gui = new hgeGUI();
	HTEXTURE tex = GameControl::getInstance()->rm->GetTexture("cursor.png");
	hgeSprite* cursorSpr = new hgeSprite(tex, 0, 0, 32, 32);
	cursorSpr->SetHotSpot(0, 0);
	gui->SetCursor(cursorSpr);
	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->Enter();

	
	gui->AddCtrl(new hgeGUIButton(1, 0, 0, 53, 53,  gameControl->rm->GetTexture("buttonReset.png"), 50, 50));
	gui->AddCtrl(new hgeGUIButton(2,40, 0, 53, 53,  gameControl->rm->GetTexture("buttonOK.png"), 50, 50));
	gui->AddCtrl(new hgeGUIButton(3,80, 0, 53, 53,  gameControl->rm->GetTexture("buttonPrev.png"), 50, 50));
	gui->AddCtrl(new hgeGUIButton(4,120, 0, 53, 53,  gameControl->rm->GetTexture("buttonNext.png"), 50, 50));
	//gui->AddCtrl(new hgeGUISlider(5, 250, 20, 300, 25, gameControl->rm->GetTexture("slider.png"), 0, 0, 50, 50));
//
	//hgeGUISlider* gg = (hgeGUISlider*)gui->GetCtrl(5);
	//gg->SetMode(0, GameControl::getInstance()->states.size() - 1, HGESLIDER_BAR);

	fnt = new hgeFont("font1.fnt");
	fnt->SetScale(0.7f);
	fnt->SetColor(0xFFFF0000);
	boardSpr = new hgeSprite(gameControl->rm->GetTexture("GameBoard.jpg"), 0, 0, 600, 600);

	
}




bool FrameFunc(){

	if (hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}


	GUIFunction();

	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);


	render();

		

	hge->Gfx_EndScene();

	

	return false;
}
void release(){
	hge->System_Shutdown();
	hge->Release();
	delete gui;
	//delete db;
	delete boardSpr;


}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	redirectIOToConsole();

	hge = hgeCreate(HGE_VERSION);


	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);

	hge->System_SetState(HGE_TITLE, "Cross Block by Chang Ching-Chao");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_SCREENWIDTH, 600);
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_DONTSUSPEND, true);


	if(hge->System_Initiate()){
		loadResource();
		hge->System_Start();

	}else{	
		//MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}



	release();
	
//	system("pause");
	return 0;
}




void winCondition(){
	if(GameControl::getInstance()->isGoal()){
		int index = GameControl::getInstance()->getStateIndex() + 1;
		GameControl::getInstance()->setStateIndex(index);
		bstart = false;
		bdeath = false;
	}
	GameControl::getInstance()->isDead();
}

void startGame(){

	float x, y;
	hge->Input_GetMousePos(&x, &y);

	GameControl::getInstance()->render();


	if(bdeath){
		//fnt->printf(250, 30, 0, "dead road"); // bug 因為用的是state裡的board的緣故，將該功能移到game control裡做
	}

	//取得消除線的起點
	static int lineBeginx = 0;
	static int lineBeginy = 0;
	if(hge->Input_KeyDown(HGEK_LBUTTON)){
		lineBeginx = x;
		lineBeginy = y;
	}
			
	//畫出消除線
	if(hge->Input_GetKeyState(HGEK_LBUTTON)){
			float mousex = 0;
			float mousey = 0;
			hge->Input_GetMousePos(&mousex, &mousey);

			if(mousex > 0 && mousey > 0 && mousex < 600 && mousey < 600){

				hge->Gfx_RenderLine(lineBeginx, lineBeginy , x, y, 0xFFFF00000);
			}
	}

	if(hge->Input_KeyUp(HGEK_LBUTTON)){
		Grid g1;
		Grid g2;
		g1.x = lineBeginx / SQUARE;
		g1.y = lineBeginy / SQUARE;
		g2.x = x / SQUARE;
		g2.y = y / SQUARE;
		if(GameControl::getInstance()->operation(g1, g2)){
				cout << "cross out" << endl;
				if(GameControl::getInstance()->isDead()){
					bdeath = true;
				}
				//GameControl::getInstance()->printTwoDimDynamicArray();
		}

	}


	GameState* state = GameControl::getInstance()->getCurrentState();
	if(hge->Input_KeyDown(HGEK_Z)){
		int step = (state->solvedStep - (state->countBoard() / state->crossOut));
		Grid a1 = state->solvedSequence[step][0];
		Grid a2 = state->solvedSequence[step][state->crossOut - 1];
		
		if(GameControl::getInstance()->operation(a1, a2)){
			cout << "cross out " << endl;
		}
	}

	

	fnt->printf(350, 5, HGETEXT_LEFT, "cross out: %d", state->crossOut);
	fnt->printf(350, 25, HGETEXT_LEFT, "solvedStep: %d", state->solvedStep);
	//fnt->printf(150, 555, HGETEXT_LEFT, "nDeadEnd: %.2f", state->nDeadEnd );
	//fnt->printf(5, 555, HGETEXT_LEFT, "nBranch:%.2f", state->nBranch );
	//fnt->printf(5, 580, HGETEXT_LEFT, "complexity:%f", state->complexity);

	fnt->printf(170, 25, HGETEXT_LEFT, "id:%d", state->id);
	timePast += hge->Timer_GetDelta();


	
}


void GUIFunction(){
	
    int id = gui->Update(hge->Timer_GetDelta());

	hgeGUISlider* slide = (hgeGUISlider*)gui->GetCtrl(5);
			switch(id){
				case 1://reset
							GameControl::getInstance()->setStateIndex(GameControl::getInstance()->getStateIndex());
							GameControl::getInstance()->printTwoDimDynamicArray();
							GameControl::getInstance()->printSolvedSequence();
							bdeath = false;
							cout << endl;
				break;

					case 2://ok
						bstart = true;
						bdeath = false;
						gui->ShowCtrl(2, false);
						GameControl::getInstance()->printTwoDimDynamicArray();
						//GameControl::getInstance()->printSolvedSequence();
						timePast = 0;
					break;

					case 3://pre
							GameControl::getInstance()->setStateIndex(GameControl::getInstance()->getStateIndex() - 1);
							bdeath = false;	
							timePast = 0;
					break;

					case 4://next
							GameControl::getInstance()->setStateIndex(GameControl::getInstance()->getStateIndex() + 1);
							bdeath = false;
							timePast = 0;
						
					break;
					case 5:
						//int index = (int)slide->GetValue();
						//if(index < 0){index = 0;};
						//GameControl::getInstance()->setStateIndex(index);
						//bdeath = false;
					break;
				
			}
	//slide->SetValue(GameControl::getInstance()->getStateIndex());

}


void render(){

		boardSpr->Render(0, 0);

		winCondition();

		fnt->printf(170, 5, HGETEXT_LEFT, "level: %d / %d ", 
		GameControl::getInstance()->getStateIndex(),
		GameControl::getInstance()->states.size() - 1);
		fnt->printf(250, 25, HGETEXT_LEFT, "time: %.2f", timePast);


		if(bstart){
			startGame();
			
		}else{
			gui->ShowCtrl(2, true);
			int index = GameControl::getInstance()->getStateIndex();
			if(index == 0){
				fnt->printf(100, 200, HGETEXT_LEFT, "press ok to start level");

			}else{
			
				fnt->printf(100, 200, HGETEXT_LEFT, "you clear the level press ok to start next");
			}
		}


			
		int gx = 0;
		int gy = 0;
		float x, y;
		hge->Input_GetMousePos(&x, &y);
		gx = x / SQUARE;
		gy = y / SQUARE;
		//commonInfoSpr->Render(0, 0);
		fnt->printf(510, 15, HGETEXT_LEFT, "(%d, %d)", (int)x, (int)y);

		fnt->printf(510, 35, HGETEXT_LEFT, "(%d, %d)", (int)gx , (int)gy);


		
		gui->Render();


}



   



#include <iostream>
#include <io.h>
#include <fcntl.h>
void redirectIOToConsole(){
    // Allocate a console so we can output some useful information.
    AllocConsole();

    // Get the handle for STDOUT's file system.
    HANDLE stdOutputHandle = GetStdHandle( STD_OUTPUT_HANDLE );

    // Redirect STDOUT to the new console by associating STDOUT's file 
    // descriptor with an existing operating-system file handle.
    int hConsoleHandle = _open_osfhandle( (intptr_t)stdOutputHandle, _O_TEXT );
    FILE *pFile = _fdopen( hConsoleHandle, "w" );
    *stdout = *pFile;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // This call ensures that iostream and C run-time library operations occur  
    // in the order that they appear in source code.
    ios::sync_with_stdio();
}



/*

	fout << "step branch_mean   branch_max   branch_min   branch_var branch_std   deadend_mean   deadend_max   deadend_min   deadend_var deadend_std sample" << endl;
	for(int i = 2; i < 21; i++){
	    fout << i << " ";
		fout << ss.mean(Statistic::BRANCH, db->getStates(GameDB::STEP_EQUAL, i)) << " ";
		fout << ss.MAX(Statistic::BRANCH, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.MIN(Statistic::BRANCH, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.variance(Statistic::BRANCH, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << sqrt(ss.variance(Statistic::BRANCH, db->getStates(GameDB::STEP_EQUAL, i)))  << " ";

		fout << ss.mean(Statistic::DEADEND, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.MAX(Statistic::DEADEND, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.MIN(Statistic::DEADEND, db->getStates(GameDB::STEP_EQUAL, i))  <<  " ";
		fout << ss.variance(Statistic::DEADEND, db->getStates(GameDB::STEP_EQUAL, i)) << " ";
		fout << sqrt(ss.variance(Statistic::DEADEND, db->getStates(GameDB::STEP_EQUAL, i))) << " ";
		fout << db->getStates(GameDB::STEP_EQUAL, i).size() << endl;
	}
		fout << "ALL" << " ";
		fout << ss.mean(Statistic::BRANCH, db->getStates(GameDB::ALL, 0)) << " ";
		fout << ss.MAX(Statistic::BRANCH, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.MIN(Statistic::BRANCH, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.variance(Statistic::BRANCH, db->getStates(GameDB::ALL, 0))  << " ";
		fout << sqrt(ss.variance(Statistic::BRANCH, db->getStates(GameDB::ALL, 0)))  << " ";

		fout << ss.mean(Statistic::DEADEND, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.MAX(Statistic::DEADEND, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.MIN(Statistic::DEADEND, db->getStates(GameDB::ALL, 0))  <<  " ";
		fout << ss.variance(Statistic::DEADEND, db->getStates(GameDB::ALL, 0)) << " ";
		fout << sqrt(ss.variance(Statistic::DEADEND, db->getStates(GameDB::ALL, 0))) << " ";
		fout << db->getStates(GameDB::ALL, 0).size() << endl;
		*/



/*Statistic ss;
	ss.calculateComplexity(db->states);

	ofstream fout(".\\data\\gameboard10\\Complexity_Analysis.txt", ios::out|ios::trunc);
	fout << "step complexity_mean  complexity_max complexity_min  complexity_var complexity_std sample" << endl;
	for(int j = 2; j < 10; j++){
		vector<GameState*> s = db->getStates(GameDB::CROSS_OUT_EQUAL, j);
		fout << "cross_out" << j << endl;
		for(int i = 2; i < 21; i++){
			fout << i << " ";
			fout << ss.mean(Statistic::COMPLEXITY, db->getStates(s, GameDB::STEP_EQUAL, i)) << " ";
			fout << ss.MAX(Statistic::COMPLEXITY, db->getStates(s, GameDB::STEP_EQUAL, i))  << " ";
			fout << ss.MIN(Statistic::COMPLEXITY, db->getStates(s, GameDB::STEP_EQUAL, i))  << " ";
			fout << ss.variance(Statistic::COMPLEXITY, db->getStates(s, GameDB::STEP_EQUAL, i))  << " ";
			fout << sqrt(ss.variance(Statistic::COMPLEXITY, db->getStates(s, GameDB::STEP_EQUAL, i)))  << " " << endl;

		}
		fout << "ALL" << " ";
		fout << ss.mean(Statistic::COMPLEXITY, db->getStates(s, GameDB::ALL, 0)) << " ";
		fout << ss.MAX(Statistic::COMPLEXITY, db->getStates(s, GameDB::ALL, 0))  << " ";
		fout << ss.MIN(Statistic::COMPLEXITY, db->getStates(s, GameDB::ALL, 0))  << " ";
		fout << ss.variance(Statistic::COMPLEXITY, db->getStates(s, GameDB::ALL, 0))  << " ";
		fout << sqrt(ss.variance(Statistic::COMPLEXITY, db->getStates(s, GameDB::ALL, 0)))  << " ";
		fout << db->getStates(s, GameDB::ALL, 0).size() << endl;
		fout << endl;
	}

	fout.close();

	db->saveGames(".\\data\\gameboard10\\db_ALL_GAME.dat");*/
/*
	Statistic ss;
	ofstream fout(".\\data\\gameboard10\\Complexity_AnalysisALL.txt", ios::out|ios::trunc);
	fout << "step complexity_mean  complexity_max complexity_min  complexity_var complexity_std sample" << endl;
	for(int i = 2; i < 21; i++){
		fout << ss.mean(Statistic::COMPLEXITY, db->getStates(GameDB::STEP_EQUAL, i)) << " ";
		fout << ss.MAX(Statistic::COMPLEXITY, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.MIN(Statistic::COMPLEXITY, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << ss.variance(Statistic::COMPLEXITY, db->getStates(GameDB::STEP_EQUAL, i))  << " ";
		fout << sqrt(ss.variance(Statistic::COMPLEXITY, db->getStates(GameDB::STEP_EQUAL, i)))  << " " << endl;
	}

		fout << "ALL" << " ";
		fout << ss.mean(Statistic::COMPLEXITY, db->getStates(GameDB::ALL, 0)) << " ";
		fout << ss.MAX(Statistic::COMPLEXITY, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.MIN(Statistic::COMPLEXITY, db->getStates(GameDB::ALL, 0))  << " ";
		fout << ss.variance(Statistic::COMPLEXITY, db->getStates(GameDB::ALL, 0))  << " ";
		fout << sqrt(ss.variance(Statistic::COMPLEXITY, db->getStates(GameDB::ALL, 0)))  << " ";
		fout << db->getStates(GameDB::ALL, 0).size() << endl;
	fout.close();
	*/