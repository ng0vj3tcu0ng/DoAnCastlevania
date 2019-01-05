#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

#include "Sprites.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define GRAVITY		0.0005f
#define GRAVITYDOG		0.0002f
#define GRAVITYBWALL		0.0005f
#define GRAVITYWATER		0.0005f
#define GRAVITYMEDUSA		0.0005f
#define GRAVITYFISHMAN    0.0007f
#define GRAVITYHOLYWATER    0.0005f
#define GRAVITYAXE		0.0005f
#define GRAVITYITEMS		0.0005f

#define ID_ACTION_TEXTURES 0
#define ID_ACTION_SPRITES 100
#define ID_ACTION_ANI 200

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
protected:
	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;
	int ny;
	int nx;
	int Type;
	int state;
	bool isFalling;
	int currentID;
	bool Destroy;
	DWORD dt;

	vector<LPANIMATION> animations;

public:
	void SetDestroy(bool Destroy) { this->Destroy = Destroy; }
	bool GetDestroy() { return this->Destroy; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetCurrentID(int currentID) { this->currentID = currentID; }
	int GetCurrentID() { return currentID; }
	int GetType() { return this->Type; }
	void SetType(const int &Type) { this->Type = Type; }
	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }
	void SetDirection(int nx) { this->nx = nx; }
	int GetDirection() { return this->nx; }
	void SetDirectionY(int nx) { this->ny = ny; }
	int GetDirectionY() { return this->ny; }
	bool GetIsFalling() { return isFalling; }

	float GetX() { return x; }
	float GetY() { return y; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	LPCWSTR convStringToLPCWSTR(string String);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(float screen_x, int SCREEN_WIDTH) = 0;
	virtual bool DoesExist() = 0;
	~CGameObject();
};