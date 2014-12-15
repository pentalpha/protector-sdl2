#ifndef _ENEMY_
#define _ENEMY_

#include <SDL.h>
#include <string>
#include "List.h"
#include "Animation.h"
#include "StaticMath.h"

class Enemy {
protected:
    std::string name;
    int type;
	
	int damage;
	

    Animation down;
    Animation left;
    Animation right;
    Animation up;

    List<SDL_Point> path;
	int gap;
    //Node<SDL_Point> next_point; // ponto de destino atual;
    StaticMath::Vector vector;
	double relativePosition;
	double maxDistance;
	int cooldown;
	int lastShot;
	
public:
	int value;
	float speed;
	int health;
	SDL_Point size;
	SDL_Point realPosition;
	Enemy();
	Enemy(SDL_Renderer *renderer, 
		int _type,
		List<SDL_Point> newPath);
	void update(Uint32 deltaTime);
	void draw(SDL_Renderer* renderer);
	
	void newDirection();
	void damagePlayer();
	/*void set_angle();
    void set_anim();
    void change_anim(char &i);
    bool got_to_destiny();*/
};

#endif