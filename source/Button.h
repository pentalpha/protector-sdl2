#ifndef _BUTTON_
#define _BUTTON_

#include <SDL.h>
#include <string>
#include "Sprite.h"
//essa classezinha � muito util... ela implementa um bot�o
//(por�m sem uma fun��o propria, ela apenas pode retornar se o mouse est� sobre ela, para sabermos se ouve um click)
class Button :
	public Sprite
{
public:
	Button();
	Button(SDL_Renderer* renderer, const char* location, SDL_Point point, std::string newID = " ");
	~Button();
	//retorna se o mouse est� sobre o bot�o
	bool mouseOver();
	//desenha o bot�o
	void draw(SDL_Renderer* renderer);
	//seta se o bot�o est� ativo ou n�o (um bot�o inativo nunca retorna true em "mouseOver()")
	void setActive(bool x);
	bool isActive();
	std::string getID();
	void setID(std::string newID);
protected:
	//diferen�a de cor aplicada a um bot�o quando o mouse est� sobre ele
	std::string id;
	Sprite glow;
	bool active;
	
};

#endif