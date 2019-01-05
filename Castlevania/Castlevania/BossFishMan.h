#pragma once

#include "Camera.h"
#include "Brick.h"
#include "GameObject.h"
#include"FireBall.h"
#include "Water.h"
#include <fstream>
#include <iostream>
#include <string>

#define FISHMAN_WALKING_SPEED 0.03f;
#define FISHMAN_STEPUP_Y -0.2;

#define FISHMAN_BBOX_WIDTH 16
#define FISHMAN_BBOX_HEIGHT 32

#define FISHMAN_STATE_IDLE_RIGHT	        0
#define FISHMAN_STATE_IDLE_LEFT	            1
#define FISHMAN_STATE_WALKING_RIGHT			2
#define FISHMAN_STATE_WALKING_LEFT			3
#define FISHMAN_STATE_ATTACKING_RIGHT	    4
#define FISHMAN_STATE_ATTACKING_LEFT	    5
#define FISHMAN_STATE_EFFECT_DIE	        6

#define FISHMAN_ATTACKING_TIME 300
#define FISHMAN_DESTROY_TIME 180
#define FISHMAN_DELAY_ATTACKING1 2500
#define FISHMAN_DELAY_ATTACKING2 5000


#define WATER1_VX 0.0f
#define WATER2_VX 0.02f
#define WATER3_VX 0.03f

#define WATER_STEPUP1 130
#define WATER_STEPUP2 120



#define TYPE_FISHMAN 53

class CBossFishMan : public CGameObject
{
	int attackingTime;
	bool isAttacking=true;
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	bool flag = true;
	bool Right = false;
	bool StartThrown;
	bool isBeingThrown;
	bool IDLE;
	bool flag1;
	bool OnMap;
	bool FirstAttacking;
	FireBall *fireball;
	vector<EffectWater *> Water;
	bool DAttackingRight;// direction attacking right
	void RenderFireBall(float screen_x, int SCREEN_WIDTH, int FISHMAN_STATE,float fishman_x, float fishman_y);
	void UpdateFireBall(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	
public:
	CBossFishMan(int x, int y);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	bool GetDirection() { return this->DAttackingRight; }
	void BricksCollision(vector<LPGAMEOBJECT> *Brick = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *Brick, float simon_x,float simon_y,int stage);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() ;

public:
	virtual void SetState(int state);
};

