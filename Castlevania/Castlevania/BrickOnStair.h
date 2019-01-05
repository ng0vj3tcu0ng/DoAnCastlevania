#pragma once
#include "GameObject.h"
#include "Camera.h"
#include"Textures.h"
#define BRICKONSTAIR_BBOX_WIDTH 16
#define BRICKONSTAIR_BBOX_HEIGHT 2

#define TYPE_ONLYUP 0
#define TYPE_ONLYDOWN 1

#define TYPE_BRICK_ON_STAIR 56

#define ID_TEX_BRICKSTAIR       100
#define BRICKSTAIR_TEXTURE_PATH		L"Objects\\Brick.png"
#define BRICKSTAIRTEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(0, 128, 128)

class CBrickOnStair : public CGameObject
{
	int TypeStair;
	int DirectionUpOrDown;
	float left, top, right, bottom;
	int Id;
	int DirectionXUp;
	int DirectionY;
public:
	//void setCap
	CBrickOnStair(int x, int y, int TypeStair, int DirectionUpOrDown,int DirectionXUp);
	void SetDirectionXUp(int HuongDiLenh) { this->DirectionXUp = HuongDiLenh; }
	int GetDirectionXUp() { return this->DirectionXUp; }
	void SetDirectionY(int HuongDiLenh) { this->DirectionY = HuongDiLenh; }
	int GetDirectionY() { return this->DirectionY; }
	void SetID(int id) { this->Id = id; }
	int GetID() { return this->Id; }
	int GetTypeStair() { return this->TypeStair; }
	void SetTypeStari(const int &TypeStair) { this->TypeStair = TypeStair; }
	int GetDirectionUpOrDown() { return this->DirectionUpOrDown; }
	void SetDirectionUpOrDown(const int &DirectionUpOrDown) { this->DirectionUpOrDown = DirectionUpOrDown; }
	virtual void Render(float screen_x, int SCREEN_WIDTH);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};