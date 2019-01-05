#pragma once
#include "Camera.h"
#include"GameObject.h"
#include <vector>

#define MOVE_X1 0.15
#define MOVE_X2 0.1
#define MOVE_Y 0.1

class IntroSource : public CGameObject
{

public:
	IntroSource(int x, int y);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};