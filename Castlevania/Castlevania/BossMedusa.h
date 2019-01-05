#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Brick.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>

#define MEDUSA_WALKING_SPEED 0.08f;

#define MEDUSA_BBOX_WIDTH 17
#define MEDUSA_BBOX_HEIGHT 32

#define MEDUSA_STATE_IDLE		         0
#define MEDUSA_STATE_WALKING_RIGHT			1
#define MEDUSA_STATE_WALKING_LEFT			2
#define MEDUSA_STATE_EFFECT		        3

#define MEDUSA_STATE_DISDESTROY 0
#define MEDUSA_STATE_DESTROY 1

#define MEDUSA_DESTROY_TIME    180

#define TYPE_MEDUSA 54

#define MEDUSA_DISTANCE_UPDATE_RENDER 300



class CBossMedusa : public CGameObject
{
	//int type;
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	bool flag;
	bool OnScreen;
	bool Active;
	bool Delete;
	bool First;
public:
	CBossMedusa(int x, int y);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	void BricksCollision(vector<LPGAMEOBJECT> *Brick = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *Brick,float camera_x,int state,float simon_x,float simon_y);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() ;

public:
	virtual void SetState(int state);
};