#include "Enemy.h"
#include <iostream>

Enemy::Enemy(){

}

Enemy::Enemy(SDL_Renderer *renderer, int _type, 
	List<SDL_Point> newPath)
	: type(_type),
	path(newPath),
	gap(0),
	realPosition(path[0]),
	relativePosition(0)
{
	int animSpeed, animWidth;
	std::string upLocation, downLocation, leftLocation, rightLocation;
	switch (type)
	{
	case(1) :
		name = "Octorok";
		health = 18;
		damage = 1;
		speed = 10;
		animSpeed = 500;
		animWidth = 4;
		upLocation = "source/img/enemy/octorok_up.png";
		downLocation = "source/img/enemy/octorok_down.png";
		leftLocation = "source/img/enemy/octorok_left.png";
		rightLocation = "source/img/enemy/octorok_right.png";
		value = 10;
		break;
	case(2) :
		name = "Keaton";
		health = 12;
		damage = 1;
		speed = 22;
		animSpeed = 300;
		animWidth = 4;
		upLocation = "source/img/enemy/keaton_up.png";
		downLocation = "source/img/enemy/keaton_down.png";
		leftLocation = "source/img/enemy/keaton_left.png";
		rightLocation = "source/img/enemy/keaton_right.png";
		value = 20;
		break;
	case(3) :
		name = "Moblin";
		health = 40;
		damage = 2;
		speed = 16;
		animSpeed = 300;
		animWidth = 4;
		upLocation = "source/img/enemy/moblin_up.png";
		downLocation = "source/img/enemy/moblin_down.png";
		leftLocation = "source/img/enemy/moblin_left.png";
		rightLocation = "source/img/enemy/moblin_right.png";
		value = 30;
		break;
	case(4) :
		name = "Stalfo";
		health = 35;
		damage = 3;
		speed = 20;
		animSpeed = 250;
		animWidth = 6;
		upLocation = "source/img/enemy/stalfo_up.png";
		downLocation = "source/img/enemy/stalfo_down.png";
		leftLocation = "source/img/enemy/stalfo_left.png";
		rightLocation = "source/img/enemy/stalfo_right.png";
		value = 35;
		break;
	case(5) :
		name = "Eye Gore";
		health = 80;
		damage = 4;
		speed = 15;
		animSpeed = 200;
		animWidth = 9;
		upLocation = "source/img/enemy/eyegore_up.png";
		downLocation = "source/img/enemy/eyegore_down.png";
		leftLocation = "source/img/enemy/eyegore_left.png";
		rightLocation = "source/img/enemy/eyegore_right.png";
		value = 40;
		break;
	default:
		animWidth = 0;
		name = "";
		health = 0;
		damage = 0;
		speed = 0;
		animSpeed = 0;
		value = 0;
		break;
	}

	cooldown = 1000;

	down = Animation(renderer, downLocation.c_str(), { animWidth, 1 }, realPosition, false, animSpeed);
	left = Animation(renderer, leftLocation.c_str(), { animWidth, 1 }, realPosition, false, animSpeed);
	right = Animation(renderer, rightLocation.c_str(), { animWidth, 1 }, realPosition, false, animSpeed);
	up = Animation(renderer, upLocation.c_str(), { animWidth, 1 }, realPosition, false, animSpeed);


	size.x = down.actual_frame.w;
	size.y = down.actual_frame.h;
	lastShot = 0;
	newDirection();
}

void Enemy::update(Uint32 deltaTime){
	if (gap < path.getSize() - 2){
		if (relativePosition >= maxDistance){
			gap++;
			newDirection();
		}
		else{
			relativePosition += speed * deltaTime / 1000;
			realPosition.x = path[gap].x + relativePosition * vector.x;
			realPosition.y = path[gap].y + relativePosition * vector.y;
			right.position = realPosition;
			down.position = realPosition;
			up.position = realPosition;
			left.position = realPosition;
		}
	}
	else{
		if (SDL_GetTicks() >= lastShot + cooldown){
			std::cout << "attack base\n";
			lastShot = SDL_GetTicks();
			damagePlayer();
		}
	}
	
	right.update();
	left.update();
	up.update();
	down.update();
}

void Enemy::newDirection(){
	if (gap >= path.getSize() - 2){
		realPosition = path[path.getSize() - 2];
		vector = StaticMath::calcVector(path[path.getSize() - 2], path[path.getSize() - 1]);
		right.position = realPosition;
		down.position = realPosition;
		up.position = realPosition;
		left.position = realPosition;
		relativePosition = 0;
		speed = 0;
		lastShot = SDL_GetTicks();
	}
	else{
		vector = StaticMath::calcVector(path[gap], path[gap + 1]);
		realPosition = path[gap];
		relativePosition = 0;
		
		right.position = realPosition;
		down.position = realPosition;
		up.position = realPosition;
		left.position = realPosition;
		maxDistance = StaticMath::distance(path[gap], path[gap + 1]);
	}
}

void Enemy::damagePlayer(){
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = 10;
	event.user.data1 = new int(damage);
	SDL_PushEvent(&event);
}

void Enemy::draw(SDL_Renderer* renderer){
	if ((vector.degrees <= 44 && vector.degrees >= 0)
		|| (vector.degrees <= 360 && vector.degrees >= 316)){
		right.draw(renderer);
	}
	else if (vector.degrees <= 135 && vector.degrees >= 45){
		up.draw(renderer);
	}
	else if (vector.degrees <= 224 && vector.degrees >= 136){
		left.draw(renderer);
	}
	else /*(vector.degrees <= 315 && vector.degrees >= 225)*/{
		down.draw(renderer);
	}
}

/*
void Enemy::update() {
    if (got_to_destiny()) {
        next_point = next_point->next;
        set_angle();
        set_anim();
    }
}
void Enemy::set_anim() {
    char i;
    if      (move_angle.cos > 0,707) {
        i = 'r'; // right
    }
    else if (move_angle.cos < -0,707) {
        i = 'l'; // left
    }

    else if (move_angle.sin < 0) {
        i = 'd'; // down
    }
    else {
        i = 'u'; // up
    }
    change_anim(i);
}

void Enemy::change_anim(char &i) {
    down.active = false;
    right.active = false;
    left.active = false;
    up.active = false;

    if (i == 'd') down.active = true;
    else if (i == 'r') right.active = true;
    else if (i == 'l') left.active = true;
    else up.active = true;
}

bool got_to_destiny() {
    float difx = x - next_point->x.x;
    float dify = y - next_point->x.y;
    if ( -1/(speed * move_angle.cos) < difx && difx < 1/(speed * move_angle.cos) &&
            -1/(speed * move_angle.sin) < dify && dify < 1/(speed * move_angle.sin) )
        return true;
    else return false;
	}*/