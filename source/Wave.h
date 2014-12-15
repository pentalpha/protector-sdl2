#ifndef _WAVE_
#define _WAVE_

#include <SDL.h>
#include <iostream>
#include "List.h"

struct Wave
{
	Uint32 time;
	int enemys;
	List<SDL_Point> distribuition;

	void print(){
		std::cout << time << "\n";
		std::cout << enemys << "\n";
		for (int d = 0; d < distribuition.getSize(); d++){
			std::cout << distribuition[d].x << ", " << distribuition[d].y << "\n";
		}
	}
};

#endif