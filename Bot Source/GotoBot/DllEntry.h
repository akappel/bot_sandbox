#ifndef DLL_ENTRY
#define DLL_ENTRY

/////////////////////////
//DO NOT TOUCH
////////////////////////

#include <math.h>

struct vec2
{
	vec2()
	{
		x = 0.0f;
		y = 0.0f;
	};

	vec2(float a, float b)
	{
		x = a;
		y = b;
	};

	float x, y;

	vec2 operator + (const vec2& v) const	{ return vec2(x+v.x,y+v.y); }
	vec2 operator - (const vec2& v) const	{ return vec2(x-v.x,y-v.y); }
	vec2 operator * (float f) const			{ return vec2(x*f,y*f); }
	vec2 operator / (float f) const			{ return vec2(x/f,y/f); }

	vec2& operator += (const vec2& v)		{ *this = *this + v; return *this; }
	vec2& operator -= (const vec2& v) 		{ *this = *this - v; return *this; }
	vec2& operator *= (float f)				{ *this = *this * f; return *this; }
	vec2& operator /= (float f)				{ *this = *this / f; return *this; }

	bool operator == (const vec2& v) const	{ return x==v.x && y==v.y; }
	bool operator != (const vec2& v) const	{ return !(*this==v); }
	vec2 operator - ()						{ return vec2(-x,-y); }
};

inline float Length(const vec2& v)							{ return sqrtf(v.x*v.x+v.y*v.y); }
inline float SquaredLength(const vec2& v)					{ return v.x*v.x+v.y*v.y; }
inline float DotProduct(const vec2& v1,const vec2& v2)		{ return v1.x*v2.x + v1.y*v2.y; }
inline vec2 Normalize(const vec2& v)						{ return v / Length(v); }
inline vec2 Perpendicular(const vec2& v)					{ return vec2(-v.y,v.x); }

//ops - only one per frame
enum eCreatureCommands
{
	OP_NOTHING,
	OP_ATTACK_FIST,		//doesn't require ammo
	OP_SHOOT_FIREBALL,	//doesn't require ammo
	OP_SHOOT_SHOTGUN,
	OP_SHOOT_CHAINGUN,
	OP_SHOOT_ROCKET,
	OP_SHOOT_GRENADE,
	OP_JUMP,
	OP_ANIM_TAUNT,
	OP_ANIM_WIN,
	OP_ANIM_LOSE,
};

struct sEntInfo
{
	sEntInfo(vec2 _pos, vec2 _vel, int _health, int _grenades, int _shotgunShells, int _chaingunBullets, 
				int _rockets, bool _penalty, bool _invincible, bool _hasQuad, int _carryObject) : //tkampa
			pos(_pos), vel(_vel), iHealth(_health), 
			iGrenades(_grenades), iShotgunShells(_shotgunShells), iChaingunBullets(_chaingunBullets),
			iRockets(_rockets), bIsPenalty(_penalty), bIsInvincible(_invincible), bHasQuad(_hasQuad), iCarryObject(_carryObject) {}; //tkampa

	vec2 pos;						//ReadOnly entity world position (shoot position)
	vec2 vel;						//ReadOnly entity current velocity
	const int iHealth;				//ReadOnly entity current health
	const int iGrenades;			//ReadOnly entity grenades in ammo
	const int iShotgunShells;		//ReadOnly entity shotgun shells in ammo
	const int iChaingunBullets;		//ReadOnly entity chaingun bullets in ammo
	const int iRockets;				//ReadOnly entity rockets in ammo
	const bool bIsPenalty;			//ReadOnly entity is in penalty
	const bool bIsInvincible;		//ReadOnly entity is invincible (happens after penalty)
	const bool bHasQuad;			//ReadOnly entity has quad damage
	const int iCarryObject;		//ReadOnly entity has carry object, tkampa

	vec2 moveDirection;				//Direction of next move
	float fMoveSpeed;				//Speed to move - Max is MAX_ENT_SPEED
	vec2 aimDirection;				//Aim direction
	eCreatureCommands nextCommand;	//next creature op
	float fRadius;					//radius bounding shape
};

enum eEntityTypes
{
	TYPE_ENEMY,
	TYPE_FIREBALL,
	TYPE_ROCKET,
	TYPE_GRENADE,
	TYPE_MODEL,
	TYPE_TELEPORT,
	TYPE_SHOTGUN_PICKUP,
	TYPE_CHAINGUN_PICKUP,
	TYPE_ROCKET_PICKUP,
	TYPE_GRENADE_PICKUP,
	TYPE_HEALTH_PICKUP,
	TYPE_QUADDAMAGE_PICKUP,
	TYPE_CARRYOBJECT_PICKUP, //tkampa
	TYPE_CARRYTARGET, //tkampa

	MAX_TYPES
};

struct sOtherEnts
{
	vec2 pos;						//entity world position
	vec2 vel;						//cur entity velocity (-1.0f to 1.0f)
	int iHealth;					//entity current health if an enemy
	eEntityTypes type;				// see eEntityTymopes for type of this entity
	long ident;						//unique identifier
	bool visible;					//always false
	vec2 collide;					//if not visible, this is the nearest collision point
	float fRadius;					//radius of bounding shape
	bool bIsPenalty;				//entity is in penalty;
	bool bIsInvincible;				//entity is invincible
	eCreatureCommands lastCommand;	//last command of creature
};

static const int MAX_AI_PATH_NODES = 2000;
static const int ROCKET_SPEED = 360;
static const int GRENADE_SPEED = 80;
static const int FIREBALL_SPEED = 200;

struct sPathNode
{
	vec2 vPos;
	int nodeIndex;
	int connectingNodeIndex[4]; //{north, south, east, west}  
};

struct sWorldInfo
{
	int iNumOtherEnts;
	sOtherEnts *pOtherEnts;
	
	int iNumPathNodes;
	sPathNode *pPathNodes;

	vec2 vLastMouseClick;	//position of last mouse click for testing
};

struct vColor
{
	vColor(float _r, float _g, float _b) 
		: r(_r), g(_g), b(_b) {};
	float r, g, b;
};

static const vColor RED		= vColor(1,0,0);
static const vColor GREEN	= vColor(0,1,0);
static const vColor BLUE	= vColor(0,0,1);
static const vColor BLACK	= vColor(0,0,0);
static const vColor WHITE	= vColor(1,1,1);
static const vColor MAGENTA	= vColor(1,0,1);
static const vColor YELLOW	= vColor(1,1,0);


//some constants
#define MAX_ENT_SPEED 60.0f			//units per second


/*Params:
	dt -				delta time in miliseconds	
	mEnt -				writeable info for moving bot
	mWorldInfo -		containes info about the world
	pOtherEnts -		list of other entities in the world
	iNumOtherEnts -		number of entities that were just passed into the function
*/
typedef void (*dllmonsteractionPtr)(const float dt, sEntInfo &mEnt, const sWorldInfo &mWorldInfo, void (*DrawLine)(vec2,vec2,vColor,float)); 



#endif