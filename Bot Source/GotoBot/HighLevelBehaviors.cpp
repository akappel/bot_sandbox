#include "HighLevelBehaviors.h"

//////////////////////////////////////////
//***Grab Healthpickup***/////////////////
//Selector: Finds health if health is low
//////////////////////////////////////////

///IsHealthLow
IsHealthLow::IsHealthLow(const sEntInfo &bot, const sWorldInfo &world) {
	botInfo = &bot;
	worldInfo = &world;
}

Status IsHealthLow::Update() {
	std::cout << "Behavior 'IsHealthLow' updated!" << std::endl;
	if (botInfo->iHealth < 50) {
		std::cout << "Health low!" << std::endl;
		return BH_SUCCESS;
	}
	return BH_FAILURE;
}

/*
///FindClosestHealthPickup
Status FindClosestHealthPickup::Update() {
	//Search for closest healthpickup
	sOtherEnts * target = &m_pBot->pWorldInfo->pOtherEnts[0];

	for (int i = 0; i < m_pBot->pWorldInfo->iNumOtherEnts; i++) {
		if (!m_pBot->pWorldInfo->pOtherEnts[i].bIsInvincible && m_pBot->pWorldInfo->pOtherEnts[i].type == TYPE_HEALTH_PICKUP) {
			if (Length(m_pBot->pWorldInfo->pOtherEnts[i].pos - m_pBot->pBotInfo->pos) < Length(target->pos - m_pBot->pBotInfo->pos)) {
				target = &m_pBot->pWorldInfo->pOtherEnts[i];
			}
		}
	}

	//If one is found, set bot's currentTarget to it and return SUCCESS
	if (target->type == TYPE_HEALTH_PICKUP) {
		m_pBot->currentTarget = target;
		return BH_SUCCESS;
	}
	//If not, return FAILED
	return BH_FAILURE;

}


///CreatePathToHealthPickup
void CreatePathToHealthPickup::OnInitialize() {
	//Clear the current path set
	m_pBot->path.clear();
}

Status CreatePathToHealthPickup::Update() {
	//Generate new path
	if (m_pBot->pPathPlanner->CreatePathToPosition(m_pBot->currentTarget->pos, m_pBot->path)) return BH_SUCCESS;

	return BH_FAILURE;
}


///FollowPathToHealthPickup
void FollowPathToHealthPickup::OnInitialize() {
	//Reset moveDirection to zero in preparation of new movement vector, if there is one
	m_pBot->pBotInfo->moveDirection = m_pBot->pBotInfo->moveDirection * 0;
}

Status FollowPathToHealthPickup::Update() {
	if (m_pBot->path.empty()) {
		return BH_SUCCESS;
	}

	//If the bot has landed on the front node of the list, pop that node
	if (pow(m_pBot->path.front().x - m_pBot->pBotInfo->pos.x, 2) + pow(m_pBot->path.front().y - m_pBot->pBotInfo->pos.y, 2) < 4) {
		m_pBot->path.pop_front();
	}
	//Else move towards it
	else {
		vec2 desiredVel = Normalize(m_pBot->path.front() - m_pBot->pBotInfo->pos) * MAX_ENT_SPEED;
		m_pBot->pBotInfo->moveDirection = desiredVel;
	}

	return BH_RUNNING;
}

void FollowPathToHealthPickup::OnTerminate(Status s) {
	//Reset moveDirection to zero in preparation of new movement vector, if there is one
	m_pBot->pBotInfo->moveDirection = m_pBot->pBotInfo->moveDirection * 0;
}
*/