#include <iostream>
#include "character.h"
#include "map.h"
#include <chrono>
#include <thread>

Map* first = (Map*)new Map[SIZE * SIZE]  {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 0, 1, 1,
	1, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
	1, 0, 1, 0, 0, 1, 0, 0, 0, 0
};

Map* second = (Map*)new Map[SIZE * SIZE];
Map* third = (Map*) new Map[SIZE * SIZE];

int main()
{
	using namespace std::chrono;
	using namespace std;

	Character* person = (Character*) new Character(5, 10);
	person->SetMaps(first, second, third);
	bool game_is_running = true;
	
	while (game_is_running) {


		person->Step();

		this_thread::sleep_for(1s);
	}

}

