#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Whip.h"
#include "Brick.h"
#include "Axe.h"
#include "BrickOnStair.h"
#include "Knife.h"
#include "debug.h"
#include "Camera.h"
#include "BossMedusa.h"
#include "BossDog.h"
#include "BossBat.h"
#include "BossFishMan.h"
#include "HolyWater.h"
#include "FireBall.h"
#include "BossBigBat.h"
#include "DoubleAttacking.h"
#include "HealthSimon.h"
#include "Bomerang.h"
#include "Water.h"
#include "Grid.h"
#include<fstream>
#include <iostream>
#include "BrickHidden.h"
//#include "Background.h"

#define SCREEN_WIDTH_HALF 180


#define SIMON_ACTTACK_MELEE 50
#define SIMON_ACTTACK_RANGE 51
#define SIMON_ACTTACK_CROUCH_MELEE 52
#define SIMON_ACTTACK_CROUCH_RANGE 53

#define SCREEN_WIDTH_HALF 180

#define SIMON_RIGHT_SPEED       0.2f
#define SIMON_WALKING_SPEED		0.06f
#define SIMON_MOVE		         0.8
#define SIMON_MOVE1		         0.2
#define SIMON_JUMPINGFORWARD_SPEED    0.05f
#define SIMON_ONSTAIR_SPEED		0.035f
#define SIMON_JUMPINGFORWARD_SPEED_Y 0.05f
#define SIMON_JUMP_SPEED_Y		0.2f
#define SIMON_ATTACKING_TIME	420
#define SIMON_BEINGATTACKED_TIME 400
#define SIMON_NOTBEINGATTACKED_TIME    2000
#define SIMON_EFFECT_TIME    1000
#define SIMON_INVISIBLE_TIME    10000
#define SIMON_DELAYSIMON_DOOR_TIME    1500
#define SIMON_DELAY_INTRO_TIME    4000
#define FISHMAN_DELAY_TIME 5000
#define SIMON_TURNATTACK_TIME 200

#define SIMON_DISTANCE_STAIR_X 5

#define SIMON_DISTANCE_STAIR_Y 5

#define SIMON_HEALTHMAX 16
#define SIMON_LIFE_NUMBER 3

#define SIMON_RESETWEAPONS -1


#define SIMON_STATE_IDLE_RIGHT				 0
#define SIMON_STATE_IDLE_LEFT				 1

#define SIMON_STATE_WALKING_RIGHT			 2
#define SIMON_STATE_WALKING_LEFT			 3

#define SIMON_STATE_CROUCH_RIGHT			 4
#define SIMON_STATE_CROUCH_LEFT				 5

#define SIMON_STATE_JUMP_RIGHT				 6
#define SIMON_STATE_JUMP_LEFT				 7

#define SIMON_STATE_ATTACK_RIGHT			 8
#define SIMON_STATE_ATTACK_LEFT				 9

#define SIMON_STATE_CROUCHING_ATTACK_RIGHT	 10
#define SIMON_STATE_CROUCHING_ATTACK_LEFT	 11

#define SIMON_STATE_EFFECT_RIGHT	         12
#define SIMON_STATE_EFFECT_LEFT	             13




#define SIMON_STATE_ONSTAIR_UP_RIGHT	     14
#define SIMON_STATE_ONSTAIR_UP_LEFT	         15


#define SIMON_STATE_ONSTAIR_DOWN_RIGHT		 16
#define SIMON_STATE_ONSTAIR_DOWN_LEFT		 17


#define SIMON_STATE_ONSTAIR_UP_IDLE_RIGHT	 18
#define SIMON_STATE_ONSTAIR_DOWN_IDLE_LEFT	 19

#define SIMON_STATE_ONSTAIR_UP_IDLE_LEFT	 20
#define SIMON_STATE_ONSTAIR_DOWN_IDLE_RIGHT	 21

#define SIMON_STATE_ONSTAIR_UP_ATTACK_RIGHT	 22
#define SIMON_STATE_ONSTAIR_DOWN_ATTACK_LEFT 23

#define SIMON_STATE_ONSTAIR_UP_ATTACK_LEFT  24
#define SIMON_STATE_ONSTAIR_DOWN_ATTACK_RIGHT   25


