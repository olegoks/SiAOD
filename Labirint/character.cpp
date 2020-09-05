#include "character.h"

void Character::Step()
{
	
	unsigned char top = *(first + SIZE * coord_.y - 1 + coord_.x);
	unsigned char bot = *(first + SIZE * coord_.y + 1 + coord_.x);
	unsigned char rihgt = *(first + SIZE * coord_.y + coord_.x + 1);
	unsigned char rihgt = *(first + SIZE * coord_.y + coord_.x - 1);


}

void Character::SetMaps(Map* first, Map* second, Map* third)
{
	this->first = first;
	this->second = second;
	this->third = third;
}
