#pragma once

#include "Camera.h"
#include "GameObject.h"
#include"Textures.h"
//#include "debug.h"
#include <fstream>
#include <iostream>
#include <string>
#define BAT_WALKING_SPEED 0.06f	

#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 16	

#define BAT_STATE_IDLE	                0
#define BAT_STATE_FLYING_RIGHT			1
#define BAT_STATE_FLYING_LEFT			2
#define BAT_STATE_EFFECT			    3


#define BAT_STATE_DISDESTROY 0
#define BAT_STATE_DESTROY 1

#define BAT_DESTROY_TIME 180

#define PI 3.14159265
#define BAT_FLYING_SPEEDY 0.04f

#define TYPE_BAT 50

class CBossBat : public CGameObject
{
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	bool OnScreen;



public:
	CBossBat(int x, int y);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, float camera_x,int state,float simon_x,float simon_y);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() ;

public:
	virtual void SetState(int state);
};

