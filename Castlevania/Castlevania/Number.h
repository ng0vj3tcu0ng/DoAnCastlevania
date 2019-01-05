
#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>

#define Number_STATE_OFF 0
#define Number_STATE_ON 1

class Number : public CGameObject
{
	static Number * __instance;
	CTextures * textures;
	int ID_TEX;
	int value;

public:
	int GetValue() { return this->value; }
	void SetValue(int value) { this->value = value; }
	Number();
	void LoadNumber();
	void Render();
	virtual void Update(DWORD dt, int nx, int xx, int yy, bool &StartThrown, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual bool DoesExist() { return true; };
};

