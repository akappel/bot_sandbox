#include "DllEntry.h"
#include <list>
#include <map>

enum nodeState {
	UNEXPLORED,
	EXPLORED
};

struct pathNode {
	sPathNode* pNode; //Will give us position, index, and connecting nodes
	pathNode* pParent;

	double g, h, f;

	int index;

	nodeState state;
};

class AStar {
private:
	//Pointer to world info for nodes
	const sWorldInfo *pWorldInfo;
	//Storage of ClosestNodeToBot ClosestNodeToTarget
	int closestNodeToBot, closestNodeToTarget;
	//Path nodes
	int numPathNodes;
	pathNode * nodes;
	//List of path, to be returned
	std::list<vec2> vPathOfNodes;

private:
	//A* star method; places path into pathOfNodeIndices list
	void Search();

public:
	//Initialize AStar instance with pointer to world nodes, ClosestNodeToBot and ClosestNodeToTarget
	AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT);
	~AStar();

	//Simple return function for generated path
	std::list<vec2> GetPathToTarget();

};
