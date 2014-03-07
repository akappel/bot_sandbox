#include "DllEntry.h"
#include <list>

class PathPlanner {
private:

	//for legibility
	enum {no_closest_node_found = -1};

private:
	//a pointer to the owner of this class aka mEnt
	sEntInfo *mEnt;

	//In the book, it says a reference to a navgraph. I will use a reference to
	//mWorldInfo for now.
	const sWorldInfo &mWorldInfo;

	//Position the bot wishes to plan a path to reach
	vec2 vDestPos;

	//Returns the index of the closest unobstructed graph node to the
	//given position. If none are found (unlikely) it returns the enum val
	//"no_closest_node_found = -1
	int GetClosestNodeToPosition(vec2 pos) const;

	//Finds out if the path is obstructed from source node to destination
	bool isPathObstructed(vec2 A, vec2 B, double BoundingRadius) const;

	//Helper function to determine if a node is within range of bot radius
	bool doNodesIntersectCircle(vec2 curPos, double BoundingRadius) const;

public:
	
	PathPlanner(sEntInfo *ourEnt);

	//Finds the least cost path between the agent's pos and the target
	//pos. Fills path with a list of waypoints if the search is successful
	//and returns true. Returns false if unsuccessful.
	bool CreatePathToPosition(vec2 TargetPos, std::list<vec2> &path);

	//Finds the least cost path to an entity of eEntityTypes with "_PICKUP" in
	//its type. Fills path with list of waypoints if the search is successful
	//and returns true. Returns false if unsuccessful.
	bool CreatePathToItem(unsigned int entityType, std::list<vec2> &path);

};