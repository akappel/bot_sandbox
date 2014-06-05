#include "Bot.h"

Bot::Bot(sEntInfo &bot, const sWorldInfo &world) :
pBotInfo(&bot), 
pWorldInfo(&world)
{
	pPathPlanner = new PathPlanner(bot, world);
	InitBT(bot, world);
}

Bot::~Bot() {
	delete pPathPlanner;
	delete pBehaviorTree;
}

void Bot::InitBT(const sEntInfo &bot, const sWorldInfo &world) {
	//Set up BT for behaviors in HighLevelBehaviors
	pBehaviorTree = new Selector();
}

void Bot::TickBT(float dt) {
	accum += dt;

	if (accum > TICK_SPEED) {
		pBehaviorTree->Tick();
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