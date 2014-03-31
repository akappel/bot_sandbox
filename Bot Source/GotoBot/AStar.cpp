#include "AStar.h"

//Comparator for sorting function
bool LowestF(const pathNode* first, const pathNode* second) {
	return (first->f < second->f);
}


AStar::AStar(const sWorldInfo &mWorldInfo, int CNTB, int CNTT) :
pWorldInfo(&mWorldInfo),
closestNodeToBot(CNTB),
closestNodeToTarget(CNTT)
{
	//One time allocation of array of pathNodes
	numPathNodes = pWorldInfo->iNumPathNodes;
	nodes = new pathNode[numPathNodes];

	//Zero out the nodes space
	memset(nodes, 0, sizeof(pathNode) * numPathNodes);

	//update information about all 495 nodes; we now have
	//an array of information for all of them.
	for (int i = 0; i < numPathNodes; i++) {
		nodes[i].pNode = &pWorldInfo->pPathNodes[i];
		nodes[i].index = pWorldInfo->pPathNodes[i].nodeIndex;
	}

	Search();
}

AStar::~AStar() {
	delete[] nodes;
}

void AStar::Search() {
	//The meat and potatoes. Will be following tutorial and code hosted here:
	//http://www.policyalmanac.org/games/aStarTutorial.htm

	std::list<pathNode*> openList;

	//Then add our initial starting node (CNTB)
	openList.push_back(&nodes[closestNodeToBot]);

	//Make initial node's parent NULL, since it is the root
	nodes[closestNodeToBot].pParent = NULL;
	nodes[closestNodeToBot].g = 0.0f;
	nodes[closestNodeToBot].h = Length(nodes[closestNodeToBot].pNode->vPos - nodes[closestNodeToTarget].pNode->vPos);
	nodes[closestNodeToBot].f = nodes[closestNodeToBot].g + nodes[closestNodeToBot].h;

	pathNode* currentNode;
	while (!openList.empty()) {

		//Sort openList so that front node always has the lowest f score
		openList.sort(LowestF);
		//Get front node in openList
		currentNode = openList.front();
		//remove it from the openList
		openList.pop_front();
		//Change state to explored
		currentNode->state = EXPLORED;

		//Check if current node is equal to target node
		if (currentNode->index == closestNodeToTarget) {
			//begin going backwards from currentNode through parents to start node, push_front node's vPos
			while (currentNode != NULL) {
				vPathOfNodes.push_front(currentNode->pNode->vPos);
				currentNode = currentNode->pParent;
			}
			break;
		}

		//Add nodes to openList and set parent to current node
		for (int i = 0; i < 4; i++) {
			int connectingNode = currentNode->pNode->connectingNodeIndex[i];
			if (connectingNode != -1 && nodes[connectingNode].state != EXPLORED) {
				openList.push_back(&nodes[connectingNode]);
				nodes[connectingNode].pParent = currentNode;
				//Calculate scores
				nodes[connectingNode].g = Length(nodes[connectingNode].pNode->vPos - currentNode->pNode->vPos) + currentNode->g;
				nodes[connectingNode].h = Length(nodes[connectingNode].pNode->vPos - nodes[closestNodeToTarget].pNode->vPos);
				nodes[connectingNode].f = nodes[connectingNode].g + nodes[connectingNode].h;

			}
		}
	}
}

std::list<vec2> AStar::GetPathToTarget() {
	return vPathOfNodes;
}