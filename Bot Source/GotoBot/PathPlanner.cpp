#include "PathPlanner.h"

bool PathPlanner::CreatePathToPosition(vec2 TargetPos, std::list<vec2> &path) {
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
	if (!isPathObstructed(mEnt->pos, TargetPos, 4.099)) {
		path.push_back(TargetPos);
		return true;
	}
	//Find the closest unobstructed node to the bot's position
	//GetClosestNodeToPosition is a method that queries the nav graph nodes (NO
	//NAV GRAPH ATM) nodes to determine the closest unobstructed node to the given
	//position vector. It is used here to find the closest unobstructed node
	//to the bot's current location.
	int ClosestNodeToBot = GetClosestNodeToPosition(mEnt->pos);

	//If no visible node found return failure.
	if (ClosestNodeToBot == no_closest_node_found) {
		return false;
	}

	//Find the closest visible unobstructed node to the target position
	int ClosestNodeToTarget = GetClosestNodeToPosition(TargetPos);
	if (ClosestNodeToTarget == no_closest_node_found) {
		return false;
	}

	//Create an instance of the A* search class to search for a path between
	//the closest node to the bot and the closest node to the target position.
	//This A* search will utilize the Euclidean straight heuristic
	// TODO Begin work on A* class

	return false; //For now
	
}

bool PathPlanner::isPathObstructed(vec2 A, vec2 B, double BoundingRadius) const {
	vec2 ToB = Normalize(B - A);
	vec2 curPos = A;

	while (SquaredLength(B - curPos) > BoundingRadius * BoundingRadius) {
		//Advance cursor position one step
		curPos += ToB * 0.5 * BoundingRadius;

		//Test that a node intersects with the bounding radius. if no, return True
		if (!doNodesIntersectCircle(curPos, BoundingRadius)) {
			return true;
		}
	}

	return false;
}

bool PathPlanner::doNodesIntersectCircle(vec2 curPos, double BoundingRadius) const {	
	for (int i = 0; i < mWorldInfo->iNumPathNodes; i++) {
		//Determine distance from node to curPos
		double dist = SquaredLength(mWorldInfo->pPathNodes[i].vPos - curPos);
		if (dist < BoundingRadius * BoundingRadius) {
			return true;
		}
	}

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
		closestNode = mWorldInfo->pPathNodes[0].nodeIndex;
		sq_len = SquaredLength(mWorldInfo->pPathNodes[0].vPos - pos);
	}

	for (int i = 1; i < mWorldInfo->iNumPathNodes; i++) {
		double temp = SquaredLength(mWorldInfo->pPathNodes[i].vPos - pos);
		if (temp < sq_len) {
			//Set node index, sq_len
			closestNode = mWorldInfo->pPathNodes[i].nodeIndex;
			sq_len = temp;
		}
	}

	return closestNode;
}