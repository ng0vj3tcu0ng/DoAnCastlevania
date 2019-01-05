#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include "debug.h"
#include "Sprites.h"
#include "Textures.h"
#include "GameObject.h"
#include "Brick.h"
#include "Camera.h"
#include <iostream>

#define STAGEINTRO 0
#define STAGE1 1  //Canh ngoai san
#define STAGE2 2  //Canh trong lau dai
#define STAGE3 3  //Canh duoi ham

using namespace std;
class Door {
public:
	int x, y, id;
	int MapNext, x_next, y_next;
};
class Background
{
protected:
	static Background * __instance;
	float x,y;
	int background_width;
	int screen_width;
	//vector<LPANIMATION> animations;
	int **Map;
	int w, h;
	vector<Door> door;
	bool NextMap;
	int Stage;
	int MapNext;
	int NewXSimon, NewYSimon;
	Camera *camera;
	//bool** Brick;
	//width,height,
	//Map=new int[width*height];
public:
	static Background * GetInstance();
	static Background * GetInstance(int stage,int ID_TEX_BACKGROUND, LPCWSTR BACKGROUND_TEXTURE_PATH, D3DCOLOR BACKGROUND_TEXTURE_BACKGROUND_COLOR, int SCREEN_WIDTH, LPCWSTR LinkMap);
	Background(int stage,int ID_TEX_BACKGROUND, LPCWSTR BACKGROUND_TEXTURE_PATH, D3DCOLOR BACKGROUND_TEXTURE_BACKGROUND_COLOR, int SCREEN_WIDTH, LPCWSTR LinkMap);
	/*void AddAnimation(int aniID);*/
	void setWidth(int background_width, int SCREEN_WIDTH) { this->background_width = background_width; this->screen_width = SCREEN_WIDTH; }
	float GetX() { return x; }
	int getWidth() { return background_width; }
	int GetStage() { return this->Stage; }
	void setStage(int Stage ) { this->Stage = Stage;  }
	int GetScreenWidth() { return screen_width; }
	void Update(float Simon_x, float simon_y, vector<LPGAMEOBJECT>* Brick, float camera_x);
	bool GetNextMap() { return this->NextMap; }
	void setNextMap(bool NextMap) { this->NextMap = NextMap; }
	int getNewXSimon() { return this->NewXSimon; }
	int getNewYSimon() { return this->NewYSimon; }
	void setNewXSimon(int NewXSimon) { this->NewXSimon = NewXSimon; }
	void setNewYSimon(int NewYSimon) { this->NewYSimon = NewYSimon; }
	void Render(float camera_x);
};