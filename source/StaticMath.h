#ifndef _STATICMATH_
#define _STATICMATH_

#include <random>
#include <math.h>

class StaticMath{
public:
	struct Vector {
		float degrees;
		float x, y;
		float module;
	};

	static int getInRange(int x, int y){
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(x, y); // define the range
		return distr(eng);
	}
	static float distance(SDL_Point x, SDL_Point y){
		SDL_Point central;
		central.x = y.x - x.x;
		central.y = y.y - x.y;
		return sqrt((central.x * central.x) + (central.y * central.y));
	}
	static Vector calcVector(SDL_Point a, SDL_Point b){
		SDL_Point central;
		central.x = b.x - a.x;
		central.y = b.y - a.y;
		float module = sqrt((central.x * central.x) + (central.y * central.y));
		Vector newVector;
		newVector.x = central.x / module;
		newVector.y = (central.y / module);
		float rad = atan2(central.x, central.y);
		newVector.degrees = rad * 180 / M_PI;
		newVector.degrees -= 90;
		if (newVector.degrees < 0){
			newVector.degrees += 360;
		}
		//newVector.degrees = rad;
		newVector.module = distance({ 0, 0 }, {newVector.x, newVector.y});
		return newVector;
	}

	static Vector calcVector(float module, float degrees){
		Vector newVector;
		newVector.degrees = degrees;

		//degrees = degrees + 90;

		float radians = (degrees / 180) * M_PI;
		newVector.module = module;
		newVector.x = module * cos(radians);
		newVector.y = module * sin(radians);

		if (newVector.x < 0.001 && newVector.x > 0){
			newVector.x = 0;
		}
		if (newVector.x > -0.001 && newVector.x < 0){
			newVector.x = 0;
		}

		return newVector;
	}

	
};

#endif