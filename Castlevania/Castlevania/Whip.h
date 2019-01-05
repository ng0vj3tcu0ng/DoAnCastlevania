#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Candle.h"
#include "Item.h"
#include "BossMedusa.h"
#include "BossDog.h"
#include "BossBat.h"
#include "BossFishMan.h"
#include "BrickHidden.h"
#include "BossBigBat.h"
#include "FireBall.h"
#include "debug.h"
#include "Grid.h"
#define WHIP_WEAPON_BBOX_WIDTH  16
#define WHIP_WEAPON_BBOX_HEIGHT 30

#define WHIP_MAXLEVER 2
#define WHIP_HIT_BIGBAT 500

#define SCREEN_WIDTH_HALF 180

#define WHIP_ANI_LEVE1_RIGHT 0
#define WHIP_ANI_LEVE1_LEFT 1
#define WHIP_ANI_LEVE2_RIGHT 2
#define WHIP_ANI_LEVE2_LEFT 3
#define WHIP_ANI_LEVE3_RIGHT 4
#define WHIP_ANI_LEVE3_LEFT 5





class Whip : public CGameObject
{

	int ID_TEX_WHIP;
	int Level;
	bool BeingAttacking; // dang danh'
public:
	bool GetBeingAttacking() { return this->BeingAttacking; }
	void Attacking();

	Whip();
	void LoadWeapon(int weaponType);
	void Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK);
	//void dogcollision(vector<LPGAMEOBJECT*> *Dogg = NULL);
	void BrickHiddenCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void CandelCollision(Grid *Map,vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossMedusaCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossDogCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossFishManCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBigBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void FireBallCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(float screen_x, int SCREEN_WIDTH) { };
	virtual void Update(DWORD dt, int nx,Grid *Map, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

	void LevelUp();
};