#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

Game::Game(const char* title, int xpos, int ypos, int width, int height, int flags, gameLock *cLock) 
: running(true),
window(SDL_CreateWindow(title, xpos, ypos, width, height, flags)),//cria a janela
renderer(SDL_CreateRenderer(window, -1, 0))//cria o renderizador da janela
{
	lock = cLock;
	fps = 30;
	delay = 1000.0f / fps; //converte o fps para milisegundos
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//define a cor padrão com que a tela zera atualizada, branco
	
	/*Map map1(renderer, "source/data/stage1.map");
	Map map2(renderer, "source/data/stage2.map"); 
	Map map3(renderer, "source/data/stage3.map");*/

	//paused = Sprite(renderer, "source/img/paused.png", 800/2 - 320/2, 600/2 - 100/2);
	//stage1.background = Sprite(renderer, stage1.map.background.c_str(), 0, 0);
	stage1.init(renderer, "source/data/stage1.map");
	stage2.init(renderer, "source/data/stage2.map");
	stage3.init(renderer, "source/data/stage3.map");

	mainMenuButton1 = Button(renderer, "source/img/iniciar-jogo.png", { 250, 300 });
	gameOverButton1 = Button(renderer, "source/img/exit-game.png", { 250, 300 });
	gameOverButton2 = Button(renderer, "source/img/voltar-menu.png", { 250, 300 + 80 });
	pauseButton = Button(renderer, "source/img/pause.png", { 800 - 10 - 30, 10 });

	//seta para começar no menu iniciar
	mainMenu.onEnter(this, INITIAL);
	currentScene = &mainMenu;
	deltaTime = 0;
	updateEnd = 0;

	paused = Sprite(renderer, "source/img/jogo-pausado.png", 250, 250);
	gameOverMessage = Sprite(renderer, "source/img/game-over.png", 200, 120);
	victoryMessage = Sprite(renderer, "source/img/victory.png", 200, 120);
	titleSprite = Sprite(renderer, "source/img/logo.png", 200, 120);
	titleBackground = Sprite(renderer, "source/img/titleBackground.png", 0, 0);
	timeoutMessage = Sprite(renderer, "source/img/timeOut.png", 200, 50);

	stage1.setNextMap(2);
	stage2.setNextMap(3);
	stage3.setNextMap(0);//ultimo mapa, vai para a cena de "Vitoria"

	//StaticMath::Vector vector;
	//vector = StaticMath::calcVector(10, 90);
	//std::cout << vector.degrees << "\n";
	//std::cout << vector.x << "\n";
	//std::cout << vector.y << "\n";

	font = TTF_OpenFont("source/font/gothic.ttf", 48);
}

void Game::printText(TTF_Font* font, std::string text, SDL_Color color, SDL_Point position, SDL_Point size){
	//SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface = TTF_RenderText_Solid(font,
		text.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,
		surface);
	SDL_Rect destiny;
	destiny.x = position.x;
	destiny.y = position.y;
	destiny.h = size.y;
	destiny.w = size.x;
	SDL_RenderCopy(renderer, texture, NULL, &destiny);
	//SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

Game::~Game(){
	//destrutor do jogo
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



void Game::run(){
	//armazena quando o frame começou
	Uint32 frameStart;
	//armazena quanto durou o frame
	Uint32 frameTime;
	//enquanto estiver rodando
	while (running){
		
		//Atualiza o tempo da trava do jogo.
		if (!lock->timeUpdate())
		{
			//running = false;
			currentScene = &timeOut;
		}

		//pega tempo atual
		frameStart = SDL_GetTicks();
		//processa a logica
		currentScene->update(this);
		updateEnd = SDL_GetTicks();
		//cuida dos eventos
		handleEvents();
		//desenha tudo
		currentScene->render(this);
		//renderiza informações de debug
		debugRender();
		frameTime = SDL_GetTicks() - frameStart;

		//se o frameTime foi mais rapido do que deveria, faz ele esperar
		//if (frameTime < delay){
		//	SDL_Delay((int)(delay - frameTime));
		//}
		//(lembrar: o jogo ainda pode ser mais lento que o FPS padrão, apenas não pode passar disso)
	}
}

void Game::debugRender(){
	printText(font, "gameTime: " + std::to_string(lock->getDecorrido()) + " / " + std::to_string(lock->getMaxTempo()), { 0, 0, 0 }, { 0, 580 }, { 120, 20 });
	SDL_RenderPresent(renderer);
}

void Game::handleEvents(){
	SDL_Event event;
	//"puxa" um evento
	if (SDL_PollEvent(&event)){
		switch (event.type)
		{
		//se o mouse foi solto
		case SDL_MOUSEBUTTONUP:
			//passa o evento para a cena atual
			currentScene->handleInput(this, event);
			break;
		//se o evento for um QUIT(usuario clicou no "X" da janelinha), sinaliza para o jogo parar de rodar
		case SDL_USEREVENT:
			currentScene->handleInput(this, event);
			break;
		case SDL_KEYUP:
			currentScene->handleInput(this, event);
			break;
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

//inclui os arquivos inline das cenas
//LEMBREM-SE: como são arquivos inline, 
//é como se eles estivessem escritos neste "Game.cpp",
//pois, afinal, são parte da classe Game.

#include "MainScene.inl" //<--- esse aqui está mais bem comentado, leiam se tiverem muitas duvidas
#include "Stage.inl"
#include "GameOverScene.inl"
#include "PauseScene.inl"
#include "VictoryScene.inl"
#include "OutOfTimeScene.inl"