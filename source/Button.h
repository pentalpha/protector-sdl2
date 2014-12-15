#ifndef _BUTTON_
#define _BUTTON_

#include <SDL.h>
#include <string>
#include "Sprite.h"
//essa classezinha é muito util... ela implementa um botão
//(porém sem uma função propria, ela apenas pode retornar se o mouse está sobre ela, para sabermos se ouve um click)
class Button :
	public Sprite
{
public:
	Button();
	Button(SDL_Renderer* renderer, const char* location, SDL_Point point, std::string newID = " ");
	~Button();
	//retorna se o mouse está sobre o botão
	bool mouseOver();
	//desenha o botão
	void draw(SDL_Renderer* renderer);
	//seta se o botão está ativo ou não (um botão inativo nunca retorna true em "mouseOver()")
	void setActive(bool x);
	bool isActive();
	std::string getID();
	void setID(std::string newID);
protected:
	//diferença de cor aplicada a um botão quando o mouse está sobre ele
	std::string id;
	Sprite glow;
	bool active;
	
};

#endif