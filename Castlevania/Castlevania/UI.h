#pragma once
#include "Camera.h"
#include"GameObject.h"
#include <vector>
#include"Number.h"

#define SCORE100 100
#define SCORE200 200
#define SCORE_MINUS_TIME 20
#define NUMBERATTACKING_MINUS_TIME 100
#define FIRSTSCORE 0
#define FIRSTTIME 300
#define FIRSTLIFE 3
#define FIRSTSTAGE 0
#define FIRSTNUMBERATTACKING 5

class UI : public CGameObject
{

	vector<Number*> Score_ani;
	int Score;



	vector<Number*> Time_ani;
	int Time;

	vector<Number*> LanDanhVuKhiDatBiet_ani;
	int NumberOfAttacking;

	vector<Number*> Life_ani;
	int Life;

	vector<Number*> Stage_ani;
	int Stage;

	int CurrentTime;
public:
	UI(int x, int y);
	int GetScore() { return this->Score; }
	void SetScore(int Score) { this -> Score += Score; }
	int GetTurnAttack() { return this->NumberOfAttacking; }
	int GetTimeLife() { return this->Time; }
	void SetTimeLife(int Time) { this->Time += Time; }
	void UpDateNumber(vector<Number*>&number,int num, int &ChaNum);
	virtual void Render(float camera_x, int SCREEN_WIDTH);
	void Update(DWORD dt, int Score, int TurnAttack,int Life,int Stage, bool BigBatDie);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};