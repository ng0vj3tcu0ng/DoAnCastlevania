#pragma once
#include "Camera.h"
#include"GameObject.h"
#include <vector>
#include "BreakingWall.h"
#include <string>
#define BRICKHIDDEN_BBOX_WIDTH  8
#define BRICKHIDDEN_BBOX_HEIGHT 8

#define BRICKHIDDEN_STATE_NORMAL 0
#define BRICKHIDDEN_STATE_DESTROY 1

#define BRICKHIDDEN_DESTROY_TIME    1000

#define BRICKHIDDEN_TYPE_0    0
#define BRICKHIDDEN_TYPE_1    1

#define BREAKINGWALL1_VX -0.02f
#define BREAKINGWALL2_VX 0.01f
#define BREAKINGWALL3_VX 0.02f
#define BREAKINGWALL4_VX 0.03f

#define ID_TEX_HIDDENBRICK    160
#define HIDDENBRICK_TEXTURE_PATH		L"Objects\\BrickIteam.png"
#define HIDDENBRICK_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(34, 177, 76)

#define TYPE_BRICKHIDDEN 55

class BrickHidden : public CGameObject
{
	int type;
	int itemType;
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	vector<EffectBWall*> BreakingWall;
	int BrickDelete;
//	Camera *camera;
public:
	BrickHidden(int x, int y, int itemType,  int HiddenBrickType,int BrickDelete);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	int GetBrickDelete() { return this->BrickDelete; }
	bool GetNormal() { return this->Normal; }
	int GetItemType() { return itemType; }
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};