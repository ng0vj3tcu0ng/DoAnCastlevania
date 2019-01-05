#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <iostream>
//#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Brick.h"
#include "Background.h"
#include "Candle.h"
#include "Whip.h"
#include "Item.h"
#include "knife.h"
#include "Axe.h"
#include "BossMedusa.h"
#include "BrickOnStair.h"
#include "BossDog.h"
#include "BossBat.h"
#include "BossFishMan.h"
#include "HolyWater.h"
#include "CDoor.h"
#include "FireBall.h"
#include "IntroSource.h"
#include "UI.h"
#include "BrickHidden.h"
#include "BossBigBat.h"

#include "Grid.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define SCREEN_WIDTH	360
#define SCREEN_HEIGHT	360
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR1 D3DCOLOR_XRGB(245, 245, 245)
#define STAGEINTRO 0
#define STAGE1 1  //Canh ngoai san
#define STAGE2 2  //Canh trong lau dai
#define STAGE3 3  //Canh duoi ham

#define MAP2_TEXTURE_PATH	    L"TiledMap\\Stage 2 Source.png"
#define MAP3_TEXTURE_PATH	    L"TiledMap\\Stage 3 Source.png"
#define MAP1_TEXTURE_PATH	    L"TiledMap\\Stage 1 Source.png"
#define MAPINTRO_TEXTURE_PATH	  L"Backgrounds\\intro.png"
#define MAPINTRO_TXT_PATH		 L"Backgrounds\\stageIntroM.txt"	

#define STAGE1_TXT_PATH		      L"TiledMap\\stage1M.txt"	
#define STAGE2_TXT_PATH		       L"TiledMap\\stage2M.txt"	
#define STAGE3_TXT_PATH		      L"TiledMap\\stage3M.txt"	


#define ID_TEX_BACKGROUND		20
#define ID_TEX_SIMON			10
#define SIMON_TEXTURE_PATH			L"Simon\\Simon.png"
#define SIMON_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(0, 128, 128)

#define MAX_FRAME_RATE 300




#define INTROSOURCE_TEXTURE_PATH	        L"Backgrounds\\Introsource.png" 
#define INTROSOURCE_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(128, 0, 0)
#define ID_TEX_INTROSOURCE     140
#define INTROSOURCE_INFO_PATH           L"Backgrounds\\IntroSource.txt"

#define UI_TEXTURE_PATH	        L"Backgrounds\\UI.png" 
#define UI_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(5, 5, 5)
#define ID_TEX_UI     150


#define STAGE1_INFO_PATH           L"Backgrounds\\1Objects1Info.txt"
#define STAGE2_INFO_PATH           L"Backgrounds\\2Objects2Info.txt"
#define STAGE3_INFO_PATH           L"Backgrounds\\3Objects3Info.txt"

#define STAGE_INFO_PATH           L"Backgrounds\\11StageInfo.txt"


#define SMALLCANDLES 0
#define BIGCANDLES 1
#define BRICKONSTAIR 2
#define BRICK 3
#define MEDUSA 4
#define DOG 5
#define BAT	 6
#define BIGBAT 7
#define HIDDENBRICK 8
#define FISHMAN 9
#define DOOR 10

#define SCORE100 100
#define SCORE200 200
#define SCORE300 300
#define SCORE700 700
#define SCORE3000 3000

Item *item;
CGame *game;
FireBall *fireball;
CSimon *simon;
CBossMedusa *bossmedusa;
CBossDog *bossdog;
CBossBat *bossbat;
CBossBigBat *bossbigbat;
CBossFishMan *bossfishman;
Background *background;
Whip *whip;
CBrick *brick;
CBrickOnStair *brickonstair;
Knife *knife;
CAXE *axe;
CHOLYWATER *holywater;
vector <LPGAMEOBJECT> objects;
vector <LPGAMEOBJECT> Brick;
vector <LPGAMEOBJECT> Items;
vector <CDoor*> Door;

