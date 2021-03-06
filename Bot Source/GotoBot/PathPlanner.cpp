#include "PathPlanner.h"

PathPlanner::PathPlanner(const sEntInfo &mEnt, const sWorldInfo &mWorldInfo) :
pEnt(&mEnt),
pWorldInfo(&mWorldInfo)
{}

bool PathPlanner::CreatePathToPosition(vec2 TargetPos, std::list<vec2> &path) {
	//Flush any current nodes in the path
	path.clear();

	//Make a note of the target position
	vDestPos = TargetPos;

	//If the target is unobstructed from the bot's pos, a path does not need to
	//be calculated, and the bot can ARRIVE directly at the destination.
	//isPathObstructed is a method that takes a start position, a target position,
	//and an entity radius and determines if an agent of that size is able
	//to move unobstructed between the two positions. It is used here to determine
	//if the bot can move directly to the target location without the need
	//for planning a path.
	//mEnt->fRadius is broken, using hard value of 4.099 (from enemy npc radius)

	/*if (!isPathObstructed(pEnt->pos, vDestPos, 4.099)) {
		path.push_back(vDestPos);
		return true;
	}*/

	//Find the closest unobstructed node to the bot's position
	//GetClosestNodeToPosition is a method that queries the nav graph nodes (NO
	//NAV GRAPH ATM) nodes to determine the closest unobstructed node to the given
	//position vector. It is used here to find the closest unobstructed node
	//to the bot's current location.

	
	int ClosestNodeToBot = GetClosestNodeToPosition(pEnt->pos);

	//If no visible node found return failure.
	if (ClosestNodeToBot == no_closest_node_found) {
		return false;
	}

	//Find the closest visible unobstructed node to the target position
	int ClosestNodeToTarget = GetClosestNodeToPosition(vDestPos);
	if (ClosestNodeToTarget == no_closest_node_found) {
		return false;
	}

	//Create an instance of the A* search class to search for a path between
	//the closest node to the bot and the closest node to the target position.
	//This A* search will utilize the Euclidean straight heuristic
	
	AStar astar(*pWorldInfo, ClosestNodeToBot, ClosestNodeToTarget);
	path = astar.GetPathToTarget();

	//Convert to indices to vectors
	/*if (!pathIndices.empty()){
		for (std::list<int>::const_iterator nodeIndex = pathIndices.begin(), end = pathIndices.end(); nodeIndex != end; ++nodeIndex) {
			path.push_back(astar.INDEX_NODE_POINTERS[(*nodeIndex)]->vPos);
		}
		path.push_back(TargetPos);
	}
	else {
		return false;
	}*/

	path.push_back(vDestPos);
	
	return true;
}

bool PathPlanner::isPathObstructed(vec2 A, vec2 B, double BoundingRadius) const {
	//Check to see if path between vecs A and B are obstructed
	//Does this by stepping towards vec B from vec A and checking that
	//the bot's bounding box stays in contact with a node

	vec2 ToB = Normalize(B - A);
	vec2 curPos = A;

	//The while loop checks that the bounding radius has not yet made contact
	//with the destination pos.
	while (pow((B.x - curPos.x), 2) + pow((B.y - curPos.y), 2) > pow(BoundingRadius, 2)) {
		//Advance cursor position one step
		curPos += ToB * 0.5 * BoundingRadius;

		//Test that a node intersects with the bounding radius. if no, return True
		//This means that a straight path is "obstructed" and thus, we need to create a path
		//with A*
		if (!doNodesIntersectCircle(curPos, BoundingRadius)) {
			return true;
		}
	}

	return false;
}

bool PathPlanner::doNodesIntersectCircle(vec2 curPos, double BoundingRadius) const {	
	for (int i = 0; i < pWorldInfo->iNumPathNodes; i++) {
		//Determine distance from node to curPos
		double dist = SquaredLength(pWorldInfo->pPathNodes[i].vPos - curPos);
		if (pow((pWorldInfo->pPathNodes[i].vPos.x - curPos.x), 2) + pow((pWorldInfo->pPathNodes[i].vPos.y - curPos.y), 2) < pow(BoundingRadius, 2)) {
			return true;
		}
	}

	//Return false if no nodes are found within the radius
	return false;

}

int PathPlanner::GetClosestNodeToPosition(vec2 pos) const {
	//This method currently runs at O(n^2). From what the book was saying,
	//we can speed this up with BSP, or some other sort of partioning work
	int closestNode = no_closest_node_found;
	double sq_len = 0.0;

	//This particular code should include exception handling for not getting
	//correct node information
	if (closestNode == no_closest_node_found) {
		closestNode = pWorldInfo->pPathNodes[0].nodeIndex;
		sq_len = Length(pWorldInfo->pPathNodes[0].vPos - pos);
	}

	for (int i = 1; i < pWorldInfo->iNumPathNodes; i++) {
		double temp = Length(pWorldInfo->pPathNodes[i].vPos - pos);
		if (temp < sq_len) {
			//Set node index, sq_len
			closestNode = pWorldInfo->pPathNodes[i].nodeIndex;
			sq_len = temp;
		}
	}

	return closestNode;
}