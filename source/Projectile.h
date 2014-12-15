#ifndef _PROJECTILE_
#define _PROJECTILE_

#include <SDL.h>
#include <iostream>
#include "Sprite.h"
#include "StaticMath.h"

class Projectile{
    public:
		enum ProjectileType{
			FIRE = 1,
			BALL = 0,
			GREEN = 3,
			MAGIC = 2
		};
		Sprite sprite;
		int range;
		float distance;
		int speedDamage;
		Projectile();
		Projectile(SDL_Renderer *renderer, ProjectileType newType, double degrees, SDL_Point position, int _range);
		void update(Uint32 deltaTime); // Atualiza o objeto aplicando a acelaração nas velocidades;
		void draw(SDL_Renderer *renderer);
        
		ProjectileType getType();
		int getDamage();
		StaticMath::Vector getVector();

		void setDamage(int x);
		void setVector(StaticMath::Vector newVector);

		bool outOfRange();

    protected:
		ProjectileType type;
		int damage;
		
		
		StaticMath::Vector speed;

        /*double velX; // Velocidade X do objeto.
        double velY; // Velocidade Y do objeto.
        double ace;*/ // Velocidade com o qual o objeto vai alterar sua velocidade de acordo com a força setada.

};

#endif
