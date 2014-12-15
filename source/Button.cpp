#include "Button.h"
#include "SDL_image.h"

Button::Button(){
}

Button::Button(SDL_Renderer* renderer, const char* location, SDL_Point point, std::string newID)
: Sprite(renderer, location, point.x, point.y),
glow(renderer, "source/img/gray.png", point.x, point.y),
id(newID)
{
	glow.size = size;

	active = false;
}

Button::~Button(){
}

bool Button::mouseOver(){
	if (active){
		//faz a colisão com a localização do mouse
		SDL_Point mousePoint;
		SDL_GetMouseState(&mousePoint.x, &mousePoint.y);//pega a localização do mouse
		if (mousePoint.x >= x && mousePoint.x <= x + size.x){
			if (mousePoint.y >= y && mousePoint.y <= y + size.y){
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else{
		return false;
	}
}

void Button::draw(SDL_Renderer* renderer){
	if (active){
		drawSprite(renderer);
		if (mouseOver()){
			glow.drawSprite(renderer);
		}
	}
}

void Button::setActive(bool x){
	active = x;
}
bool Button::isActive(){
	return active;
}

std::string Button::getID(){
	return id;
}
void Button::setID(std::string newID){
	id = newID;
}