


#ifndef GRID
#define GRID

class Grid{
public:
	Grid(){x = y = 0;};
	Grid(int _x, int _y){
			x = _x;
			y = _y;
		};

	void set(int _x, int _y){
		x = _x;
		y = _y;
	};
public:
	int x;
	int y;
};


#endif

