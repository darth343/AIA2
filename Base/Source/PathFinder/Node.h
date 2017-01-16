#ifndef NODE_H
#define NODE_H
#include "Vector3.h"
struct Node
{
	Node() : parent(nullptr) {};
	Node(Vector3 _Pos, Node* parent = nullptr) : parent(parent)
	{
		posX = _Pos.x;
		posY = _Pos.y;
	};
	~Node(){};
	int posX;
	int posY;

	int nodeID;

	Node * parent;

	float G;
	float H;
	float getF(){ return G + H; };
	float Distance(Node* End)
	{
		float x = abs(posX - End->posX);
		float y = abs(posY - End->posY);
		return (x + y) * 10;
	}
};
#endif