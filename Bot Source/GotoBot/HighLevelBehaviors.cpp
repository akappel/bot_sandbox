#include "HighLevelBehaviors.h"

//////////////////////////////////////////
//***Grab Healthpickup***/////////////////
//Selector: Finds health if health is low
//////////////////////////////////////////

///IsHealthLow
IsHealthLow::IsHealthLow(sEntInfo & bot, const sWorldInfo & world) {
	pBotInfo = &bot;
	pWorldInfo = &world;
}

bool IsHealthLow::Run() {
	//Simple check that starts the Grab healthpickup behavior if 
	//health is low
	if (pBotInfo->iHealth < 50) {
		return true;
	}

	return false;
}


///FindClosestHealthPickup
FindClosestHealthPickup::FindClosestHealthPickup(sEntInfo & bot, const sWorldInfo & world) {
	pBotInfo = &bot;
	pWorldInfo = &world;
}

bool FindClosestHealthPickup::Run() {
	//Search through pWorldInfo objects and find closest HealthPickup
	//(May be better to not use straight line distance, since it may not
	//be the "closest" path-wise)...

	// TODO Implement function
	return true;
	

	// TODO Create sublist of healthpickups on init for faster traversal



}


///CreatePathToTarget
CreatePathToTarget::CreatePathToTarget(sEntInfo & bot, const sWorldInfo & world, eEntityTypes t) {
	pBotInfo = &bot;
	pWorldInfo = &world;
	target = t;
}

bool CreatePathToTarget::Run() {
	// TODO Implement function
	return true;
}


///FollowPathToTarget
FollowPathToTarget::FollowPathToTarget(sEntInfo & bot, const sWorldInfo & world) {
	pBotInfo = &bot;
	pWorldInfo = &world;
}

bool FollowPathToTarget::Run() {
	// TODO Implement function
	return true;
}