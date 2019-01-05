#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Debug.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
#include <string>
#define DOOR_BBOX_WIDTH 1
#define DOOR_BBOX_HEIGHT 1

#define DOOR_STATE_IDLE 0
#define DOOR_STATE_OPEN 1
#define DOOR_STATE_CLOSE 2

#define DOOR_TIME_OPENCLOSE 300




class CDoor : public CGameObject
{
	//int ain;
	bool FlagOpen;
	//bool flag_Opening;
	bool FlagClose;
	//bool flag_Closing;
	int now;
	bool LockClose;
	bool ChangeStatusDoor;
public:
	CDoor(int x, int y);
	void SetState(int state);
	bool GetClose() { return this->FlagClose; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void Render(float simon_x, int camera_x);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual bool DoesExist() { return true; };

};