#define SIMON_STATE_BEINGATTACKED_RIGHT                   26
#define SIMON_STATE_BEINGATTACKED_LEFT                   27

#define SIMON_STATE_IDLE_INTRO                   28

#define SIMON_DIRECTION_UP_STAIR -1

#define SIMON_STATE_DIE                   29
#define SIMON_STATE_KILL_BIGBAT                   30

#define SIMON_STATE_INVISIBLE                  31
#define SIMON_FALLING_STAGE3_Y 140
#define SIMON_WALKING_BBOX_WIDTH  16
#define SIMON_WALKING_BBOX_HEIGHT 30

#define SIMON_STATE_ONSTAIR_UP	 100
#define SIMON_STATE_ONSTAIR_DOWN   200

#define NUMBER_WHIP 0
#define NUMBER_KNIFE 1
#define NUMBER_AXE 2
#define NUMBER_HOLYWATER 3
#define NUMBER_BOMERANG 4
class CSimon : public CGameObject
{
	int TimeUpdate1;
	static CSimon * __instance;
	bool isAttacking;
	int attackingTime;
	int Flicker;
	bool LockFlicker;
	bool TurnoffNhapNhay;
	int DelayIntroTime; 
	int CantBeingAttacked;
	int EfffectInvisibleTime;
	bool BeingAttacked; //bi tan cong
	bool isJumpingForward;
	bool TheendIntro;
	bool EffectGetItem;
	bool EffectInvisible;
	Whip *whip;
	Knife *knife;
	CAXE *axe;
	CHOLYWATER *holywater;
	Bomerang *bomerang;
	vector<HealthSimon*> healthsimon_ani;
	CDoubleAttacking *X2Attacking;
	vector<EffectWater *>water;
	int healthsimon;
	int max_healthsimon;
	//Background *background;
	int WeaponRange;//1:knife,2:axe,3:holy water
	int WeaponMelee;//0:whip

	bool BossCantAttacked; 
	bool GetItem;
	bool StartThrown;
	bool TurnOffCBrick;
	//bool CROUCHING;
	bool IDLE;
	//bool left;
	bool CanGoStair; // Có thể đi cầu thang
	int IdStair; // số hiệu cầu thang
	bool IsOnStair; // đang trên cầu thag
	bool StartWalkingStair; // Bắt đầu đi cầu thang
	bool BeingDownStair; // Đang đi xuống cầu thang, để set sprites
	bool CanUpStair;	//có thể đi lên
	bool CanDownStair; //có thể đi xuống
	int DirectionXStair;
	int DirectionYStair;
	bool ChangeDirection;
	bool BeingAttackRight = false;
	bool MOVE;
	//bool LockMoveLeftDoor; // Lock Move Trước Door
	//bool LockMoveRightDoor;  // Lock Move Sau Door

	int DelayMove = 0;
	bool FlagDelay;
	bool FlagIdle;



	bool FlagStartIntroTime;

	bool MOVENHERIGHT;
	bool HavingCross;

	bool DoubleAttacking;
	bool StopWatch;
	int StopWatchTime;
	bool TheendBigBat;
	int TunrnActack;
	int TypeItems;
	//bool flagGetItem;

	int Life;

	bool GetAxe;
	bool GetKnife;
	bool GetHolyWater;
	bool GetBomerang;
	bool GetBagMoney;


	bool ResetPlay;

