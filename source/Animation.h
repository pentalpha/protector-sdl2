#ifndef _ANIMATION_
#define _ANIMATION_

#include <SDL.h>
#include <SDL_rect.h>
#include <string>
#include "List.h"
#include "Sprite.h"

class Animation{
public:
	struct Message{
		Message();
		Message(SDL_Point _pos, SDL_Point _n, int _speed,
		std::string _location, float _scale);
		SDL_Point pos, n;
		int speed;
		std::string location;
		float scale;
	};
	static void sentAnimation(Message anim);
    SDL_Point position;
    SDL_Rect actual_frame;
    SDL_Point spritesNumber;
    int spriteStarted;
    int duration; // quantidades de frames por imagem
    SDL_Point count;
    bool finite;
    bool active;
	SDL_Texture* texture;
	float scale;

    Animation();
	Animation(SDL_Renderer *renderer, const char* location, SDL_Point sprites, SDL_Point point, bool isFinite, int spriteDuration, float animScale = 1.0);
	void start();
	void update();
    void draw(SDL_Renderer* renderer);
};

#endif