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

/*struct enemyBot {
	//static int numEnemies;
	sOtherEnts *pInfo;
};

//Pointer for current Enemy
enemyBot *enemies;
int numEnemies;
enemyBot currentEnemy;
PathPlanner pathPlanner;
std::list<vec2> path;

//For initialization purposes
bool bInitialRun = true;

//For time keeping
float accum = 0.0f;
const float NEW_PATH_DT = 0.5f;*/

void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float));

/*void InitEnemyBotArray(const sWorldInfo &mWorldInfo) {
	//Get count of enemies
	numEnemies = 0;
	for (int i = 0; i < mWorldInfo.iNumOtherEnts; i++) {
		if (mWorldInfo.pOtherEnts[i].type == TYPE_ENEMY) {
			numEnemies++;
		}
	}
	//init enemy array to count size
	enemies = new enemyBot[numEnemies];

	//add the enemies to that array
	int arrPos = 0;
	for (int i = 0; i < mWorldInfo.iNumOtherEnts; i++) {
		if (mWorldInfo.pOtherEnts[i].type == TYPE_ENEMY) {
			enemies[arrPos].pInfo = &mWorldInfo.pOtherEnts[i];
			arrPos++;
		}
	}
}*/

/*enemyBot FindNewEnemy(enemyBot currentEnemy, const sEntInfo &mEnt) {
	//Set to first enemy in the set
	currentEnemy = enemies[0];

	//Find enemy with the lowest distance from our bot
	for (int i = 1; i < numEnemies; i++) {
		if (!enemies[i].pInfo->bIsInvincible) {
			if (Length(enemies[i].pInfo->pos - mEnt.pos) < Length(currentEnemy.pInfo->pos - mEnt.pos)) {
				currentEnemy = enemies[i];
			}
		}
	}

	//TODO For some reason, the currentEnemy reverts to NULL, when this function returns.
	//I thought the assignment above would work, but it doesn't seem so...
	return currentEnemy;
}*/

Bot * bot;

extern "C" __declspec(dllexport)
void dllmonsteraction(const float dt, 
					  sEntInfo &mEnt, 
					  const sWorldInfo &mWorldInfo, 
					  void (*DrawLine)(vec2,vec2,vColor,float))
{
	/*//Init array of enemy pointers
	if (!enemies) {
		InitEnemyBotArray(mWorldInfo);
	}

	//Initilize the pathPlanner object
	if (!pathPlanner.pEnt && !pathPlanner.pWorldInfo){
		pathPlanner.pEnt = &mEnt;
		pathPlanner.pWorldInfo = &mWorldInfo;
	}

	//Find a new enemy to attack, will happen on first pass
	if (bInitialRun) {
		currentEnemy = FindNewEnemy(currentEnemy, mEnt);
		//Create path to enemy position using pathPlanner
		pathPlanner.CreatePathToPosition(currentEnemy.pInfo->pos, path);
		bInitialRun = false;
	}

	//If current enemy has died, find a new enemy
	if (currentEnemy.pInfo->bIsInvincible) {
		currentEnemy = FindNewEnemy(currentEnemy, mEnt);
	}

	//If our bot dies, create a new path ***WORKS
	//if (mEnt.bIsInvincible) {
	//	pathPlanner.CreatePathToPosition(currentEnemy.pInfo->pos, path);
	//}

	//Create new path every half-second, aka when accumulation of dt > .5
	accum += dt;
	if (accum > NEW_PATH_DT) {
		pathPlanner.CreatePathToPosition(currentEnemy.pInfo->pos, path);
		accum = 0.0f;
	}
	
	//Make sure the path still has nodes to move towards. If not, generate new path
	if (path.empty()) {
		pathPlanner.CreatePathToPosition(currentEnemy.pInfo->pos, path);
	}
	
	//Reset moveDirection to zero in preparation of new movement vector, if there is one
	mEnt.moveDirection = mEnt.moveDirection * 0;
	//If the bot has landed on the front node of the list, pop that node
	if (pow(path.front().x - mEnt.pos.x, 2) + pow(path.front().y - mEnt.pos.y, 2) < 4) {
		path.pop_front();
	}
	//Else move towards it
	else {
		vec2 desiredVel = Normalize(path.front() - mEnt.pos) * MAX_ENT_SPEED;
		mEnt.moveDirection = desiredVel;
	}

	//Aim at the enemy
	mEnt.aimDirection = Normalize(currentEnemy.pInfo->pos - mEnt.pos);

	//Set next command
	mEnt.nextCommand = OP_SHOOT_FIREBALL;*/

	//Start up the bot
	if (!bot) { bot = new Bot(mEnt, mWorldInfo); }
	//Tick it or ticket
	bot->TickBT(dt);
	// TODO
	bot->Fire(dt);
	bot->Move();

	DrawAiPaths(mWorldInfo, DrawLine);
}


