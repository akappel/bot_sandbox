#include "Bot.h"

//////////////////////////////
// Bot.cpp
//////////////////////////////


/////////////////////////////////////////////////////
// Bot::Bot(sEntInfo &, const sWorldInfo &)
/////////////////////////////////////////////////////
Bot::Bot(sEntInfo & bot, const sWorldInfo & world) :
pBotInfo(&bot), 
pWorldInfo(&world)
{
	pPathPlanner = new PathPlanner(bot, world);
	InitHighLevelBehaviors(*this);
	//InitLowLevelBehaviors(*this);
}

/////////////////////////////////////////////////////
// Bot::~Bot()
/////////////////////////////////////////////////////
Bot::~Bot() {
	delete pPathPlanner;
	delete btHighLevel;
}

void Bot::InitHighLevelBehaviors(Bot& b) {
	//Set up BT for behaviors in HighLevelBehaviors
	btHighLevel = new Selector();
	Sequence *beh_GetHealthPickup = new Sequence();

	beh_GetHealthPickup->AddChild(new IsHealthLow(b));
	//beh_GetHealthPickup->AddChild(new FindClosestHealthPickup(b));
	//beh_GetHealthPickup->AddChild(new CreatePathToHealthPickup(b));
	//beh_GetHealthPickup->AddChild(new FollowPathToHealthPickup(b));

	btHighLevel->AddChild(beh_GetHealthPickup);
}

void Bot::TickBT(float dt) {
	accum += dt;

	if (accum > HERTZ) {
		btHighLevel->Tick();
		accum = 0;
	}
}

void Bot::Fire(float dt) {

}

void Bot::Move() {
	//Reset moveDirection to zero in preparation of new movement vector, if there is one
	pBotInfo->moveDirection = pBotInfo->moveDirection * 0;
	if (!path.empty()) {
		//If the bot has landed on the front node of the list, pop that node
		if (pow(path.front().x - pBotInfo->pos.x, 2) + pow(path.front().y - pBotInfo->pos.y, 2) < 4) {
			path.pop_front();
		}
		//Else move towards it
		else {
			vec2 desiredVel = Normalize(path.front() - pBotInfo->pos) * MAX_ENT_SPEED;
			pBotInfo->moveDirection = desiredVel;
		}
	}
}

void Bot::ChangeTarget(eEntityTypes entity) {
	//Change current target  to passed entity
	e_CurrentTarget = entity;

	//Calculate new path

}