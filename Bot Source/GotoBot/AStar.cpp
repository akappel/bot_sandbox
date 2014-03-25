#include "AStar.h"

const int G_WEIGHT = 10;

AStar::AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT) :
	pWorldInfo(&mWorldInfo),
	closestNodeToBot(CNTB),
	closestNodeToTarget(CNTT)
{
	//Initialize INDEX_NODE_POINTERS
	for (int i = 0; i < pWorldInfo->iNumPathNodes; i++){
		INDEX_NODE_POINTERS[pWorldInfo->pPathNodes[i].nodeIndex] = &pWorldInfo->pPathNodes[i];
	}
	Search();
}

void AStar::Search() {
	//The meat and potatoes. Will be following tutorial and code hosted here:
	//http://www.policyalmanac.org/games/aStarTutorial.htm
	
	//First we will create our openlist, our "closed list" is pathOfNodeIndices
	std::list<int> openList;

	//Some informative maps to help with looking up information
	std::map<int, int> parentNodeOf;
	std::map<int, int> nodeGScore;
	std::map<int, int> nodeHScore;
	std::map<int, int> nodeFScore;
	std::map<int, bool> inClosedList;

	//used while  finding lowest cost node
	int lowestCostNode;

	//Init bool map to false
	for (int i = 0; i < pWorldInfo->iNumPathNodes; i++){
		inClosedList[pWorldInfo->pPathNodes[i].nodeIndex] = false;
	}

	//Then add our initial starting node (CNTB)
	openList.push_back(closestNodeToBot);

	//Add initial node parent of -1, since it is the root
	parentNodeOf[closestNodeToBot] = -1;
	nodeGScore[closestNodeToBot] = 0;

	//Check that the cNodeToBot is not equal to cNodeToTarget
	if (closestNodeToBot == closestNodeToTarget) {
		openList.remove(closestNodeToBot);
		pathOfNodeIndices.push_back(closestNodeToBot);
	}
	else {
		do {
			lowestCostNode = -1;
			// TODO Currently states that list iterator is "not dereferencable". must fix
			//Find node with lowest F cost node in openList
			for (std::list<int>::const_iterator nodeIndex = openList.begin(), end = openList.end(); nodeIndex != end; ++nodeIndex) {
				//Calculate GScore
				//Get the parent's GScore
				int parentGScore = 0;
				if (parentNodeOf[(*nodeIndex)] != -1) {
					parentGScore = nodeGScore[parentNodeOf[(*nodeIndex)]];
				}
				//Add GScore to nodeGScore
				int g = parentGScore + G_WEIGHT;
				//Store GScore for this node into nodeGScore
				nodeGScore[(*nodeIndex)] = g;
				//Calculate HScore, using node vPos and cNodeToTarget
				double h = Length(INDEX_NODE_POINTERS[(*nodeIndex)]->vPos - INDEX_NODE_POINTERS[closestNodeToTarget]->vPos);
				//Store HScore of this node into nodeHScore (May not be needed...)
				//nodeHScore[(*nodeIndex)] = h;
				//Put FScore in nodeFScore for nodeIndex
				nodeFScore[(*nodeIndex)] = g + h;
				//Check if f is lower than current LowestCostNode f
				if (lowestCostNode == -1) {
					lowestCostNode = (*nodeIndex);
				}
				if (nodeFScore[(*nodeIndex)] < nodeFScore[lowestCostNode]) {
					lowestCostNode = (*nodeIndex);
				}
			}

			for (int i = 0; i < 4; i++) {
				int connectingNode = pWorldInfo->pPathNodes[lowestCostNode].connectingNodeIndex[i];
				if (connectingNode != -1 && inClosedList[connectingNode] == false) {
					openList.push_back(connectingNode);
					//Add nodes to openList and their parents to nodeParents
					parentNodeOf[connectingNode] = lowestCostNode;
				}
			}

			//Drop selected lowestCostNode from openList, add to pathOfNodeIndices
			openList.remove(lowestCostNode);
			pathOfNodeIndices.push_back(lowestCostNode);
			inClosedList[lowestCostNode] = true;


		} while (lowestCostNode != closestNodeToTarget);
	}
}

std::list<int> AStar::GetPathToTarget() {
	return pathOfNodeIndices;
}
