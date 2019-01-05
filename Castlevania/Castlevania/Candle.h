#pragma once
#include "Camera.h"
#include"GameObject.h"
#include <vector>
#include <fstream>
#include <iostream>
#include<string>
#define CANDLE_BBOX_WIDTH  8
#define CANDLE_BBOX_HEIGHT 25

#define TYPE_CANDLE 60

#define CANDLE_TYPE_SMALL 0
#define CANDLE_TYPE_BIG 1


#define CANDLE_STATE_NORMAL 0
#define CANDLE_STATE_DESTROY 1

#define CANDLE_DESTROY_TIME    500
#define ID_TEX_CANDLES			30


class Candle : public CGameObject
{
	int type;
	int itemType;
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy
	bool OnScreen;
//	Camera *camera;
public:
	Candle(int x, int y, int itemType, int CandleType);
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	int GetItemType() { return itemType; }
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() ;

};