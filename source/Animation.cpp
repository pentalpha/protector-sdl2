#include "Animation.h"

Animation::Animation(){

}

Animation::Animation(SDL_Renderer *renderer, const char* location, SDL_Point sprites, SDL_Point point, bool isFinite, int spriteDuration, float animScale){
    SDL_Point size;
	SDL_Surface* tempSurf = IMG_Load(location);//carrega de acordo com a localização
	texture = SDL_CreateTextureFromSurface(renderer, tempSurf);//cria a textura a partir da "Surface"
	SDL_FreeSurface(tempSurf);//libera o espaço alocado na memoria para a "Surface"
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	spritesNumber = sprites;
	actual_frame.w = size.x / sprites.x;
    actual_frame.h = size.y / sprites.y;
    actual_frame.x = actual_frame.y = 0;
    position = point;
    finite = isFinite;
    duration = spriteDuration;
	count.x = count.y = 0;
	scale = animScale;
	start();
}

void Animation::start(){
	spriteStarted = SDL_GetTicks();
	active = true;
}

void Animation::update() {
    if (active) {
        if (spriteStarted + duration <= SDL_GetTicks()){
            spriteStarted = SDL_GetTicks();
			count.x++;
            if (count.x >= spritesNumber.x){

				if (spritesNumber.y == 1){
					if (finite){
						active = false;
						count.x = spritesNumber.x - 1;
					}
					else{
						count.x = count.y = 0;
					}
				}
				else{
					count.y++;
					count.x = 0;
					if (count.y >= spritesNumber.y){
						if (finite){
							active = false;
							count.x = spritesNumber.x - 1;
							count.y = spritesNumber.y - 1;
						}
						else{
							count.x = count.y = 0;
						}
					}
				}
				
            }
			actual_frame.x = count.x * actual_frame.w;
			actual_frame.y = count.y * actual_frame.h;
        }
    }
}

void Animation::draw(SDL_Renderer* renderer) {

    SDL_Rect destiny;
    destiny.x = position.x;
    destiny.y = position.y;
    destiny.w = actual_frame.w * scale;
    destiny.h = actual_frame.h * scale;
	
	SDL_RenderCopy(renderer, texture, &actual_frame, &destiny);
}

Animation::Message::Message(SDL_Point _pos, SDL_Point _n, int _speed,
	std::string _location, float _scale){
	pos = _pos;
	n = _n;
	speed = _speed;
	location = _location;
	scale = _scale;
}

Animation::Message::Message(){
	
}

void Animation::sentAnimation(Message anim){
	SDL_Event event;
	Message *message = new Message;
	*message = anim;

	event.type = SDL_USEREVENT;
	event.user.code = 50;
	event.user.data1 = message;
	SDL_PushEvent(&event);
}