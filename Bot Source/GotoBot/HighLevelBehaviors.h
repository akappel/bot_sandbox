#ifndef HIGHLEVELBEHAVIORS_H
#define HIGHLEVELBEHAVIORS_H

#include "Behavior.h"

//////////////////////////////////////////
//***Grab Healthpickup***/////////////////
//Selector: Finds health if health is low
//////////////////////////////////////////

///IsHealthLow: Condition node
//Return true if health is low
class IsHealthLow : public BTTask {

public:
	IsHealthLow(sEntInfo & bot, const sWorldInfo & world);

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

	bool Run();

};


#endif