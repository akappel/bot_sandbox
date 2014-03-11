#include "DllEntry.h"
#include <list>

class AStar {
private:
	//Pointer to world info for nodes
	const sWorldInfo *pWorldInfo;
	//Storage of ClosestNodeToBot ClosestNodeToTarget
	int cNodeToBot, cNodeToTarget;
	//List of path, to be returned
	std::list<int> pathOfNodeIndices;

private:
	void Search();

public:
	//Initialize AStar instance with pointer to world nodes, ClosestNodeToBot and ClosestNodeToTarget
	AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT);

	//Simple return function for generated path
	std::list<int> GetPathToTarget();
};