void Game::PauseScene::update(Game *pointerToGame){
}

void Game::PauseScene::render(Game *pointerToGame){
	//limpa a tela
	SDL_RenderClear(pointerToGame->renderer);
	//uma caracteristica importante do metodo de renderização da pausa
	//é que ela desenha, em segundo plano, os graficos da estagio atual
	//para então desenhar sua propria interface
	pointerToGame->pausedStage->render(pointerToGame);
	pointerToGame->pauseButton.draw(pointerToGame->renderer);
	pointerToGame->paused.drawSprite(pointerToGame->renderer);
	//desenha o renderer na tela
	SDL_RenderPresent(pointerToGame->renderer);
}

void Game::PauseScene::handleInput(Game *pointerToGame, SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONUP){
		if (pointerToGame->pauseButton.mouseOver()){
			onExit(pointerToGame, pointerToGame->pausedStage->getStateID());
		}
	}
}

void Game::PauseScene::onEnter(Game *pointerToGame, GameStates previous){
	pointerToGame->pauseButton.setActive(true);
	//muda a imagem do botão de pausa para uma imagem de "Play" ou "Resumir"
	pointerToGame->pauseButton.setTexture(pointerToGame->renderer, "source/img/resume.png");
}

void Game::PauseScene::onExit(Game *pointerToGame, GameStates next){
	pointerToGame->pauseButton.setActive(false);
	if (next == STAGE){
		pointerToGame->currentScene = pointerToGame->pausedStage;
	}
	pointerToGame->currentScene->onEnter(pointerToGame, getStateID());
}