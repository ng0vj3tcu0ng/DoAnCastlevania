#pragma once
#include <Windows.h>
#include "Point.h"
#include "debug.h"

#define CAMERA_MOVE 1.5

#define STAGEINTRO 0
#define STAGE1 1  //Canh ngoai san
#define STAGE2 2  //Canh trong lau dai
#define STAGE3 3  //Canh duoi ham
class Camera
{
	static Camera *__instance;

	float x, y;
	int Background_Width;
	int Screen_Width;
	int Start=0;
	bool OPENDOOR=false ;
	bool CameraMove = false; // camera di chuyen khi simon gan Door
public:
	static Camera *GetInstance();
	int GetStart() { return this->Start; }
	bool GetCameraMove() { return this->CameraMove; }
	void SetStart(int Start) { this->Start = Start; }
	void SetX(int x) { this->x = x; }
	int GetOpenDoor() { return this->OPENDOOR; }
	void SetWidth(int Background_Width, int SCREEN_WIDTH) { this->Background_Width = Background_Width; this->Screen_Width = SCREEN_WIDTH;}
	float GetX() { return x; }
	float GetY() { return y; }
	int GetBackgroundWidth() { return Background_Width; }
	int GetScreenWidth() { return Screen_Width; }
	Point PositionOnCamera(float x, float y);
	void Update(int SCREEN_WIDTH, int background_width, float simon_x,float simon_y, bool MOVE, int IdStage);
};