#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Brick.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>

#define DOG_WALKING_SPEED 0.08f;		

#define DOG_BBOX_WIDTH 32
#define DOG_BBOX_HEIGHT 16

#define DOG_STATE_IDLE_RIGHT	        0
#define DOG_STATE_IDLE_LEFT	            1
#define DOG_STATE_WALKING_RIGHT			2
#define DOG_STATE_WALKING_LEFT			3
#define DOG_STATE_FALLING			    4
#define DOG_STATE_EFFECT		        5

#define DOG_STATE_DISDESTROY 0
#define DOG_STATE_DESTROY 1

#define DOG_DESTROY_TIME 500


#define TYPE_DOG 52

#define DOG_DISTANCE_UPDATE_RENDER 100

class CBossDog : public CGameObject
{
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	bool flag;
	bool flag1;
	bool Active;
	bool OnScreen;
	bool ChangeDirec;
public:
	CBossDog(int x, int y);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	void BricksCollision(vector<LPGAMEOBJECT> *Brick = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *Brick, float simon_x,float simon_y,int state);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() ;

public:
	virtual void SetState(int state);
};