Camera *camera = Camera::GetInstance();
UI *ui;
Grid *Map;
class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (background->GetStage() == 0) return;
	if (simon->GetMOVE()) return;
	if (simon->GetIsAttacking()) return;
	if (simon->GetTheendBigBat()) return;
	if (simon->GetBeingAttack()) return;
	if (simon->GetLife() == 0) return;

	if (KeyCode == DIK_S)
		if (game->IsKeyDown(DIK_L) || game->IsKeyDown(DIK_J)) simon->SetIsJumpingForward(true);
	// Handling Crouching Attack
	if (KeyCode == DIK_A)
	{
		if (!game->IsKeyDown(DIK_I))
		{
			simon->SetWeaponMelee(NUMBER_WHIP);
			simon->SetState(SIMON_STATE_ATTACK_RIGHT, 0); 
				
		}
		if (game->IsKeyDown(DIK_K))
		{
			simon->SetWeaponMelee(NUMBER_WHIP);
			simon->SetState(SIMON_ACTTACK_CROUCH_MELEE, 0);
			return;
		}
	}
	
	/*if (KeyCode == DIK_A)
		
		if (game->IsKeyDown(DIK_I))
		{
			if (!simon->GetLockRangedweapon()) {
				simon->SetWeaponRange(NUMBER_KNIFE);
			}
			else
			{
				if (!simon->GetLockAxe())
				{
					simon->SetWeaponRange(NUMBER_AXE);
				}
				else
				{
					if (!simon->GetLockHolyWater())
					{
						simon->SetWeaponRange(NUMBER_HOLYWATER);
					}
					else
					{
						if (!simon->GetLockBomerang())
						{
							simon->SetWeaponRange(NUMBER_BOMERANG);

						}
					}
				}
			}
			simon->SetState(SIMON_STATE_ATTACK_RIGHT, ui->GetTurnAttack());
			return;
		}*/
	//if (KeyCode == DIK_A/* && !rangedWeapon->GetIsBeingThrown()*/)
	//	if (game->IsKeyDown(DIK_C))
	//	{
	//		simon->SetVuKhi(NUMBER_AXE);
	//		simon->SetState(SIMON_STATE_CROUCHING_ATTACK_RIGHT);
	//		return;
	//	}
	switch (KeyCode)
	{
	case DIK_S:
		simon->SetState(SIMON_STATE_JUMP_RIGHT, 0);
		break;
	//case DIK_A:
	//	simon->SetWeaponMelee(NUMBER_WHIP);
	//	simon->SetState(SIMON_ACTTACK_MELEE, 0);
	//	break;
	case DIK_A:
		{
			if (game->IsKeyDown(DIK_I))
			{

				if (!simon->GetLockRangedweapon()) {
					simon->SetWeaponRange(NUMBER_KNIFE);
				}
				else
				{
					if (!simon->GetLockAxe())
					{
						simon->SetWeaponRange(NUMBER_AXE);
					}
					else
					{
						if (!simon->GetLockHolyWater())
						{
							simon->SetWeaponRange(NUMBER_HOLYWATER);
						}
						else
						{
							if (!simon->GetLockBomerang())
							{
								simon->SetWeaponRange(NUMBER_BOMERANG);

							}
						}
					}
				}

				simon->SetState(SIMON_ACTTACK_RANGE, ui->GetTurnAttack());
			}
		}
	/*	else
		{
			simon->SetWeaponMelee(NUMBER_WHIP);
			simon->SetState(SIMON_STATE_ATTACK_RIGHT,0);
			break; 
		}*/
		break;

		
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}



LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		//OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

