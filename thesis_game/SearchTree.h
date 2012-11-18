#include "vector"
#include "stack"
#include "Node.h"
#include "GameState.h"
#include <vector>
using namespace std;


#ifndef SEARCHTREE
#define SEARCHTREE


class SearchTree{
public:
	SearchTree();
	~SearchTree(){};

public://search function
	void beginSearch(int times, vector<GameState*> states, int mode);
	void randomDFS(GameState* _initState);
	
public:
	void astar(GameState* _initState);
	void bfs(GameState* _initState);
	bool dfs(GameState* _initState);
	bool dfs(int maxDepth, GameState* _initState);
	vector<Node*> expand(Node* node);

	void calculateBranchAndDeadEnds(vector<GameState*> states);
	void calculateBranchAndDeadEnds(GameState* state);
private:
	bool isGoal(Node* node);
	bool isCircle(Node* node, vector<Node*> closed);
	int heuristic(Node* node);//這裡的概念是，我們還要多試幾步才能看到解
	int countFAmount(int F, vector<Node*> fringe);
public:
	enum eSearch{//亂數產生的方向
		BFS = 0,
		DFS = 1,
		ASTAR = 2,
		RANDOMDFS = 3
	};
};

#endif

