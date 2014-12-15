Game::Stage::Stage(){

}

void Game::Stage::init(SDL_Renderer* renderer, std::string mapLocation)
{
	map = Map(renderer, mapLocation);
	statusBox = Sprite(renderer, "source/img/box-status.png", 10, 40);
	wavesBox = Sprite(renderer, "source/img/box-hordas.png", 10, 10);
	skipButton = Button(renderer, "source/img/skip.png", { 265, 10 });
	skipButton.setActive(true);
	base = map.baseLocation;
	background = Sprite(renderer, map.background.c_str(), 0, 0);
	gold = map.initialGold;
	nTowers = map.maxTowers;
	towers = new Tower[nTowers+1];
	for (int i = 0; i < nTowers; i++){
		towers[i] = Tower(renderer,
			map.towerLocation[i],
			Tower::TowerType::EMPTY_PLACE,
			&enemys);
	}
	towers[nTowers] = Tower(renderer,
		base,
		Tower::TowerType::MASTER,
		&enemys);
	nRoutes = map.maxRoutes;
	routes = new List<SDL_Point>[nRoutes];
	for (int i = 0; i < nRoutes; i++){
		routes[i] = map.routes[i];
	}
	waveManager = WaveManager(map.waves, map.maxRoutes);
	health = map.baseResistance;
	maxWaves = map.waves.getSize();
}

void Game::Stage::makeCollisions(){
	for (int i = 0; i < projectiles.getSize(); i++){
		//pointerToGame->projectiles[i].update(deltaTime);
		SDL_Rect projectileRect;
		projectileRect.x = projectiles[i].sprite.x;
		projectileRect.y = projectiles[i].sprite.y;
		projectileRect.w = projectiles[i].sprite.size.x;
		projectileRect.h = projectiles[i].sprite.size.y;
		
		SDL_Rect enemyRect;
		for (int j = 0; j < enemys.getSize(); j++){
			enemyRect.x = enemys[j].realPosition.x;
			enemyRect.y = enemys[j].realPosition.y;
			enemyRect.w = enemys[j].size.x;
			enemyRect.h = enemys[j].size.y;

			SDL_Rect result;
			if (SDL_IntersectRect(&enemyRect, &projectileRect, &result) == SDL_TRUE ){
				enemys[j].health -= projectiles[i].getDamage();
				enemys[j].speed -= projectiles[i].speedDamage;
				projectiles[i].distance = 3000;

				std::string animLocation;
				SDL_Point tam;
				if (projectiles[i].getType() == Projectile::BALL){
					animLocation = "source/img/Attack1.png";
					tam = { 3, 1 };
				}else if(projectiles[i].getType() == Projectile::FIRE){
					animLocation = "source/img/Attack2.png";
					tam = { 5, 2 };
				}else if(projectiles[i].getType() == Projectile::MAGIC){
					animLocation = "source/img/Attack4.png";
					tam = { 5, 2 };
				}else if(projectiles[i].getType() == Projectile::GREEN){
					animLocation = "source/img/State1.png";
					tam = { 5, 3 };
				}

				Animation::sentAnimation(Animation::Message({ projectileRect.x, projectileRect.y},
				tam, 50, animLocation, 0.2));
			}
			//pointerToGame->enemys[i].update(deltaTime);
			
		}
	}
}

void Game::Stage::update(Game *pointerToGame){

	if (enemys.getSize() < 1){
		if (waveManager.getWaves() < 1){
			onExit(pointerToGame, STAGE);
			return;
		}
	}

	Uint32 deltaTime = SDL_GetTicks() - pointerToGame->updateEnd;

	

	waveManager.update(deltaTime);

	for (int i = 0; i < projectiles.getSize(); i++){
		if (projectiles[i].outOfRange()){
			projectiles.remove(i);
			break;
		}
		else{
			projectiles[i].update(deltaTime);
		}
	}

	for (int i = 0; i < enemys.getSize(); i++){
		if (enemys[i].health <= 0){
			gold += 25;
			enemys.remove(i);
			break;
		}
		else{
			enemys[i].update(deltaTime);
		}
		
	}
	
	for (int i = 0; i < animations.getSize(); i++){
		if (animations[i].active == false){
			animations.remove(i);
			i--;
		}
		else{
			animations[i].update();
		}

	}

	for (int i = 0; i < nTowers+1; i++){
		towers[i].update();
	}

	makeCollisions();
}

