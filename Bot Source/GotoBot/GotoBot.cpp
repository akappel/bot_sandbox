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