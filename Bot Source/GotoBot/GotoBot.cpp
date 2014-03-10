//------------------------------------------------------------------
// AIBotExample.cpp : Replace code here!
//------------------------------------------------------------------	

#include "DllEntry.h"
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <list>
#include "PathPlanner.h"

//Pointer for current Enemy
sOtherEnts *pCurrentEnemy = NULL;
std::list<vec2> path;

void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float));

extern "C" __declspec(dllexport)
void dllmonsteraction(const float dt, 
					  sEntInfo &mEnt, 
					  const sWorldInfo &mWorldInfo, 
					  void (*DrawLine)(vec2,vec2,vColor,float))
{
	//Initial instantiation of pointer to nearest enemy
	if (pCurrentEnemy == NULL) {
		FindNewEnemy(pCurrentEnemy, mEnt, mWorldInfo);
	}

	//Checks if the enemy is dead(?), finds new nearest enemy
	if (pCurrentEnemy->bIsInvincible == TRUE) {
		FindNewEnemy(pCurrentEnemy, mEnt, mWorldInfo);
	}
	
	//Implementation of our path planner
	PathPlanner pathPlanner = PathPlanner::PathPlanner(mWorldInfo);
	pathPlanner.CreatePathToPosition(pCurrentEnemy->pos, path);
	// TODO Implement A* search class, act on its choices of nodes

	//2. Calc desired velocity to enemy
	vec2 desiredVel = Normalize(pCurrentEnemy->pos - mEnt.pos) * MAX_ENT_SPEED;
	mEnt.moveDirection += desiredVel;
	
	//Set direction to face
	if (SquaredLength(mEnt.vel) > 0.00000001) {
		mEnt.aimDirection = Normalize(mEnt.vel);
	}

	//Set next command
	mEnt.nextCommand = OP_SHOOT_FIREBALL;

	/*
	REQUIREMENTS:
		-Get the data
		-Pass data to python
		-Get return data from python
		-Update the data
		-Repeat

	Our data is actually passed by way of reference addresses; one to our bot and one for everything
	else. In order to pass our data to the python interpreter, we'll need to package the data we need
	into a single object and send it off. The thing about it is, a lot of the stuff doesn't change.
	Checking if something has changed before creating a new package of it to send to Python is a lot
	less taxing than just doing it, so checks should be in place to help with load times.

	The python interpreter will be running a state machine in the background. This state machine
	will receive the datagram from this function and update the bot's state. Then return updated
	data to this function so that it in turn can update what it can update.

	datagram = [mEnt + mWorldInfo + dt]

	send(datagram) -> Py -> update_state_from_datagram -> update_bot_data -> return new_datagram [mEnt] -> 
		-> dllmonsteraction -> updatemEnt
	

	*/

	

	DrawAiPaths(mWorldInfo, DrawLine);
}


void DrawAiPaths(const sWorldInfo &mWorldInfo,  void (*DrawLine)(vec2,vec2,vColor,float))
{
	//first find best fit
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
				DrawLine(vLineStart, vLineEnd, GREEN, 0.0f);
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
	}


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

void FindNewEnemy(sOtherEnts *pCurrentEnemy, const sEntInfo &mEnt, const sWorldInfo &mWorldInfo) {
	if (pCurrentEnemy == NULL) {
		pCurrentEnemy = &mWorldInfo.pOtherEnts[0];
	}
	else {
		double currentLen = Length(pCurrentEnemy->pos - mEnt.pos);
		for (int i = 0; i < mWorldInfo.iNumOtherEnts; i++) {
			if (mWorldInfo.pOtherEnts[i].type == TYPE_ENEMY) {
				double temp = Length(mWorldInfo.pOtherEnts[i].pos - mEnt.pos);
				if (temp < currentLen) {
					pCurrentEnemy = &mWorldInfo.pOtherEnts[i];
					currentLen = temp;
				}
			}
		}
	}
}