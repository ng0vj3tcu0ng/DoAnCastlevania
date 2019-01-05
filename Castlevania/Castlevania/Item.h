#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Camera.h"
#include "debug.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>
#define ITEM_TYPE_WHIP_UPGRADE	180
#define ITEM_TYPE_DAGGER		181
#define ITEM_TYPE_HEART			182
#define ITEM_TYPE_MONEY_BAG		183
#define ITEM_TYPE_HEARTS		184	
#define ITEM_TYPE_AXE		    185
#define ITEM_TYPE_HOLYWATER		186
#define ITEM_TYPE_CROSS         187
#define ITEM_TYPE_INVINCIBILITY  188
#define ITEM_TYPE_JEWEL          189
#define ITEM_TYPE_DOUBLEATTACK   190
#define ITEM_TYPE_POTROAST     191
#define ITEM_TYPE_STOPWATCH    192
#define ITEM_TYPE_BOMERANG    193

#define ITEM_TYPE_BBOX_WIDTH	16
#define ITEM_TYPE_BBOX_HEIGHT	16
#define ITEM_TYPE_BBOXS_WIDTH	12
#define ITEM_TYPE_BBOXS_HEIGHT	10
#define ITEM_TYPE_BBOXSS_WIDTH	8
#define ITEM_TYPE_BBOXSS_HEIGHT	8

#define PI 3.14159265
#define ITEM_VY 0.03f


class Item :public CGameObject
{
	bool CollisionBrick;
	int FallingStyle;
	bool Destroy;
public:
	Item(int x, int y, int type,int FallingStyle);
	int GetType() { return this->Type; }
	void SetDestroy(bool Destroy) { this->Destroy = Destroy; }
	void SetType(const int &Type) { this->Type = Type; }
	void SetFallingStyle(int FallingStyle) { this->FallingStyle = FallingStyle; }
	void BricksCollision(vector<LPGAMEOBJECT> *Brick = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() { return Destroy; };

};