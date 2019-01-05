#pragma once
#include "GameObject.h"
class CBrick : public CGameObject
{
	float left, top, right, bottom;
	bool Destroy;
public:
	CBrick();
	CBrick(float left, float top, float right, float bottom);
	bool GetDestroy() { return this->Destroy; }
	void SetDestroy(bool Destroy) { this->Destroy = Destroy; }
	virtual void Render(float screen_x, int SCREEN_WIDTH) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};