#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Candle.h"
#include "Item.h"
#include"BossMedusa.h"
#include "BossDog.h"
#include "BossBat.h"
#include "BossFishMan.h"
#include "BossBigBat.h"
#include"debug.h"
#include "FireBall.h"
#include "Grid.h"
#define BOMERANG_BBOX_WIDTH 17
#define BOMERANG_BBOX_HEIGHT 8

#define BOMERANG_SPEED_X 0.12f
#define BOMERANG_SPEED_Y 0.0f

#define BOMERANG_STATE_IDLE		 0
#define BOMERANG_STATE_THROW_RIGHT  1
#define BOMERANG_STATE_THROW_LEFT   2

#define SCREEN_WIDTH_HALF 180

#define BOMERANG_RESET_X 120
class Bomerang : public CGameObject
{
	CTextures * textures;
	int ID_TEX;
	int type = 0;
	bool isBeingThrown; // dang nem
	bool lock;
	bool isBeingFly; // dang bay
	bool LockNx;
public:
	bool getLock() { return this->lock; }
	void Unlock(bool value) { this->lock = !value; }
	//bool getDangBay() { return this->isBeingFly; }
	//void Phong() { this->isBeingFly = true; }
	
	Bomerang();
	void LoadWeapon();
	void SetType(int type) { this->type = type; LoadWeapon(); }
	int GetType() { return type; }
	void SetIsBeingThrown(bool value) { isBeingThrown = value; }
	bool GetIsBeingThrown() { return isBeingThrown; }
	void Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK);

	void CandelCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossMedusaCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossDogCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossFishManCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BossBigBatCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);
	void FireBallCollision(Grid *Map, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Render_UI();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, int nx, int simon_x, bool &StartThrown,Grid *map, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual bool DoesExist() { return true; };

};