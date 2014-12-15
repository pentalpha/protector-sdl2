#ifndef _WAVEMANAGER_
#define _WAVEMANAGER_

#include <SDL.h>
#include <iostream>
#include "StaticMath.h"
#include "List.h"
#include "Wave.h"

class WaveManager{
protected:
	List<Wave> waves;
	List<SDL_Point> enemyQueue;
	int arrivalTime;
	int totalRoutes;
	int minArrival;
	int maxArrival;
public:
	WaveManager();
	WaveManager(const WaveManager &waveManager);
	WaveManager(List<Wave> newWaves, int routes);
	//~WaveManager();
	void update(int deltaTime);
	void throwEnemy(SDL_Point enemy);
	void createEnemy(List<SDL_Point> distribuition);
	int getWaves();
	int timeToNext();
	void skipWaiting();
};

#endif