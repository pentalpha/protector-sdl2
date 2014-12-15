#ifndef _SPRITE_
#define _SPRITE_

#include <SDL.h>
#include <SDL_image.h>

/*Criei esta classe para facilidtar o uso de sprites*/
/*Ela será o equivalente a um GameObject*/

class Sprite
{
public:
	float x, y;//posição
	SDL_Point size;//tamanho
	float scale;//escala em que será desenhado
	double angle;
	Sprite();
	//renderizador, localização da imagem, posição x e y
	Sprite(SDL_Renderer* renderer, const char* location, float a, float b);
	~Sprite();
	void setTexture(SDL_Renderer* renderer, const char* location);
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* location);
	//metodo de desenho simples
	void drawSprite(SDL_Renderer* renderer);
	//metodo de desenho mais complexo, com suporte a rotação e inverção (FLIP)
	void drawSprite(SDL_Renderer* renderer, bool allScreen, SDL_RendererFlip flip);
	SDL_Texture* texture;//a textura
protected:
	
};

#endif