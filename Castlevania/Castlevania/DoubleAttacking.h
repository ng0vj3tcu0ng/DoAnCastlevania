#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>

class CDoubleAttacking : public CGameObject
{
	CTextures * textures;
	int ID_TEX;

public:

	
	CDoubleAttacking();
	void LoadIt();
	void Render_UI();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, int nx, int xx, int yy, bool &StartThrown, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual bool DoesExist() { return true; };

};