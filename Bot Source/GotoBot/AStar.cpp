#include "AStar.h"
#include <map>

AStar::AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT) :
	pWorldInfo(&mWorldInfo),
	cNodeToBot(CNTB),
	cNodeToTarget(CNTT)
{
	Search();
}

void AStar::Search() {
	//The meat and potatoes. Will be following tutorial and code hosted here:
	//http://www.policyalmanac.org/games/aStarTutorial.htm
	
	//First we will create our openlist
	std::list<int> openList;

	//Also need a "closed list"
	std::list<int> closedList;

	//Multidimensional array that stores parent square reference
	std::map<int, int> nodeParents;

	//Then add our starting node (CNTB)
	openList.push_back(cNodeToBot);

	//Find all adjacent nodes to CNTB (Working under the assumption
	//that the node index is the same as the element position in pPathNodes)
	for (int i = 0; i < 4; i++) {
		openList.push_back(pWorldInfo->pPathNodes[cNodeToBot].connectingNodeIndex[i]);
		//Add nodes to and their parents to nodeParents
		nodeParents[i] = cNodeToBot;
	}

	//Pop initial node from openList to closedList
	closedList.push_back(openList.front());
	openList.pop_front();
	
	//TODO NEXT: Path Scoring

}

std::list<int> AStar::GetPathToTarget() {
	return pathOfNodeIndices;
}