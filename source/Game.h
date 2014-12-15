#ifndef _GAMEMAIN_
#define _GAMEMAIN_

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Sprite.h"
#include "Tower.h"
#include "Map.h"
#include "Button.h"
#include "WaveManager.h"
#include "Animation.h"
#include "StaticMath.h"
#include "Enemy.h"
#include "Projectile.h"
#include "gameLock.h"

//class Scene;
//cada um representa um estado do jogo e está relacionado com um valor inteiro unico
enum GameStates{
	//sinaliza que o jogo está para iniciar
	INITIAL = -1,
	//menu principal
	MAIN = 0,
	PAUSE = 1,
	//tela de game over
	GAMEOVER = 2,
	//sinaliza que o jogo será finalizado
	FINALEND = -2,
	STAGE = 3,
	VICTORY = 4,
	TIMEOUT = 5
};

class Game{
public:

	//inclui os arquivos de definição das Scenes...
	//como são quase todos iguais, eu coloquei em um unico arquivo mesmo.
	//as Scenes diferentes estão declaradas aqui dentro de outra classe 
	//para evitar um erro de compilação causado por #includes redundantes,
	//pois a Scene precisa do Game, da mesma forma que o Game precisa da Scene.
	
	#include "Scenes.inl"

	//TRAVA DO JOGO
	gameLock *lock;

	//GAME STATES
	//aponta para o estagio que foi pausado durante o estado de pausa
	Scene *pausedStage;
	//cena atual
	Scene *currentScene;
	//cenas disponiveis
	MainScene mainMenu;
	Stage stage1;
	Stage stage2;
	Stage stage3;
	PauseScene pause;
	GameOverScene gameOver;
	VictoryScene victory;
	OutOfTimeScene timeOut;

	//TIME
	//FPS fixo
	int fps;
	//e convertido para milisegundos
	int delay;
	Uint32 deltaTime;
	Uint32 updateEnd;

	TTF_Font *font;

	//SPRITES:
	
	Sprite paused, gameOverMessage, victoryMessage, titleSprite, titleBackground, timeoutMessage;
	
	
	SDL_Texture *octorokUpTexture, *octorokDownTexture, *octorokLeftTexture, *octorokRightTexture;
	Animation animExample;

	//BUTTONS
	Button mainMenuButton1, gameOverButton1, gameOverButton2, pauseButton;

	//SYSTEM:
	//<-indica se o jogo está rodando
	bool running;
	//janela
	SDL_Window* window;
	//renderizador
	SDL_Renderer* renderer;

	//MAPA
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Game();
	Game(const char* title, int xpos, int ypos, int width, int height, int flags, gameLock *cLock);
	void printText(TTF_Font* font, std::string text, SDL_Color color, SDL_Point position, SDL_Point size);
	~Game();
	
	void run(); //metodo principal, executa o jogo

	void debugRender();

	void handleEvents(); //semelhante ao update(), porém serve para que o jogo reaja a eventos

	//retorna se o jogo está rodando
	bool isRunning(){
		return running;
	}
};

#endif
