#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Candle.h"
#include "Item.h"
#include "BossDog.h"
#include "BossBat.h"
#include "BossFishMan.h"
#include"BossMedusa.h"
#include "BossBigBat.h"
#include "FireBall.h"
#include "Grid.h"

#define HOLYWATER_BBOX_WIDTH 16
#define HOLYWATER_BBOX_HEIGHT 16

#define HOLYWATER_SPEED_X 0.07f
#define HOLYWATER_SPEED_Y 0.1f

#define HOLYWATER_STATE_IDLE		    0
#define HOLYWATER_STATE_THROW_RIGHT		1
#define HOLYWATER_STATE_THROW_LEFT		2
#define HOLYWATER_STATE_FIRE            3

#define HOLYWATER_TURNOFF_TIME 2000

#define SCREEN_WIDTH_HALF 180

class CHOLYWATER : public CGameObject
{
	CTextures * textures;
	int ID_TEX;
	int type = 2;
	int TurnOffFireTime;
	bool isBeingThrown; // dang nem
	bool lock;
	bool NotFalling=false;
	bool LockNx = true; // Co xet nx cua no 1 lan, neu khong quay lung tung :V 
	bool LockVy = true; // Co de khong cho no bay len
public:
	bool getLock() { return this->lock; }
	void Unlock(bool value) { lock = !value; }
	void SetTurnOffFireTime(int TurnOffFireTime) {this->TurnOffFireTime = TurnOffFireTime;}
	//bool getDangBay() { return this->isBeingFly; }
	//void Phong() { this->isBeingFly = true; }	
	CHOLYWATER();
	void LoadWeapon();
	void SetType(int type) { this->type = type; LoadWeapon(); }
	int GetType() { return type; }
	void SetIsBeingThrown(bool value) { isBeingThrown = value; }
	bool GetIsBeingThrown() { return isBeingThrown; }
	void Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK);
	void SetState(int state);
	void Render_UI();

	void BricksCollision(vector<LPGAMEOBJECT> *Brick );

	void BossMedusaCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossDogCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossFishManCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBigBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void FireBallCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, int nx, int xx, int yy, bool &StartThrown, Grid *map, vector<LPGAMEOBJECT> *Brick, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual bool DoesExist() { return true; };

};