#ifndef _SPRITE_
#define _SPRITE_

#include <SDL.h>
#include <SDL_image.h>

/*Criei esta classe para facilidtar o uso de sprites*/
/*Ela ser� o equivalente a um GameObject*/

class Sprite
{
public:
	float x, y;//posi��o
	SDL_Point size;//tamanho
	float scale;//escala em que ser� desenhado
	double angle;
	Sprite();
	//renderizador, localiza��o da imagem, posi��o x e y
	Sprite(SDL_Renderer* renderer, const char* location, float a, float b);
	~Sprite();
	void setTexture(SDL_Renderer* renderer, const char* location);
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* location);
	//metodo de desenho simples
	void drawSprite(SDL_Renderer* renderer);
	//metodo de desenho mais complexo, com suporte a rota��o e inver��o (FLIP)
	void drawSprite(SDL_Renderer* renderer, bool allScreen, SDL_RendererFlip flip);
	SDL_Texture* texture;//a textura
protected:
	
};

#endif