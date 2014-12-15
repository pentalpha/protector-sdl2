#include "Sprite.h"
#include <iostream>

Sprite::Sprite()
{
	x = 0;
	y = 0;
	scale = 1;
	angle = 0;
}

Sprite::Sprite(SDL_Renderer* renderer, const char* location, float a, float b)
{
	x = a;
	y = b;
	scale = 1;//escala 1, a imagem será desenhada na tela no seu tamanho padrão
	angle = 0;
	setTexture(renderer, location);//carrega a imagem
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(SDL_Renderer* renderer, const char* location){
	SDL_Surface* tempSurf = IMG_Load(location);//carrega de acordo com a localização
	texture = SDL_CreateTextureFromSurface(renderer, tempSurf);//cria a textura a partir da "Surface"
	SDL_FreeSurface(tempSurf);//libera o espaço alocado na memoria para a "Surface"

	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);//passa o tamanho da textura para a variavel size
}

SDL_Texture* Sprite::loadTexture(SDL_Renderer* renderer, const char* location){
	SDL_Texture* newTexture;
	SDL_Surface* tempSurf = IMG_Load(location);//carrega de acordo com a localização
	newTexture = SDL_CreateTextureFromSurface(renderer, tempSurf);//cria a textura a partir da "Surface"
	SDL_FreeSurface(tempSurf);//libera o espaço alocado na memoria para a "Surface"
	return newTexture;
}

void Sprite::drawSprite(SDL_Renderer* renderer){
	SDL_Rect destiny;
	//o retangulo de destino é um retangulo na tela onde a imagem será desenhada
	destiny.x = x;
	destiny.y = y;
	destiny.w = size.x * scale;
	destiny.h = size.y * scale;
	//center representa o ponto ao redor do qual o sprite irá girar
	//lembre-se que o angulo aqui não é radianos... são graus! E no sentido horario.
	SDL_Point center = { destiny.w / 2, destiny.h / 2 };
	SDL_RenderCopyEx(renderer, texture, 0, &destiny, angle, &center, SDL_FLIP_NONE);
}

void Sprite::drawSprite(SDL_Renderer* renderer, bool allScreen, SDL_RendererFlip flip){
	
	//o retangulo de destino é um retangulo na tela onde a imagem será desenhada
	if (allScreen){
		SDL_RenderCopy(renderer, texture, 0, 0);
	} else {
		SDL_Rect destiny;
		destiny.x = x;
		destiny.y = y;
		destiny.w = size.x * scale;
		destiny.h = size.y * scale;
		//center representa o ponto ao redor do qual o sprite irá girar
		//lembre-se que o angulo aqui não é radianos... são graus! E no sentido horario.
		SDL_Point center = { destiny.w / 2, destiny.h / 2 };
		SDL_RenderCopyEx(renderer, texture, 0, &destiny, angle, &center, flip);
	}
}