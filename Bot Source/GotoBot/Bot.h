#pragma once

#include "DllEntry.h"
#include "PathPlanner.h"
#include "Behavior.h"
#include "HighLevelBehaviors.h"
#include <list>
#include <iostream>

/////////////////////////
// Bot.h
/////////////////////////


/*
Purpose: The interface that encapsulates all of the bot's features.
*/

class Bot {
public:
	//Store references to our bot's data and world data, to pass on to our bot's utilities
	sEntInfo *pBotInfo;
	const sWorldInfo *pWorldInfo;

	//Create references for our PathPlanner, BT, etc.
	PathPlanner *pPathPlanner;
	std::list<vec2> path;

	//Behavior tree used for high level behaviors
	Selector *pBehaviorTree;

	//tick speed for BT
	const float TICK_SPEED = 0.5f;
	float accum = 0.0f;

public:
	Bot(sEntInfo &bot, const sWorldInfo &world);
	~Bot();

	//Tick the bot, which provides the delta time to utilities
	void TickBT(float dt);
	
	//Initialize behavior tree
	void InitBT(const sEntInfo &bot, const sWorldInfo &world);

	void Fire(float dt);

	void Move();
};
