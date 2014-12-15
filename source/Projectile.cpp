#include "Projectile.h"

Projectile::Projectile(){

}

Projectile::Projectile(SDL_Renderer *renderer, ProjectileType newType,
	double degrees, SDL_Point position, int _range)
	:type(newType)
{
	range = _range;
	float vel;
	std::string location;

	switch (type){
	case BALL:
		vel = 250;
		damage = 4;
		speedDamage = 0;
		location = "source/img/ball.png";
		sprite.scale = 1.0;
		break;
	case FIRE:
		vel = 300;
		damage = 3;
		speedDamage = 0;
		location = "source/img/fireBlast.png";
		sprite.scale = 1.0;
		break;
	case MAGIC:
		vel = 350;
		damage = 8;
		speedDamage = 0;
		location = "source/img/magicBlast.png";
		sprite.scale = 1.0;
		break;
	case GREEN:
		vel = 250;
		damage = 5;
		speedDamage = 3;
		location = "source/img/greenBlast.png";
		sprite.scale = 1.0;
		break;
	default:
		vel = 0;
		damage = 0;
		speedDamage = 0;
		location = "source/img/arrow.png";
		sprite.scale = 1;
	}

	sprite = Sprite(renderer, location.c_str(), position.x, position.y);

	speed = StaticMath::calcVector(vel, degrees);

	sprite.angle = speed.degrees;
	distance = 0;
	std::cout << speed.degrees << "\n";
	std::cout << speed.x << "\n";
	std::cout << speed.y << "\n";
}

void Projectile::update(Uint32 deltaTime)
{
	distance += speed.module * deltaTime / 1000;
	sprite.x += speed.x * deltaTime / 1000;
	sprite.y += speed.y * deltaTime / 1000;
	//std::cout << speed.degrees << "\n";
	//std::cout << distance << "\n";
	//std::cout << sprite.point.x << "\n";
	//std::cout << sprite.y << "\n";
}

bool Projectile::outOfRange(){
	return (distance >= range);
}

void Projectile::draw(SDL_Renderer* renderer){
	sprite.drawSprite(renderer);
}

Projectile::ProjectileType Projectile::getType(){
	return type;
}
int Projectile::getDamage(){
	return damage;
}
StaticMath::Vector Projectile::getVector(){
	return speed;
}

void Projectile::setDamage(int x){
	damage = x;
}
void Projectile::setVector(StaticMath::Vector newVector){
	speed = newVector;
	sprite.angle = speed.degrees;
	
}

/*void Projectile::setForce( LForce* force )
{
    double directionX; // Velocidade do eixo X do projétil.
    double directionY; // Velocidade do eixo Y do projétil.

    directionX = getAce() * cos(force->getDirection() * M_PI / 180);
    if(force->getSentidoX() == 1)
    {
        directionX = directionX;
    }

    directionY = getAce() * sin(force->getDirection() * M_PI / 180);
    if(force->getSentidoY() == 1)
    {
        directionY = -directionY;
    }

    setVel( getVelX() + directionX, getVelY() + directionY ); // Seta a velocidade X e Y do projétil.
}

void Projectile::setAce(double num)
{
    ace = num;
}

void Projectile::setVel(double numX, double numY)
{
    velX = numX;
    velY = numY;
}

double Projectile::getVelX()
{
    return velX;
}

double Projectile::getVelY()
{
    return velY;
}

double Projectile::getAce()
{
    return ace;
}
*/