#ifndef HIGHLEVELBEHAVIORS_H
#define HIGHLEVELBEHAVIORS_H

#include "Behavior.h"
#include "DllEntry.h"

//////////////////////////////////////////
//***Grab Healthpickup***/////////////////
//Selector: Finds health if health is low
//////////////////////////////////////////

///IsHealthLow: Condition node
//Return true if health is low
class IsHealthLow : public BTTask {

public:
	IsHealthLow(sEntInfo & bot, const sWorldInfo & world);
	~IsHealthLow() {}

	bool Run();

};


///FindClosestHealthPickup: Action node
//Return true if health a health pickup is found. Also
//sets a variable so that later Tasks can path to it.
// TODO Change to "FindClosestItem<"ITEM_CLASS">" so that we can it for multiple items.
// This will make it more modular.
class FindClosestHealthPickup : public BTTask {

public:
	FindClosestHealthPickup(sEntInfo & bot, const sWorldInfo & world);
	~FindClosestHealthPickup() {}

	bool Run();

};


///CreatePathToTarget: Action node
//Return true if path is successfully create
//Again, this can potentially be set up to reference different fields
//in the "Blackboard" data struct aka CreatePathToTarget(target="ENEMY")
//or CreatePathToTarget(target="HEALTH_PICKUP").
class CreatePathToHealthPickup : public BTTask {

public:
	CreatePathToHealthPickup(sEntInfo & bot, const sWorldInfo & world, eEntityTypes t);
	~CreatePathToHealthPickup() {}

	bool Run();
};


///FollowPathToTarget: Action node
class FollowPathToHealthPickup : public BTTask {

public:
	FollowPathToHealthPickup(sEntInfo & bot, const sWorldInfo & world);
	~FollowPathToHealthPickup() {}

	bool Run();
};

#endif