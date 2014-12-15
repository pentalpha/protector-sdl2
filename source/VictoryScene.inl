void Game::VictoryScene::update(Game *pointerToGame){

}

void Game::VictoryScene::render(Game *pointerToGame){
	//limpa a tela
	SDL_RenderClear(pointerToGame->renderer);
	//o sprite tem dois metodos possiveis de "draw", amboms simples
	pointerToGame->victoryMessage.drawSprite(pointerToGame->renderer);
	pointerToGame->gameOverButton1.draw(pointerToGame->renderer);
	pointerToGame->gameOverButton2.draw(pointerToGame->renderer);
	//desenha o renderer na tela
	SDL_RenderPresent(pointerToGame->renderer);
}

void Game::VictoryScene::handleInput(Game *pointerToGame, SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONUP){
		if (pointerToGame->gameOverButton1.mouseOver()){
			onExit(pointerToGame, FINALEND);
		}
		else if (pointerToGame->gameOverButton2.mouseOver()){
			onExit(pointerToGame, MAIN);
		}
	}
}

void Game::VictoryScene::onEnter(Game *pointerToGame, GameStates previous){
	pointerToGame->gameOverButton1.setActive(true);
	pointerToGame->gameOverButton2.setActive(true);
}

void Game::VictoryScene::onExit(Game *pointerToGame, GameStates next){
	pointerToGame->gameOverButton1.setActive(false);
	pointerToGame->gameOverButton2.setActive(false);
	//sinaliza para finalizar o jogo
	if (next == FINALEND){
		pointerToGame->running = false;
	}
	//volta para o main menu...
	else if (next == MAIN){
		pointerToGame->currentScene = &pointerToGame->mainMenu;
		pointerToGame->currentScene->onEnter(pointerToGame, getStateID());
	}
}