/*
	Load all game resources.
*/
void LoadBackground(int IdStage)
{
	switch (IdStage)
	{
	case STAGEINTRO:
		background = Background::GetInstance(STAGEINTRO, ID_TEX_BACKGROUND, MAPINTRO_TEXTURE_PATH, NULL, SCREEN_WIDTH, NULL);
		break;
	case STAGE1:
		background = Background::GetInstance(STAGE1, ID_TEX_BACKGROUND, MAP1_TEXTURE_PATH, NULL, SCREEN_WIDTH, STAGE1_TXT_PATH);
		break;
	case STAGE2:
		background = Background::GetInstance(STAGE2, ID_TEX_BACKGROUND, MAP2_TEXTURE_PATH, BACKGROUND_COLOR, SCREEN_WIDTH, STAGE2_TXT_PATH);
		break;
	case STAGE3:
		background = Background::GetInstance(STAGE3, ID_TEX_BACKGROUND, MAP3_TEXTURE_PATH, NULL, SCREEN_WIDTH, STAGE3_TXT_PATH);
		break;
	default:
		break;
	}
}
void LoadIntroSource()
{
	simon->SetPosition(230.0f, 125);
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_INTROSOURCE, INTROSOURCE_TEXTURE_PATH, INTROSOURCE_TEXTURE_BACKGROUND_COLOR);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texIntroSource = textures->Get(ID_TEX_INTROSOURCE);

	// Bat type 0
	sprites->Add(30300, 0, 0, 9, 7, texIntroSource);
	sprites->Add(30301, 10, 0, 19, 7, texIntroSource);

	sprites->Add(30302, 0, 8, 32, 21, texIntroSource);

	LPANIMATION ani;
	//Bat intro
	ani = new CAnimation(50);
	ani->Add(30300);
	ani->Add(30301);
	animations->Add(330, ani);
	// Dia Bay intro
	ani = new CAnimation(50);
	ani->Add(30302);
	animations->Add(331, ani);
	ifstream in;
	int n;
	int x = 0, y = 0, direction = 0;

	in.open(INTROSOURCE_INFO_PATH);

	// Read type 0
	in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> x >> y >> direction;
		IntroSource *introsource = new IntroSource(x, y);
		if (i == 2)
		{
			introsource->AddAnimation(331);
		}
		else introsource->AddAnimation(330);
		introsource->SetDirection(direction);
		objects.push_back(introsource);
	}
	in.close();
}

