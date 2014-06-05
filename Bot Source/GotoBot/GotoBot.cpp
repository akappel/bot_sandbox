//------------------------------------------------------------------
// AIBotExample.cpp : Replace code here!
//------------------------------------------------------------------	

#include "DllEntry.h"
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <list>
#include "PathPlanner.h"
#include "Bot.h"

void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float));

Bot *bot;

extern "C" __declspec(dllexport)
void dllmonsteraction(const float dt, 
					  sEntInfo &mEnt, 
					  const sWorldInfo &mWorldInfo, 
					  void (*DrawLine)(vec2,vec2,vColor,float))
{

	//Start up the bot
	if (!bot) { bot = new Bot(mEnt, mWorldInfo); }
	//Tick it or ticket. #punny #2cool4me
	bot->TickBT(dt);
	// TODO
	bot->Fire(dt);
	bot->Move();

	//Display path
	DrawAiPaths(mWorldInfo, DrawLine);
}


void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float))
{

	//Draw bot's path
	/*for (std::list<vec2>::const_iterator it = path.begin(); it != path.end(); ++it) {
		std::list<vec2>::const_iterator it2 = it;
		it2++;

		if (it2 == path.end()) {
			break;
		}

		DrawLine((*it), (*it2), RED, 0.0f);

	}*/

}