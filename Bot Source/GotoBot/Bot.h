#pragma once

#include "DllEntry.h"
#include "PathPlanner.h"
#include "Behavior.h"
#include "HighLevelBehaviors.h"
#include <list>

/////////////////////////
// Bot.h
/////////////////////////


/*
Purpose: The interface that encapsulates all of the bot's features.
*/

class Selector;

class Bot {
public:
	//////////////////////////////////////
	// member variables
	//////////////////////////////////////
	
	//Store references to our bot's data and world data, to pass on to our bot's utilities
	sEntInfo * pBotInfo;
	const sWorldInfo * pWorldInfo;

	//Create references for our PathPlanner, BT, etc.
	PathPlanner * pPathPlanner;
	std::list<vec2> path;

	Selector * btHighLevel; //Behavior tree used for highlevel behaviors
	Selector * btLowLevel; //Behavior tree used for aiming and shooting at nearest enemy

	eEntityTypes e_CurrentTarget;

	//Store a reference to our current enemy here
	const sOtherEnts * pEnemyBot;

	//tick speed for BT
	const float HERTZ = 0.5f;
	float accum = 0.0f;

public:
	///////////////////////////////////////
	// ctor & dtor
	///////////////////////////////////////
	Bot(sEntInfo & bot, const sWorldInfo & world);
	~Bot();

	///////////////////////////////////////
	// functions
	///////////////////////////////////////

	//Tick the bot, which provides the delta time to utilities
	void TickBT(float dt);

	//std::list<vec2> GetPath();
	//void SetPath();
	//void ClearPath();
	//bool ChangePath();
	
	void ChangeTarget(eEntityTypes entity);

	//Initailze behavior trees
	void InitHighLevelBehaviors(Bot& b);
	//void InitLowLevelBehaviors(Bot& b);

	void Fire(float dt);

	void Move();

	void SetEnemy(const sOtherEnts & enemy);
	sOtherEnts& GetEnemy() const;

};