void LoadUI()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_UI, UI_TEXTURE_PATH, UI_TEXTURE_BACKGROUND_COLOR);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texIntroSource = textures->Get(ID_TEX_UI);

	// UI type 0
	sprites->Add(11000, 0, 0, 255, 39, texIntroSource);


	LPANIMATION ani;
	//Bat intro
	ani = new CAnimation(100);
	ani->Add(11000);
	animations->Add(110, ani);
	ui = new UI(0, 0);
	ui->AddAnimation(110);
	//objects.push_back(ui);
}
void CreateCandel(int x, int y, int item, int typeCandel) {
	Candle *candle = new Candle(x, y, item, typeCandel);
	objects.push_back(candle);
}
void CreateBrick(int left, int right, int top, int bottom) {
	CBrick *brick = new CBrick(left, top, right, bottom);
	Brick.push_back(brick);
}
void CreateMedusa(int x, int y) {
	CBossMedusa* bossmedusa = new CBossMedusa(x, y);
	objects.push_back(bossmedusa);
}
void CreateDog(int x, int y) {
	CBossDog* bossdog = new CBossDog(x, y);
	objects.push_back(bossdog);
}
void CreateBat(int x, int y) {
	CBossBat* bossbat = new CBossBat(x, y);
	objects.push_back(bossbat);
}
void CreateBigBat(int x, int y, int item) {
	CBossBigBat* bossbigbat = new CBossBigBat(x, y, item);
	objects.push_back(bossbigbat);
}
void CreateHiddenBrick(int x, int y, int item, int typeHiddenBrick, int BrickDelete)
{
	BrickHidden *hiddenbrick = new BrickHidden(x, y, item, typeHiddenBrick, BrickDelete);
	objects.push_back(hiddenbrick);
}
void CreateBrickOnStair(int x, int y, int TypeStair, int DirectionUpOrDown, int DirectionXUp)
{
	CBrickOnStair *brickonstair = new CBrickOnStair(x, y, TypeStair, DirectionUpOrDown, DirectionXUp);
	objects.push_back(brickonstair);
}
void CreateFishMan(int x, int y, int z)
{
	CBossFishMan* bossfishman = new CBossFishMan(x, y);
	bossfishman->SetState(z);
	objects.push_back(bossfishman);
}
void CreateDoor(int x, int y)
{
	CDoor *cdoor = new CDoor(x, y);
	Door.push_back(cdoor);
}
void LoadObjects(int Stage)
{
	ifstream in;
	switch (Stage)
	{
	case STAGEINTRO:
		return;
		break;
	case STAGE1:
		in.open(STAGE1_INFO_PATH);
		break;
	case STAGE2:
		in.open(STAGE2_INFO_PATH);
		break;
	case STAGE3:
		in.open(STAGE3_INFO_PATH);
		break;
	default:
		break;
	}

	while (!in.eof())
	{
		int type;
		in >> type;
		if (type == 888888) break;

		if (type == SMALLCANDLES || type == BIGCANDLES) {//Candles

			while (1)
			{
				int x = 0, y = 0, typeItem;

				in >> x >> y >> typeItem;
				if (x == 999999)break;
				CreateCandel(x, y, typeItem, type);

			}
		}

		if (type == BRICKONSTAIR)//BrickOnStair
		{
			int x = 0, y = 0, TypeStair, DirectionUpOrDown, DirectionXUp;
			while (1)
			{
				in >> x >> y >> TypeStair >> DirectionUpOrDown >> DirectionXUp;
				if (x == 999999)break;
				CreateBrickOnStair(x, y, TypeStair, DirectionUpOrDown, DirectionXUp);
			}

		}
		if (type == BRICK) {//brick
			int left = 0, right = 0, top = 0, bottom = 0;
			while (1)
			{
				in >> left >> top >> right >> bottom;
				if (left == 999999)break;
				CreateBrick(left, right, top, bottom);
			}
		}
		if (type == MEDUSA) {//MEDUASA
			int x = 0, y = 0;
			while (1)
			{

				in >> x >> y;
				if (x == 999999)break;
				CreateMedusa(x, y);

			}

		}
		if (type == DOG) {//DOG
			int x = 0, y = 0;
			while (1)
			{


				in >> x >> y;
				if (x == 999999)break;
				CreateDog(x, y);


			}

		}
		if (type == BAT) {//BAT
			int x = 0, y = 0;
			while (1)
			{


				in >> x >> y;
				if (x == 999999)break;
				CreateBat(x, y);
			}

		}
		if (type == BIGBAT) {//BIGBAT
			int x = 0, y = 0, typeItem;
			while (1)
			{


				in >> x >> y >> typeItem;
				if (x == 999999)break;
				CreateBigBat(x, y, typeItem);
			}

		}
		if (type == HIDDENBRICK)//HiddenBrick
		{
			int x = 0, y = 0, typeItem, typeHiddenBrick, BrickDelete;
			while (1)
			{
				in >> x >> y >> typeItem >> typeHiddenBrick >> BrickDelete;
				if (x == 999999)break;
				CreateHiddenBrick(x, y, typeItem, typeHiddenBrick, BrickDelete);
			}

		}
		if (type == FISHMAN)//FishMan
		{
			int x = 0, y = 0, z = 0;
			while (1)
			{
				in >> x >> y >> z;
				if (x == 999999)break;
				CreateFishMan(x, y, z);
			}

		}
		if (type == DOOR)//Door
		{
			int x = 0, y = 0;
			while (1)
			{
				in >> x >> y;
				if (x == 999999)break;
				CreateDoor(x, y);
			}
		}

	}
	in.close();
	cin.ignore();
}
void LoadStage(int stageId)
{
	objects.clear();
	Brick.clear();
	Items.clear();
	switch (stageId)
	{
	case STAGEINTRO:	
		LoadBackground(STAGEINTRO);
		LoadIntroSource();
		break;
	case STAGE1:
		LoadBackground(STAGE1);
		LoadObjects(STAGE1);
		break;
	case STAGE2:		
		simon->SetPosition(background->getNewXSimon(), background->getNewYSimon());
		LoadBackground(STAGE2);
		LoadObjects(STAGE2);
		break;
	case STAGE3:
		simon->SetPosition(background->getNewXSimon(), background->getNewYSimon());
		LoadBackground(STAGE3);
		LoadObjects(STAGE3);
		break;
	default:
		break;
	}
}

