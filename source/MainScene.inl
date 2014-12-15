void Game::MainScene::update(Game *pointerToGame){
}

void Game::MainScene::render(Game *pointerToGame){
	SDL_RenderClear(pointerToGame->renderer);//limpa a tela
	//desenha o botão de iniciar o jogo
	pointerToGame->titleBackground.drawSprite(pointerToGame->renderer);
	pointerToGame->titleSprite.drawSprite(pointerToGame->renderer);
	pointerToGame->mainMenuButton1.draw(pointerToGame->renderer);
	SDL_RenderPresent(pointerToGame->renderer);//desenha o renderer na tela
}

void Game::MainScene::handleInput(Game *pointerToGame, SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONUP){
		//se o botão foi clicado, iniciar o jogo!
		if (pointerToGame->mainMenuButton1.mouseOver()){
			onExit(pointerToGame, STAGE);
		}
	}
}

void Game::MainScene::onEnter(Game *pointerToGame, GameStates previous){
	//ativa o botão
	pointerToGame->mainMenuButton1.setActive(true);
	if (previous != INITIAL){
		pointerToGame->stage1 = Stage();
		pointerToGame->stage1.init(pointerToGame->renderer, "source/data/stage1.map");
		pointerToGame->stage2 = Stage();
		pointerToGame->stage2.init(pointerToGame->renderer, "source/data/stage2.map");
		pointerToGame->stage3 = Stage();
		pointerToGame->stage3.init(pointerToGame->renderer, "source/data/stage3.map");
		pointerToGame->stage1.setNextMap(2);
		pointerToGame->stage2.setNextMap(3);
		pointerToGame->stage3.setNextMap(0);
	}
}

void Game::MainScene::onExit(Game *pointerToGame, GameStates next){
	//desativa o botão
	pointerToGame->mainMenuButton1.setActive(false);
	if (next == STAGE){
		//se a proxima cena for STAGE, avançar para ela!
		pointerToGame->currentScene = &pointerToGame->stage1;
	}
	//chama o OnEnter() da proxima cena, passando o apontador para Game e o gameState atual
	pointerToGame->currentScene->onEnter(pointerToGame, getStateID());
}