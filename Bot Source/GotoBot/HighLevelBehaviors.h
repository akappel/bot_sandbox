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
class IsHealthLow : public Behavior {

public:
	IsHealthLow(Bot& b) : Behavior(b) {}
	~IsHealthLow() {}

	virtual void OnInitialize() {}
	virtual Status Update();
	virtual void OnTerminate(Status) {}
};


///FindClosestHealthPickup: Action node
//Return true if health a health pickup is found. Also
//sets a variable so that later Tasks can path to it.
// TODO Change to "FindClosestItem<"ITEM_CLASS">" so that we can it for multiple items.
// This will make it more modular.
class FindClosestHealthPickup : public Behavior {

public:
	FindClosestHealthPickup(Bot& b) : Behavior(b) {}
	~FindClosestHealthPickup() {}

	virtual void OnInitialize() {}
	virtual Status Update();
	virtual void OnTerminate(Status) {}
};


///CreatePathToTarget: Action node
//Return true if path is successfully create
//Again, this can potentially be set up to reference different fields
//in the "Blackboard" data struct aka CreatePathToTarget(target="ENEMY")
//or CreatePathToTarget(target="HEALTH_PICKUP").
class CreatePathToHealthPickup : public Behavior {

public:
	CreatePathToHealthPickup(Bot& b) : Behavior(b) {}
	~CreatePathToHealthPickup() {}

	virtual void OnInitialize();
	virtual Status Update();
	virtual void OnTerminate(Status) {}
};


///FollowPathToTarget: Action node
class FollowPathToHealthPickup : public Behavior {

public:
	FollowPathToHealthPickup(Bot& b) : Behavior(b) {}
	~FollowPathToHealthPickup() {}

	virtual void OnInitialize() {}
	virtual Status Update();
	virtual void OnTerminate(Status) {}
};

#endif