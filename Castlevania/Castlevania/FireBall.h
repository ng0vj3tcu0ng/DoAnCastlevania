#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Fireball.h"
#include "debug.h"
#include <fstream>
#include <iostream>
#include <string>
#define FIREBALL_BBOX_WIDTH 2
#define FIREBALL_BBOX_HEIGHT 5

#define FIREBALL_SPEED_X 0.1f
#define FIREBALL_SPEED_Y 0.0f

#define FIREBALL_STATE_THROW_RIGHT  0
#define FIREBALL_STATE_THROW_LEFT   1
#define FIREBALL_STATE_EFFECT  2

#define TYPE_FIREBALL 79


#define FIREBALL_DESTROY_TIME 200
class FireBall : public CGameObject
{
	CTextures * textures;
	int ID_TEX;
	bool isBeingThrown; 
	bool Normal; // binh thuong
	int StartDestroy; // bat dau pha huy

	//bool isBeingFly; // dang bay

public:	
	FireBall();
	//bool getDangBay() { return this->isBeingFly; }
	//void Phong() { this->isBeingFly = true; }
	void LoadWeapon();
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	void SetIsBeingThrown(bool value) { isBeingThrown = value; }
	bool GetIsBeingThrown() { return isBeingThrown; }
	void Render(float screen_x, int SCREEN_WIDTH, int FISHMAN_STATE, float fishman_x, float fishman_y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, int nx, int xx,bool &Direction,vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual bool DoesExist() { return true; };

};