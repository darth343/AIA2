#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "Node.h"
using std::vector;
class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	Node * getNextNodeFromOpenList();
	void FindPath(Vector3 currentPos, Vector3 endGoal);
	void ContinueSearch();
	void openNode(int posX, int posY, float newCost, Node * parent);
	void ClearLists();
	vector<Node *> openList;
	vector<Node *> visitedList;
	vector<Vector3> pathToEnd;
	Node* getStart();
	bool initializedStartandEnd;
	bool found;
	bool isStuck;
private:
	Node* start;
	Node* end;
};

#endif // !PATHFINDER_H
