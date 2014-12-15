#ifndef _TOWER_
#define _TOWER_

#include <SDL.h>
#include <iostream>
#include <string>
#include "List.h"
#include "Sprite.h"
#include "Tower.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Button.h"

class Tower{
public:
	enum TowerType{
		MASTER = 0,
		COMMON_TOWER = 1,
		RED_TOWER = 3,
		EMPTY_PLACE = 2,
		BLUE_TOWER = 4,
		GREEN_TOWER = 5
	};

	Sprite sprite;
	List<Button> upgrades;
	Projectile ammo;
	

	Tower();

	Tower(SDL_Renderer* renderer, SDL_Point point, 
		TowerType towerType, List<Enemy> *enemysPointer);
	void upgradeTower(SDL_Renderer *renderer, TowerType newType);
	void update();
	void draw(SDL_Renderer* renderer);
	bool mouseOver();
	bool getUpgradesOpen();
	void setUpgradesOpen(bool x);
protected:
	Uint32 lastShot;
	
	SDL_Point shootStart;
	int cooldown;
	TowerType type;
	std::string name;
	int range;
	
	Sprite arrow;
	List<Enemy> *enemys;
	Sprite infoVerde, infoAzul, infoVermelho, infoComum;
	void throwArrow(int enemy);

	bool upgradesOpen;
};

#endif