void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float))
{
	/*//first find best fit
	vec2 vMin = vec2( 10000,  10000);
	vec2 vMax = vec2(-10000, -10000);

	for(int i=0; i<mWorldInfo.iNumPathNodes; i++)
	{
		sPathNode *pathEnt1 = &mWorldInfo.pPathNodes[i];
		if(pathEnt1->vPos.x < vMin.x)
			vMin.x = pathEnt1->vPos.x;
		if(pathEnt1->vPos.x > vMax.x)
			vMax.x = pathEnt1->vPos.x;

		if(pathEnt1->vPos.y < vMin.y)
			vMin.y = pathEnt1->vPos.y;
		if(pathEnt1->vPos.y > vMax.y)
			vMax.y = pathEnt1->vPos.y;
	}

	float fGridSize = 8.0f;
	//int numX = (vMax.x - vMin.x)/fGridSize;
	//int numY = (vMax.y - vMin.y)/fGridSize;


	//now fill in 2d array of map
	const int XGRID_MAX=70;
	const int YGRID_MAX=70;
	bool pathGrid[XGRID_MAX][YGRID_MAX];
	memset(&pathGrid, 0, sizeof(bool)*XGRID_MAX*YGRID_MAX);
	for(int i=0; i<mWorldInfo.iNumPathNodes; i++)
	{
		sPathNode *pathEnt1 = &mWorldInfo.pPathNodes[i];

		if(pathEnt1->vPos.x>=vMin.x && pathEnt1->vPos.x<=vMax.y &&
			pathEnt1->vPos.y>=vMin.y && pathEnt1->vPos.y<=vMax.y)
		{
			int xPos = int((pathEnt1->vPos.x - vMin.x) / fGridSize);
			int yPos = int((pathEnt1->vPos.y - vMin.y) / fGridSize);

			pathGrid[xPos][yPos] = true;
		}
	}

	//draw lines along y axis
	for(int x=0; x<XGRID_MAX; x++)
	{
		bool bInLine = false;
		vec2 vLineStart;
		for(int y=0; y<YGRID_MAX; y++)
		{
			if(pathGrid[x][y] && !bInLine)
			{
				vLineStart.x = vMin.x + x*fGridSize;
				vLineStart.y = vMin.y + y*fGridSize;
				bInLine = true;
			}

			if(!pathGrid[x][y] && bInLine)
			{
				vec2 vLineEnd;
				vLineEnd.x = vMin.x + x*fGridSize;
				vLineEnd.y = vMin.y + (y-1)*fGridSize;
				DrawLine(vLineStart, vLineEnd, GREEN, 1.0f);
				bInLine = false;
			}
		}
	}

	//draw lines along x axis
	for(int y=0; y<YGRID_MAX; y++)
	{
		bool bInLine = false;
		vec2 vLineStart;
		for(int x=0; x<XGRID_MAX; x++)
		{
			if(pathGrid[x][y] && !bInLine)
			{
				vLineStart.x = vMin.x + x*fGridSize;
				vLineStart.y = vMin.y + y*fGridSize;
				bInLine = true;
			}

			if(!pathGrid[x][y] && bInLine)
			{
				vec2 vLineEnd;
				vLineEnd.x = vMin.x + (x-1)*fGridSize;
				vLineEnd.y = vMin.y + y*fGridSize;
				DrawLine(vLineStart, vLineEnd, GREEN, 0.0f);
				bInLine = false;
			}
		}
	}

	//look for nodes with no connections
	for(int i=0; i<mWorldInfo.iNumPathNodes; i++)
	{
		sPathNode *pathEnt1 = &mWorldInfo.pPathNodes[i];
		bool bFoundConnection = false;
		for(int j=0; j<4; j++)
		{
			if(pathEnt1->connectingNodeIndex[j]!=-1)
			{
				bFoundConnection = true;
				break;
			}
		}

		if(bFoundConnection)
			continue;

		vec2 vTop = pathEnt1->vPos + vec2(0,4);
		vec2 vBot = pathEnt1->vPos + vec2(0,-4);
		vec2 vRight = pathEnt1->vPos + vec2(4,0);
		vec2 vLeft = pathEnt1->vPos+ vec2(-4,0);

		DrawLine(vTop, vBot, GREEN, 0.0f);
		DrawLine(vRight, vLeft, GREEN, 0.0f);
	}*/

	//Draw bot's path
	/*for (std::list<vec2>::const_iterator it = path.begin(); it != path.end(); ++it) {
		std::list<vec2>::const_iterator it2 = it;
		it2++;

		if (it2 == path.end()) {
			break;
		}

		DrawLine((*it), (*it2), RED, 0.0f);

	}*/


	/*
	//old slow way
	for(int i=0; i<mWorldInfo.iNumPathNodes; i++)
	{
		sPathNode *pathEnt1 = &mWorldInfo.pPathNodes[i];
		for(int j=0; j<4; j++)
		{
			if(pathEnt1->connectingNodeIndex[j]!=-1)
			{
				sPathNode *pathEnt2 = &mWorldInfo.pPathNodes[pathEnt1->connectingNodeIndex[j]];
				//DrawLine(pathEnt1->vPos, pathEnt2->vPos, GREEN, 0.0f); 
			}
		}
	}
	*/
}