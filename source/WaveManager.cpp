#include "WaveManager.h"

WaveManager::WaveManager() :
enemyQueue(1),
waves(1)
{
	totalRoutes = 0;
	arrivalTime = 0;
	totalRoutes = 0;
	minArrival = 0;
	maxArrival = 0;
}

WaveManager::WaveManager(const WaveManager &waveManager){
	arrivalTime = waveManager.arrivalTime;
	enemyQueue = waveManager.enemyQueue;
	totalRoutes = waveManager.totalRoutes;
	waves = waveManager.waves;
	for (int i = 0; i < waves.getSize(); i++){
		waves[i].print();
	}
	maxArrival = waveManager.maxArrival;
	minArrival = waveManager.minArrival;
}


WaveManager::WaveManager(List<Wave> newWaves, int routes) :
enemyQueue(1),
waves(newWaves)
{
	totalRoutes = routes;
	maxArrival = 3000;
	minArrival = 1750;
	for (int i = 0; i < waves.getSize(); i++){
		waves[i].print();
	}
}

/*WaveManager::~WaveManager(){
	enemyQueue.empty();
	waves.empty();
	maxArrival = 0;
	minArrival = 0;
	totalRoutes = 0;
	arrivalTime = 0;
}*/

void WaveManager::createEnemy(List<SDL_Point> distribuition){
	SDL_Point newEnemy;
	List<SDL_Point> list;
	int anterior = 0;
	for (int i = 0; i < distribuition.getSize(); i++){
		int atual = distribuition[i].y + anterior-1;
		list.push({anterior, atual});
		anterior = atual+1;
	}
	int result = StaticMath::getInRange(0, 99);
	for (int i = 0; i < list.getSize(); i++){
		if (result >= list[i].x && result <= list[i].y){
			newEnemy.x = distribuition[i].x;
		}
	}
	newEnemy.y = StaticMath::getInRange(0, totalRoutes - 1);
	std::cout << "total routes" << totalRoutes << "\n";
	//std::cout << "New Enemy: " << newEnemy.x << ", " << newEnemy.y << ";\n";
	enemyQueue.push(newEnemy);
}

void WaveManager::update(int deltaTime){
	//se fila vazia
	//std::cout << "wave updated\n";
	if (enemyQueue.getSize() <= 0){
		//se há uma wave restante
		if (waves.getSize() >= 1){
			//se time da wave maior que 0
			if (waves[0].time > 0){
				//time = time - deltatime
				if (deltaTime >= waves[0].time){
					waves[0].time = 0;
				}
				else{
					waves[0].time -= deltaTime;
				}
				
				std::cout << "waves[0].time " << waves[0].time << "\n";
			//senão
			}else{
				//dá pop na wave
				Wave actualWave = waves.pop();
				//enche a fila baseado na distribuition
				for (int i = 0; i < actualWave.enemys; i++){
					createEnemy(actualWave.distribuition);
				}
				//calcula proximo arrival time
				arrivalTime = StaticMath::getInRange(minArrival, maxArrival);
				//std::cout << "New Arrival Time: " << arrivalTime << "\n";
				
			}
		}
	}//senão
	else{
		//se arrival time menor q zero
		if (arrivalTime <= 0){
			//lança primeiro inimigo como evento
			throwEnemy(enemyQueue.pop());
			//calcula novo arrival time
			arrivalTime = StaticMath::getInRange(minArrival, maxArrival);
			//std::cout << "New Arrival Time: " << arrivalTime << "\n";
		}//senao
		else{
			//diminui arrival time baseado em delta time
			if (deltaTime >= arrivalTime){
				arrivalTime = 0;
			}
			else{
				arrivalTime -= deltaTime;
			}
			//std::cout << "arrivalTime " << arrivalTime << "\n";
		}
	}				
}

void WaveManager::throwEnemy(SDL_Point enemy){
	SDL_Event event;
	SDL_Point *pointer = new SDL_Point;
	pointer->x = enemy.x;
	pointer->y = enemy.y;
	event.type = SDL_USEREVENT;
	event.user.code = 1;
	event.user.data1 = pointer;
	SDL_PushEvent(&event);
	//std::cout << "Throw Enemy: " << enemy.x << ", " << enemy.y << ";\n";
}

int WaveManager::getWaves(){
	return waves.getSize();
}

int WaveManager::timeToNext(){
	if (enemyQueue.getSize() == 0){
		if (waves.getSize() > 0){
			return waves[0].time;
		}
		else{
			return -100;
		}
	}
	else{
		return -100;
	}
}

void WaveManager::skipWaiting(){
	if (enemyQueue.getSize() == 0){
		if (waves.getSize() > 0){
			waves[0].time = 120;
		}
	}
}