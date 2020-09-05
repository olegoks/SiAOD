#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "map.h"
#include <vector>

struct Coordinats {
	unsigned int x;
	unsigned int y;
	explicit Coordinats(const unsigned int x_, const unsigned int y_) : x(x_), y(y_) {}
};

enum Floar {
	First = 0,
	Second = 1,
	Third = 2
};

class Character {

private:

	Coordinats coord_;
	Map* third;
	Map* second;
	Map* first;
	Floar current_floar;
	std::vector<Coordinats> saves;

public:

	void Step();
	void SetMaps(Map* first, Map* second, Map* third);
	Coordinats GetCoordinats() const noexcept { return coord_; }
	explicit Character() noexcept :coord_(0, 0), current_floar(Third) { }
	explicit Character(const unsigned int x_, const unsigned int y_) noexcept:coord_(x_, y_), current_floar(Third) {}

};

#endif