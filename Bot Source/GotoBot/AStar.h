#include "DllEntry.h"
#include <list>
#include <map>

class AStar {
private:
	//Pointer to world info for nodes
	const sWorldInfo *pWorldInfo;
	//Storage of ClosestNodeToBot ClosestNodeToTarget
	int closestNodeToBot, closestNodeToTarget;
	//List of path, to be returned
	std::list<int> pathOfNodeIndices;

private:
	//A* star method; places path into pathOfNodeIndices list
	void Search();

public:
	//Initialize AStar instance with pointer to world nodes, ClosestNodeToBot and ClosestNodeToTarget
	AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT);

	//Simple return function for generated path
	std::list<int> GetPathToTarget();

	//Dictionary for node pointers, based on their index ids
	//Can this not be a const??
	std::map<int, sPathNode*> INDEX_NODE_POINTERS;
};