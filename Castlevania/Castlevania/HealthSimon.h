#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>

#define HEALTHSIMON_STATE_OFF 0
#define HEALTHSIMON_STATE_ON 1
class HealthSimon : public CGameObject
{
	CTextures * textures;
	int ID_TEX;
	int ani;
public:

	HealthSimon();
	void LoadHealth();
	void Render(int type);
	virtual void Update(DWORD dt, int nx, int xx, int yy, bool &StartThrown, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual bool DoesExist() { return true; };
};