void Game::Stage::render(Game *pointerToGame){
	//limpa a tela
	SDL_RenderClear(pointerToGame->renderer);
	//o sprite tem dois metodos possiveis de "draw", amboms simples
	background.drawSprite(pointerToGame->renderer, true, SDL_FLIP_NONE);
	
	//draw enemys
	for (int i = 0; i < enemys.getSize(); i++){
		enemys[i].draw(pointerToGame->renderer);
	}

	//towers
	for (int i = 0; i < nTowers; i++){
		towers[i].draw(pointerToGame->renderer);
		//pointerToGame->towers[i].ammo.draw(pointerToGame->renderer);
	}

	for (int i = 0; i < projectiles.getSize(); i++){
		projectiles[i].draw(pointerToGame->renderer);
	}

	for (int i = 0; i < animations.getSize(); i++){
		animations[i].draw(pointerToGame->renderer);
	}

	//interface
	pointerToGame->pauseButton.draw(pointerToGame->renderer);
	wavesBox.drawSprite(pointerToGame->renderer);
	statusBox.drawSprite(pointerToGame->renderer);
	skipButton.draw(pointerToGame->renderer);
	std::string waveTime;
	if (waveManager.timeToNext() == -100){
		waveTime = "---";
	}
	else{
		waveTime = std::to_string(waveManager.timeToNext() / 1000) + "s";
	}
	pointerToGame->printText(pointerToGame->font, "Horda " + std::to_string(maxWaves - waveManager.getWaves()) + " de " + std::to_string(maxWaves) + " | Proxima: " + waveTime, { 0, 0, 0 }, { 10, 10 }, {235, 28});
	pointerToGame->printText(pointerToGame->font, std::to_string(health), { 0, 0, 0 }, { 37, 41 }, { 28, 23 });
	pointerToGame->printText(pointerToGame->font, std::to_string(gold), { 0, 0, 0 }, { 107, 41 }, { 40, 23 });

	//desenha o renderer na tela
	SDL_RenderPresent(pointerToGame->renderer);
}

