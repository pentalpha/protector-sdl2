#include <SDL.h>
//#include "Scene.h"
#include "Game.h"
#include "gameLock.h"

int main(int argc, char ** argv)
{
	//inicializa��o geral do SDL, poderia ser mais especifica com flags diferentes
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Respons�vel pela trava do jogo, usar a funcao de baixo na hora da apresenta��o, para o jogo rodar apenas por 15 segundos no dia.
	//gameLock lock("source/file");
	gameLock lock("source/file", 15000);

	//contru��o da classe Game
	//os argumentos s�o para a janela do jogo... com titulo, resolu��o 800x600, centralizada na tela e maximizada
	Game game("Setting Up",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN, &lock);

	//executa o jogo, caso tenha tempo dispon�vel naquele dia.
	if (lock.timeVerify())
	{
		game.run();
		lock.timeClose();
		rename("source/auxfile", "source/file");
	}
	return 0;
}