void LoadResources()
{

	simon = CSimon::GetInstance();

	LoadStage(STAGEINTRO);

}
void CSampleKeyHander::KeyState(BYTE *states)
{
	if ((simon->GetReSetPlay() && ui->GetTimeLife() == 0) || (simon->GetLife() == 0 || ui->GetTimeLife() <= 0) && !simon->GetTheendBigBat())
	{

		if (game->IsKeyDown(DIK_SPACE))
		{
			objects.clear();
			Items.clear();
			LoadStage(STAGEINTRO);
			simon->SetMOVE(true);
			simon->SetTheEndBigBat(false);
			simon->SetLife(SIMON_LIFE_NUMBER);
			simon->SetWeaponRange(SIMON_RESETWEAPONS);
			simon->SetHealthSimon(SIMON_HEALTHMAX);
			simon->SetDoubleAttacking(false);
			LoadUI();
		}

	}

	// if simon is attacking or falling, deny all key control
	//if (simon->GetEffectItem()) return;
	if (simon->GetIsAttacking() || simon->GetIsFalling()) return;
	if (simon->GetTheendBigBat()) return;
	if (simon->GetBeingAttack()) return;
	if (simon->GetLife() == 0) return;
	if (camera->GetCameraMove()) return;

	if (game->IsKeyDown(DIK_K))
	{
		if (!simon->GetCanGoStair() && !simon->GetIsOnStair())
		{
			simon->SetState(SIMON_STATE_CROUCH_RIGHT, 0);
		}
		else
		{
			simon->SetState(SIMON_STATE_ONSTAIR_DOWN, 0);
		}
	}
	/*	if (game->IsKeyDown(DIK_K))
			simon->SetState(SIMON_STATE_CROUCH_RIGHT,0);
		else */ else if (game->IsKeyDown(DIK_L))
		simon->SetState(SIMON_STATE_WALKING_RIGHT, 0);
		else if (game->IsKeyDown(DIK_J))
		simon->SetState(SIMON_STATE_WALKING_LEFT, 0);
		else if (game->IsKeyDown(DIK_I))
		simon->SetState(SIMON_STATE_ONSTAIR_UP, 0);
	/*else if (game->IsKeyDown(DIK_K))
		simon->SetState(SIMON_ANI_ONSTAIR_DOWN,0);*/
		else
		simon->SetState(SIMON_STATE_IDLE_RIGHT, 0);
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/

void Update(DWORD dt)
{

	background->Update(simon->GetX(), simon->GetY(), &Brick, camera->GetX());

	if (ui != NULL)
		ui->Update(dt, 0, simon->GetTunrnActack(), simon->GetLife(), background->GetStage(), simon->GetTheendBigBat());
	if (background->GetStage() == STAGEINTRO)
	{
		if (simon->GetTheendIntro())
		{
			background->setNextMap(true);
			background->setStage(STAGE1);
			simon->SetPosition(0, 113);
			simon->SetMOVE(false);
			simon->SetDirection(1);
		}

	}
	if (simon->GetMoneyBag())
	{
		simon->SetMoneyBag(false);
		ui->SetScore(SCORE700);
	}
	if (background->GetNextMap())
	{
		LoadStage(background->GetStage());
		return;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetCurrentID(i);
	}

	for (int i = 0; i < Brick.size(); i++)
		Brick[i]->SetCurrentID(i);

	Map = new Grid(background->getWidth());
	//rangedWeapon->Update(dt, &objects);
	//whip->Update(dt, &objects);
	{
		for (int i = 0; i < objects.size(); i++)
		{
			int size = objects.size();
			bool ADD = true;
			switch (objects[i]->GetType())
			{

			case TYPE_CANDLE: //CANDEL
				if (!objects[i]->DoesExist())
				{
					Candle *candle = dynamic_cast<Candle *>(objects[i]);
					delete objects[i];
					objects.erase(objects.begin() + i);
					continue;
				}
				if (objects[i]->GetDestroy() || simon->GetLife() == 0)
				{
					Candle *candle = dynamic_cast<Candle *>(objects[i]);
					objects[i] = objects[objects.size() - 1];
					objects.pop_back();
					ADD = false;
					if (!simon->GetLife() == 0)
					{
						Item * item = new Item(candle->GetX(), candle->GetY(), candle->GetItemType(), 1);
						Items.push_back(item);
						//Map->AddId(objects[objects.size() - 1]->GetX(), objects.size() - 1);

					}
				}
				else
				{
					dynamic_cast<Candle *>(objects[i])->Update(dt, &objects, camera->GetX(), SCREEN_WIDTH);
				}
				break;
			case TYPE_MEDUSA: // MEDUSA
				if (objects[i]->GetDestroy() || simon->GetCross())
				{
					ui->SetScore(SCORE100);
				}
				if (!objects[i]->DoesExist() || objects[i]->GetDestroy() || simon->GetCross() || background->GetStage() == 3 || background->GetStage() == 1 || simon->GetLife() == 0)
				{

					CBossMedusa *bossmedusa = dynamic_cast<CBossMedusa *>(objects[i]);
					delete objects[i];
					objects.erase(objects.begin() + i);
					ADD = false;
					continue;
				}
				else {
					dynamic_cast<CBossMedusa *>(objects[i])->Update(dt, &objects, &Brick, camera->GetX(), background->GetStage(), simon->GetX(), simon->GetY());
				}
				break;
			case TYPE_DOG: // DOG	
				if (objects[i]->GetDestroy())
				{
					ui->SetScore(200);
				}
				if (!objects[i]->DoesExist() || objects[i]->GetDestroy() || background->GetStage() == 3 || background->GetStage() == 1 || simon->GetLife() == 0)
				{

					CBossDog *bossdog = dynamic_cast<CBossDog *>(objects[i]);
					delete objects[i];
					objects.erase(objects.begin() + i);
					ADD = false;
					continue;
				}
				else {
					dynamic_cast<CBossDog *>(objects[i])->Update(dt, &objects, &Brick, simon->GetX(), simon->GetY(), background->GetStage());
				}

				break;
			case TYPE_BAT://BAT
				if (objects[i]->GetDestroy())
				{
					ui->SetScore(SCORE200);
				}
				if (!objects[i]->DoesExist() || objects[i]->GetDestroy() || background->GetStage() == 3 || background->GetStage() == 1 || simon->GetLife() == 0)
				{

					CBossBat *bossbat = dynamic_cast<CBossBat *>(objects[i]);
					delete objects[i];
					objects.erase(objects.begin() + i);
					ADD = false;
					continue;

				}
				else
				{
					dynamic_cast<CBossBat *>(objects[i])->Update(dt, &objects, camera->GetX(), background->GetStage(), simon->GetX(), simon->GetY());
				}
				break;
			case TYPE_FISHMAN://FISHMAN	
				if (objects[i]->GetDestroy())
				{
					ui->SetScore(SCORE300);

				}
				if (!objects[i]->DoesExist() || objects[i]->GetDestroy() || background->GetStage() == 1 || background->GetStage() == 2 || simon->GetLife() == 0)
				{
					CBossFishMan *bossfishman = dynamic_cast<CBossFishMan *>(objects[i]);
					delete objects[i];
					objects.erase(objects.begin() + i);
					ADD = false;
					continue;

				}
				else
				{
					if (!simon->GetStopWatch())
					{
						dynamic_cast<CBossFishMan *>(objects[i])->Update(dt, &objects, &Brick, simon->GetX(), simon->GetY(), background->GetStage());
					}
				}

				break;
			case TYPE_BRICKHIDDEN: //BRICK HIDDEN
				if (objects[i]->GetDestroy())
				{

					BrickHidden *brickhidden = dynamic_cast<BrickHidden *>(objects[i]);

					objects[i] = objects[objects.size() - 1];
					objects.pop_back();
					ADD = false;
					Item * item = new Item(brickhidden->GetX(), brickhidden->GetY(), brickhidden->GetItemType(), 2);
					Items.push_back(item);
					//Map->AddId(objects[objects.size()-1]->GetX(), objects.size()-1);
					delete Brick[brickhidden->GetBrickDelete()];
					Brick.erase(Brick.begin() + brickhidden->GetBrickDelete());
					continue;
				}
				else
				{
					objects[i]->Update(dt, &Brick);
				}
				break;
			case TYPE_BIGBAT:
				if (objects[i]->GetDestroy() || simon->GetLife() == 0)
				{
					CBossBigBat *bossbigbat = dynamic_cast<CBossBigBat *>(objects[i]);
					objects[i] = objects[objects.size() - 1];
					ui->SetScore(SCORE3000);
					objects.pop_back();
					ADD = false;
					if (simon->GetLife() != 0)
					{
						Item * item = new Item(bossbigbat->GetX() + 20, bossbigbat->GetY(), bossbigbat->GetItemType(), 2);
						Items.push_back(item);
						//Map->AddId(objects[objects.size() - 1]->GetX(), objects.size() - 1);
					}

				}
				else {
					dynamic_cast<CBossBigBat *>(objects[i])->Update(dt, &objects, camera->GetScreenWidth(), camera->GetX(), simon->GetX(), simon->GetY(), simon->GetDoubleAttacking(),simon->GetReSetHeathBigBat());
				}
				break;
			case TYPE_FIREBALL: // Fire Ball of FishMan
				if (objects[i]->GetDestroy())
				{
					FireBall *fireball = dynamic_cast<FireBall *>(objects[i]);
					objects[i] = objects[objects.size() - 1];
					ui->SetScore(SCORE100);
					objects.pop_back();
					ADD = false;
				}
				else {
					objects[i]->Update(dt, &Brick);
				}
				break;
			default:
				objects[i]->Update(dt, &Brick);
				break;
			}

			if (ADD)
				Map->AddId(objects[i]->GetX(), i);


		}
	}
	for (int i = 0; i < Items.size(); i++)
	{
		if (!Items[i]->DoesExist())
		{
			Items[i]->Update(dt, &Brick);
		}
		else
		{
			delete Items[i];
			Items.erase(Items.begin() + i);
			continue;
		}
	}
	//DebugOut(L"Y = %f", simon->GetY());

	if (simon->GetY() > 2000) // roi xuong vuc Map 3
	{
		background->setNextMap(true);
		background->setStage(2);
		background->setNewXSimon(1620);
		background->setNewYSimon(-100);
		simon->SetLife(simon->GetLife() - 1);
		simon->SetHealthSimon(16);
	}

	for (int i = 0; i < objects.size(); i++) // xoa het object be hown toa do simon X , khi len len ham`
	{
		if (simon->GetX() < 100 && background->GetStage() == STAGE2)
		{
			if (objects[i]->GetX() > 2045)
			{
				delete objects[i];
				objects.erase(objects.begin() + i);
				continue;
			}
		}
		if (simon->GetX() > 1500 && background->GetStage() == STAGE2)
		{
			if (objects[i]->GetX() < 1500)
			{
				delete objects[i];
				objects.erase(objects.begin() + i);
				continue;
			}
		}

		if (simon->GetX() > 1850 && background->GetStage() == STAGE2)
		{
			if (objects[i]->GetX() < 1800)
			{
				delete objects[i];
				objects.erase(objects.begin() + i);
				continue;
			}
		}
	}

	/*for (int i=0;i<background->getWidth()/180;i++)
		DebugOut(L"Size %d \n", Map->GetIdInArea(i).size());
	DebugOut(L"-----------------------------------\n");*/

	simon->Update(dt, background->GetStage(), Map, camera->GetBackgroundWidth(), camera->GetStart(), camera->GetX(), &objects, &Brick, &Items);
	camera->Update(SCREEN_WIDTH, background->getWidth(), simon->GetX(), simon->GetY(), simon->GetMOVE(), background->GetStage());

}


/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		if (simon->GetCross())
		{
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR1);

		}
		//}
		Camera *camera = Camera::GetInstance();
		//Point pos = camera->PositionOnCamera(x, y);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		background->Render(camera->GetX());
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera->GetX(), SCREEN_WIDTH);
		for (int i = 0; i < Door.size(); i++)
			if (background->GetStage() == 2)
			{
				Door[i]->Render(simon->GetX(), camera->GetX());
			}
		for (int i = 0; i < Items.size(); i++)
		{
			Items[i]->Render(camera->GetX(), SCREEN_WIDTH);
		}
		simon->Render(camera->GetX(), SCREEN_WIDTH);
		if (ui != NULL)
			ui->Render(camera->GetX(), SCREEN_WIDTH);
		spriteHandler->End();
		d3ddv->EndScene();
	}
	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Render();
			Update(dt);

		}
		else
			Sleep(tickPerFrame - dt);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();

	game->InitKeyboard(keyHandler);

	LoadResources();
	LoadUI();
	Run();

	/*	if (simon->GetLife() <= 0 || ui->GetTimeLife() <= 0 && !simon->GetTheendBigBat())
		{
			LoadStage(0);
		}*/


	return 0;
}