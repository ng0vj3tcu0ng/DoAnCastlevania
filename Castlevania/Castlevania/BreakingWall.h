#pragma once
#include "GameObject.h"
#include "Textures.h"
//#include "debug.h"
#include <fstream>
#include <iostream>
#include <string>
#define BREAKING_BBOX_WIDTH 7
#define BREAKING_BBOX_HEIGHT 7

#define BREAKING_SPEED_X 0.1f
#define BREAKING_STEPUP_Y 0.1

class EffectBWall : public CGameObject
{
	CTextures * textures;
	int ID_TEX;
	bool isFalling;
	bool flag_Start;
	int StepUp;
	int StarThrown;
public:
	EffectBWall();
	void Start(float vx, int x, int y, int StepUp);
	void LoadEffect();
	void SetIsFalling(bool value) { isFalling = value; }
	bool GetIsFalling() { return isFalling; }
	void Render(float screen_x, int SCREEN_WIDTH, float fishman_x, float fishman_y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(float camera_x, int SCREEN_WIDTH) {};
	virtual bool DoesExist() { return true; };

};