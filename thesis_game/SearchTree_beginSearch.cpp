#include "SearchTree.h"


void SearchTree::beginSearch(int times, std::vector<GameState*> states, int mode = DFS){


		switch(mode){
			case BFS:	
				cout << "processing BFS, please waiting:" << endl;
				break;
			case DFS:
				cout << "processing DFS, please waiting:" << endl;
				break;
			case ASTAR:
				cout << "processing ASTAR, please waiting:" << endl;
				break;
			case RANDOMDFS:
				cout << "processing RANDOMDFS, please waiting:" << endl;
				break;
		}






		for(int i = 0; i < times ; i++){
			
			int j = 0;
			for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
				GameState* state = *it;
				j++;
				cout << j << "/" << states.size() << endl;

				switch(mode){
					case BFS:	
						bfs(state);
						break;
					case DFS:
						dfs(state);
						break;
					case ASTAR:
						astar(state);
						break;
					case RANDOMDFS:
						randomDFS(state);
						break;
				}
			}
			cout << "executed times:" << i + 1 << "/" << times << endl;
		}

	cout << "finish!" << endl;;

}