void Game::Stage::handleInput(Game *pointerToGame, SDL_Event event){
	
	if (event.type == SDL_MOUSEBUTTONUP){
		//se o usuario clicou no botão de pausa, pausa o jogo
		if (pointerToGame->pauseButton.mouseOver()){
			onExit(pointerToGame, PAUSE);
		}
		else{
			for (int i = 0; i < nTowers; i++){
				if (towers[i].mouseOver()){
					towers[i].setUpgradesOpen( !(towers[i].getUpgradesOpen()) );
				}
			}
			for (int i = 0; i < nTowers; i++){
				if (towers[i].getUpgradesOpen()){
					for (int j = 0; j < towers[i].upgrades.getSize(); j++)
					{
						if (towers[i].upgrades[j].mouseOver()){
							if (towers[i].upgrades[j].getID() == "Torre Comum"){
								if (gold >= 60){
									towers[i].upgradeTower(pointerToGame->renderer, Tower::COMMON_TOWER);
									gold -= 60;
								}
							}
							else if (towers[i].upgrades[j].getID() == "Torre Vermelha"){
								if (gold >= 120){
									towers[i].upgradeTower(pointerToGame->renderer, Tower::RED_TOWER);
									gold -= 120;
								}
							}
							else if (towers[i].upgrades[j].getID() == "Torre Azul"){
								if (gold >= 120){
									towers[i].upgradeTower(pointerToGame->renderer, Tower::BLUE_TOWER);
									gold -= 120;
								}
							}
							else if (towers[i].upgrades[j].getID() == "Torre Verde"){
								if (gold >= 120){
									towers[i].upgradeTower(pointerToGame->renderer, Tower::GREEN_TOWER);
									gold -= 120;
								}
							}
						}
					}
				}
			}
		}
		if (skipButton.mouseOver()){
			waveManager.skipWaiting();
		}
	}
	else if (event.type == SDL_KEYUP){
		if (event.key.keysym.sym == SDLK_n){
			onExit(pointerToGame, GameStates::STAGE);
		}
	}
	else if (event.type == SDL_USEREVENT){
		/*
		1 = ADD ENEMY;
		10 = DAMAGE PLAYER;
		30 = ADD PROJECTILE;
		50 = ADD Animação;
		*/
		if (event.user.code == 1){
			SDL_Point *pointer = (SDL_Point*)event.user.data1;
			std::cout << "ADD Enemy: ";
			std::cout << pointer->x << " " << pointer->y << "\n";
			enemys.push(Enemy(pointerToGame->renderer, 
				pointer->x, 
				routes[pointer->y]));
			delete pointer;
		}
		else if (event.user.code == 30){
			Projectile *pointer = (Projectile*)event.user.data1;
			projectiles.push(*pointer);
			//delete pointer;
		}
		else if (event.user.code == 50){
			Animation::Message *pointer = (Animation::Message*)event.user.data1;
			animations.push(Animation(pointerToGame->renderer, pointer->location.c_str(), 
				pointer->n, pointer->pos, true, pointer->speed, pointer->scale));
			delete pointer;
		}
		else if (event.user.code == 10){
			int *damage = (int*)event.user.data1;
			health -= *damage;
			/*if (health <= 15){
				animations.push(Animation(pointerToGame->renderer, "source/img/flame.png",
				{ 11, 1 }, {base.x - 12, base.y - 12}, false, 100, 1));
				if (health <= 6){
					animations.push(Animation(pointerToGame->renderer, "source/img/flame.png",
					{ 11, 1 }, { base.x + 12, base.y - 12 }, false, 100, 1));
				}
			}*/
			if (health <= 0){
				onExit(pointerToGame, GAMEOVER);
			}
		}

	}
}

void Game::Stage::onEnter(Game *pointerToGame, GameStates previous){
	pointerToGame->pauseButton.setActive(true);
	if (previous == MAIN || previous == STAGE){
	}
	else if (previous == PAUSE){
		//muda a textura do botão de pausa novamente para um simbolo de "Pausar"
		pointerToGame->pauseButton.setTexture(pointerToGame->renderer, "source/img/pause.png");
	}
}

void Game::Stage::onExit(Game *pointerToGame, GameStates next){
	pointerToGame->pauseButton.setActive(false);
	if (next == PAUSE){
		//guarda o estagio atual em "pausedStage" para poder continuar daqui depois
		pointerToGame->pausedStage = pointerToGame->currentScene;
		pointerToGame->currentScene = &pointerToGame->pause;
	}
	else{
		
		//destroy everything
		//delete pointerToGame->towers;

		//for (int i = 0; i < pointerToGame->nRoutes; i++){
			//pointerToGame->routes[i].~List();
		//}

		//delete pointerToGame->routes;
		//pointerToGame->waveManager.~WaveManager();
		
		if (next == GAMEOVER){
			pointerToGame->currentScene = &pointerToGame->gameOver;
		}
		else if (next == STAGE){
			if (nextStage == 0){
				pointerToGame->currentScene = &pointerToGame->victory;
			}
			else if (nextStage == 2){
				pointerToGame->currentScene = &pointerToGame->stage2;
			}
			else if (nextStage == 3){
				pointerToGame->currentScene = &pointerToGame->stage3;
			}
		}
	}
	pointerToGame->currentScene->onEnter(pointerToGame, getStateID());
}

void Game::Stage::setNextMap(int newMap){
	nextStage = newMap;
}