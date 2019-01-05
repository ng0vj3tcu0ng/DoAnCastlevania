#pragma once
#include "HealthBoss.h"
#include "GameObject.h"
#include "Camera.h"
#include "debug.h"
#include"Textures.h"
#include <fstream>
#include <iostream>
#include <string>


#define BIGBAT_STATE_IDLE	       0
#define BIGBAT_STATE_FLYING	       1
#define BIGBAT_STATE_BEATTACKING   2
#define BIGBAT_STATE_EFFECT	       3

#define BIGBAT_BBOX_WIDTH	16
#define BIGBAT_BBOX_HEIGHT	23

#define TYPE_BIGBAT 51

#define BIGBAT_DESTROY_TIME 2000
#define BIGBAT_BEINGATTACKING_TIME 500

#define BIGBAT_FLYING_TIME1 1000
#define BIGBAT_FLYING_TIME2 2000

#define BIGBAT_DISTANCE_ACTIVE 100
#define BIGBAT_HEALTHMAX 16



class CBossBigBat : public CGameObject
{
	bool Normal; // binh thuong
	int status; //Trang Thai
	int itemType; 
	float newVx;
	float newVy;
	float XDes, YDes;
	int Blood;
	int StartDestroy;
	bool BeingAttacking;
	bool Active;
	int TurnOffAttacking;
	int timerandom;
	vector<HealthBoss *> healthB_ani;
	int max_healthboss;
	int DoubleAttacking;
	bool flag;
	bool ReSetHeath;
public:
	CBossBigBat(float x, float y,int itemType);
	void SetMaxHeath(int max_healthboss) {this->max_healthboss = max_healthboss;}
	void SetNormal(bool Normal) { this->Normal = Normal; }
	bool GetNormal() { return this->Normal; }
	void SetReSetHeath(bool ReSetHeath) { this->ReSetHeath = ReSetHeath; }
	void SetBeingAttacking(bool BeingAttacking) { this->BeingAttacking = BeingAttacking; }
	void SetBlood(int Blood) { this->Blood = Blood; }
	void SetDoubleAttacking(int DoubleAttacking) { this->DoubleAttacking = DoubleAttacking; }
	int GetBlood() { return Blood; }
	int GetItemType() { return itemType; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, int SCREEN_WIDTH, float camera_x, float simon_x, float simon_y,bool DoubleAttack,bool ReSetHeath);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	virtual bool DoesExist() { return true; };
public:
	virtual void SetState(int state);
};