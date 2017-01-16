#ifndef TILE_H
#define TILE_H
#include "Vector3.h"
#include "../PathFinder/Node.h"

class Tile
{
public:
	Tile(Vector3 pos, int ID):
		Pos(pos),
		BlockID(ID)
	{};
	Tile(){};
	~Tile(){};
	void SetCollision(bool collide)
	{
		shouldCollide = collide;
	}
	int BlockID;
	Vector3 Pos;
	Node node;
	bool shouldCollide;
	void SetPosition();
	void onTrigger();
};

#endif