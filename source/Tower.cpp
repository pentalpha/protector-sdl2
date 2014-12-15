#include "Tower.h"

Tower::Tower(){
}

Tower::Tower(SDL_Renderer* renderer, SDL_Point point, Tower::TowerType towerType
	, List<Enemy> *enemysPointer) : type(towerType) 
{
	const char* textureLocation;

	Projectile::ProjectileType ammoType;

	for (int i = 0; i < upgrades.getSize(); i++){
		upgrades.pop();
	}

	List<TowerType> towerUpgrades;

	switch (type){
	case (COMMON_TOWER) :
		range = 120;
		name = "Common Tower";
		cooldown = 2000;
		ammoType = Projectile::BALL;
		textureLocation = "source/img/Tower1.png";
		towerUpgrades.push(RED_TOWER);
		towerUpgrades.push(BLUE_TOWER);
		towerUpgrades.push(GREEN_TOWER);
		break;
	case(RED_TOWER) :
		range = 100;
		cooldown = 800;
		name = "Torre Vermelha";
		ammoType = Projectile::FIRE;
		textureLocation = "source/img/Tower2.png";
		break;
	case(BLUE_TOWER) :
		range = 200;
		cooldown = 3500;
		name = "Torre Azul";
		ammoType = Projectile::MAGIC;
		textureLocation = "source/img/Tower3.png";
		break;
	case(GREEN_TOWER) :
		range = 120;
		cooldown = 2000;
		name = "Torre Verde";
		ammoType = Projectile::GREEN;
		textureLocation = "source/img/Tower4.png";
		break;
	case(MASTER) :
		range = 100;
		cooldown = 2000;
		name = "City";
		ammoType = Projectile::GREEN;
		textureLocation = "source/img/none.png";
		break;
	case EMPTY_PLACE:
	default:
		range = 0;
		cooldown = -1;
		name = "Empty Place";
		ammoType = Projectile::BALL;
		textureLocation = "source/img/Tower0.png";
		towerUpgrades.push(COMMON_TOWER);
	}

	sprite = Sprite(renderer, textureLocation, point.x, point.y);
	if (type != MASTER){
		shootStart.x = sprite.x + sprite.size.x / 2;
		shootStart.y = sprite.y + sprite.size.y / 4;
	}
	else{
		shootStart.x = point.x;
		shootStart.y = point.y;
	}
	

	ammo = Projectile(renderer, ammoType, 0, shootStart, range);

	lastShot = 0;

	enemys = enemysPointer;
	
	arrow = Sprite(renderer, "source/img/upgrade.png", point.x + sprite.size.x, point.y + sprite.size.y);
	arrow.x -= arrow.size.x / 2;
	arrow.y -= arrow.size.y / 2;
	arrow.scale = 1;

	SDL_Point buttonLocation = { sprite.x + sprite.size.x + 5, sprite.y };

	for (int i = 0; i < towerUpgrades.getSize(); i++){
		if (towerUpgrades[i] == COMMON_TOWER){
			upgrades.push(Button(renderer, "source/img/upgrade1.png",
			buttonLocation, "Torre Comum"));
		}
		else if (towerUpgrades[i] == RED_TOWER){
			upgrades.push(Button(renderer, "source/img/upgrade2.png",
				buttonLocation, "Torre Vermelha"));
		}
		else if (towerUpgrades[i] == BLUE_TOWER){
			upgrades.push(Button(renderer, "source/img/upgrade3.png",
				buttonLocation, "Torre Azul"));
		}
		else if (towerUpgrades[i] == GREEN_TOWER){
			upgrades.push(Button(renderer, "source/img/upgrade4.png",
				buttonLocation, "Torre Verde"));
		}
		buttonLocation.y += 27;
	}

	for (int i = 0; i < upgrades.getSize(); i++){
		upgrades[i].setActive(false);
	}

	upgradesOpen = false;

	infoComum = Sprite(renderer, "source/img/info-comum.png", buttonLocation.x + 24 + 4, point.y);
	infoVerde = Sprite(renderer, "source/img/info-verde.png", buttonLocation.x + 24 + 4, point.y);
	infoAzul = Sprite(renderer, "source/img/info-azul.png", buttonLocation.x + 24 + 4, point.y);
	infoVermelho = Sprite(renderer, "source/img/info-vermelha.png", buttonLocation.x + 24 + 4, point.y);
}

void Tower::upgradeTower(SDL_Renderer *renderer, TowerType newType){
	for (int i = 0; i < upgrades.getSize(); i++){
		upgrades.pop();
	}

	Animation::sentAnimation(Animation::Message({ sprite.x - 30, sprite.y - 15 }, 
										{ 5, 5 }, 50, "source/img/Heal4.png", 0.5));

	*this = Tower(renderer, {sprite.x, sprite.y}, newType, enemys);
}

void Tower::update(){
	if (cooldown >= 0){
		if (SDL_GetTicks() >= lastShot + cooldown){
			//algoritmo para encontrar um inimigo e, se encontrar,
			//atirar e setar o lastShot para SDL_GetTicks()
			for (int i = 0; i < enemys->getSize(); i++){
				Node<Enemy> *tempEnemy = enemys->nodeX(i);
				if (StaticMath::distance(shootStart, tempEnemy->x.realPosition) <= range){
					throwArrow(i);
					lastShot = SDL_GetTicks();
					std::cout << "shoot\n";
					break;
				}
			}
			
		}
	}
}

void Tower::throwArrow(int enemy){
	SDL_Event event;
	
	StaticMath::Vector oldVector = ammo.getVector();
	Node<Enemy> *node = enemys->nodeX(enemy);
	SDL_Point target = node->x.realPosition;
	StaticMath::Vector degrees = StaticMath::calcVector(shootStart, target);
	ammo.setVector(StaticMath::calcVector(oldVector.module, -degrees.degrees));
	
	event.type = SDL_USEREVENT;
	event.user.code = 30;
	event.user.data1 = &ammo;

	SDL_PushEvent(&event);
}

void Tower::draw(SDL_Renderer* renderer){
	sprite.drawSprite(renderer);
	if (upgrades.getSize() > 0){
		if (upgradesOpen){
			for (int i = 0; i < upgrades.getSize(); i++){
				upgrades[i].draw(renderer);
				if (upgrades[i].mouseOver()){
					if (upgrades[i].getID() == "Torre Comum"){
						infoComum.drawSprite(renderer);
					}
					else if (upgrades[i].getID() == "Torre Vermelha"){
						infoVermelho.drawSprite(renderer);
					}
					else if (upgrades[i].getID() == "Torre Azul"){
						infoAzul.drawSprite(renderer);
					}
					else if (upgrades[i].getID() == "Torre Verde"){
						infoVerde.drawSprite(renderer);
					}
					
				}
			}
		}
		else{
			arrow.drawSprite(renderer);
		}
	}
}

bool Tower::mouseOver(){
	if (upgrades.getSize() > 0){
		//faz a colisão com a localização do mouse
		SDL_Point mousePoint;
		SDL_GetMouseState(&mousePoint.x, &mousePoint.y);//pega a localização do mouse
		if (mousePoint.x >= sprite.x && mousePoint.x <= sprite.x + sprite.size.x){
			if (mousePoint.y >= sprite.y && mousePoint.y <= sprite.y + sprite.size.y){
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

bool Tower::getUpgradesOpen(){
	return upgradesOpen;
}

void Tower::setUpgradesOpen(bool x){
	upgradesOpen = x;
	for (int i = 0; i < upgrades.getSize(); i++){
		upgrades[i].setActive(x);
	}
}