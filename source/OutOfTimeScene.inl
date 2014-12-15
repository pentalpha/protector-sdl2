void Game::OutOfTimeScene::update(Game *pointerToGame){

}

void Game::OutOfTimeScene::render(Game *pointerToGame){
	//limpa a tela
	SDL_RenderClear(pointerToGame->renderer);
	//o sprite tem dois metodos possiveis de "draw", amboms simples
	pointerToGame->timeoutMessage.drawSprite(pointerToGame->renderer);
	pointerToGame->gameOverButton1.draw(pointerToGame->renderer);
	//pointerToGame->gameOverButton2.draw(pointerToGame->renderer);
	//desenha o renderer na tela
	SDL_RenderPresent(pointerToGame->renderer);
}

void Game::OutOfTimeScene::handleInput(Game *pointerToGame, SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONUP){
		if (pointerToGame->gameOverButton1.mouseOver()){
			onExit(pointerToGame, FINALEND);
		}
		//else if (pointerToGame->gameOverButton2.mouseOver()){
			//onExit(pointerToGame, MAIN);
		//}
	}
}

void Game::OutOfTimeScene::onEnter(Game *pointerToGame, GameStates previous){
	pointerToGame->gameOverButton1.setActive(true);
	//pointerToGame->gameOverButton2.setActive(true);
}

void Game::OutOfTimeScene::onExit(Game *pointerToGame, GameStates next){
	pointerToGame->gameOverButton1.setActive(false);
	//pointerToGame->gameOverButton2.setActive(false);
	//sinaliza para finalizar o jogo
	if (next == FINALEND){
		pointerToGame->running = false;
	}
}