	bool ReSetHeathBigBat;
public:
	CSimon();
	void LoadSimon();
	static CSimon * GetInstance();
	void LeverUpWeapons(int vk);
	void RenderWeapons(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK);
	void UpdateWeapons(DWORD dt, vector<LPGAMEOBJECT> *Brick, vector<LPGAMEOBJECT> *colliable_objects,Grid *map);
	int GetTunrnActack();
	void Setweapons();
	void  ResetAttacking();
	void SimonFlicker();
	void SimonMove(int IdStage, float camera_x);
	void SimonIntro(int IdStage);
	//Get
	bool GetReSetHeathBigBat() { return ReSetHeathBigBat; }
	bool GetReSetPlay() { return ResetPlay; }
	bool GetEffectItem() { return GetItem; }
	int GetState() { return state; }
	int GetLife() { return this->Life; }
	int GetTheendBigBat() { return this->TheendBigBat; }
	bool GetBeingAttack() { return BeingAttacked; }
	bool GetMoneyBag() { return this->GetBagMoney; }
	bool GetLockAxe() { return this->axe->getLock(); }
	bool GetLockBomerang() { return this->bomerang->getLock(); }
	bool GetLockRangedweapon() { return this->knife->getLock(); }
	bool GetLockHolyWater() { return this->holywater->getLock(); }
	bool GetIsAttacking() { return isAttacking; }
	bool GetIsOnStair() { return IsOnStair; }
	bool GetCanGoStair() { return CanGoStair; }
	bool GetStartWalkingStair() { return StartWalkingStair; }
	bool getIsJumpingForward() { return isJumpingForward; }
	bool GetTheendIntro() { return TheendIntro; }
	bool GetMOVE() { return MOVE; }
	bool GetCross() { return HavingCross; }
	int GetStopWatch() { return StopWatch; }
	bool GetLockNhapNhay() { return LockFlicker; }
	bool GetDoubleAttacking() { return DoubleAttacking; }
	int GetHealthSimon() { return healthsimon; }


	//Set
	void SetTheEndBigBat(bool TheendBigBat) { this->TheendBigBat = TheendBigBat; }
	void SetDoubleAttacking(bool DoubleAttacking) { this->DoubleAttacking = DoubleAttacking; }
	void SetMoneyBag(int NhatBag) { this->GetBagMoney = NhatBag; }
	void SetBeingAttackRight(bool BeingAttackRight) { this->BeingAttackRight = BeingAttackRight; }
	void SetBeingAttack(bool BeingAttack) { this->BeingAttacked = BeingAttack; }
	void SetInvisible(bool Invisible) { this->BossCantAttacked = Invisible; }	
	void SetLife(int life) { this->Life = life; }
	void SetHealthSimon(int healthsimon) { this->healthsimon = healthsimon; }	
	void SetFlagDelay(bool flag_Delay) { this->FlagDelay = flag_Delay; }
	void SetDelay(int delay) { this->DelayMove = delay; }	
	void SetLockAxe(bool GetAxe) {  this->GetAxe= GetAxe; }
	void SetLockBomerang(bool GetBomerang) { this->GetBomerang = GetBomerang; }
	void SetLockRangedweapon(bool GetKnife) {  this->GetKnife= GetKnife; }
	void SetLockHolyWater(bool GetHolyWater) { this->GetHolyWater = GetHolyWater; }
	void SetState(int state,int TurnAttack);
	void SetWeaponRange(int vk);
	void SetWeaponMelee(int vk);
	void SetIsJumpingForward(bool value) { isJumpingForward = value; }
	void SetIsOnStair(bool value) { IsOnStair = value; }
	void SetTheendIntro(bool value) { TheendIntro = value; }
	void SetMOVE(bool value) { MOVE = value; }
	void Update(DWORD dt, int IdStage, Grid* map,int background_width, int StartThrown, float camera_x, vector<LPGAMEOBJECT> *coObjectsL, vector<LPGAMEOBJECT> *Brick, vector<LPGAMEOBJECT> *Items);
	//Va CHam
	void BricksCollision(vector<LPGAMEOBJECT> *Brick );
	void SetCollisionStair(vector<LPGAMEOBJECT> *Objects);
	void ItemsCollision(vector<LPGAMEOBJECT> *Items);
	void FireBallCollision(vector<LPGAMEOBJECT> *Objects );
	void BossMedusaCollision(vector<LPGAMEOBJECT>* Objects, Grid * map);
	void BossDogCollision(vector<LPGAMEOBJECT> *Objects, Grid * map);
	void BossBatCollision(vector<LPGAMEOBJECT> *Objects, Grid * map);
	void BossFishManCollision(vector<LPGAMEOBJECT> *Objects, Grid * map);
	void BossBigBatCollision(vector<LPGAMEOBJECT> *Objects, Grid * map);

	virtual void Render(float screen_x, int SCREEN_WIDTH);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual bool DoesExist() { return true; };

};