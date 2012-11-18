#include <time.h>
#include "math.h"
#include <cstdlib>
#include "hge.h"

#ifndef GAMEPARAMETER
#define GAMEPARAMETER
class GameParameter{
public:
	GameParameter();
	GameParameter(float a);
public:
	GameParameter* clone();
public:

	float B;
	float D;
};


#endif