#ifndef _MAP_
#define _MAP_

#include <string>
#include <SDL.h>
#include <fstream>
#include "List.h"
#include "Sprite.h"
#include "Wave.h"

class Map
{
public:
	int baseResistance;
	std::string background;
	unsigned int initialGold;
	SDL_Point baseLocation;
	unsigned short int maxTowers;
	List<SDL_Point> towerLocation;
	unsigned short int maxRoutes;
	List<SDL_Point> *routes;
	unsigned short int maxWaves;
	List<Wave> waves;
	Map();
	Map(SDL_Renderer* renderer, std::string location);

};

#endif