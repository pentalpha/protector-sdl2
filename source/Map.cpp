#include "Map.h"

Map::Map(){

}

Map::Map(SDL_Renderer* renderer, std::string location)
: waves(1)
{
	std::fstream file;
	file.open(location.c_str());

	file >> background;
	file >> baseResistance;
	file >> initialGold;
	//std::cout << initialGold << "\n";
	file >> baseLocation.x >> baseLocation.y;
	file >> maxTowers;
	//std::cout << maxTowers << "\n";
	for (int i = 0; i < maxTowers; i++){
		int x, y;
		file >> x >> y;
		//std::cout << x << ", " << y << "\n";
		towerLocation.push({ x, y });
	}
	//towerLocation.push(baseLocation); //ultima localização sempre é a base.
	
	file >> maxRoutes;
	//std::cout << maxRoutes << "\n";
	routes = new List<SDL_Point>[maxRoutes];
	for (int i = 0; i < maxRoutes; i++){
		int nPoints;
		file >> nPoints;
		//std::cout << nPoints << "\n";
		for (int j = 0; j < nPoints; j++){
			int x, y;
			file >> x >> y;
			//std::cout << x << ", " << y << "\n";
			routes[i].push({ x, y });
		}
		routes[i].push(baseLocation);//ultimo ponto sempre é a base
	}
	
	file >> maxWaves;
	//std::cout << maxWaves << "\n";
	for (int i = 0; i < maxWaves; i++){
		Wave tempWave;
		file >> tempWave.time;
		tempWave.time = tempWave.time * 1000;
		file >> tempWave.enemys;
		int nEnemys;
		file >> nEnemys;

		tempWave.distribuition = List<SDL_Point>(0);
		
		for (int j = 0; j < nEnemys; j++){
			int x, y;
			file >> x >> y;
			tempWave.distribuition.push({ x, y });
		}

		waves.push(tempWave);
	}

	/*for (int d = 0; d < waves.getSize(); d++){
		waves[d].print();
	}*/
}
