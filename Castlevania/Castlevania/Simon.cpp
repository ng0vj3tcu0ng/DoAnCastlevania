#include "Simon.h"


#define SIMON_INFOR_TXT_PATH  L"Backgrounds\\TexturesSpritesAni\\TSASimon.txt"


CSimon * CSimon::__instance = NULL;
CSimon * CSimon::GetInstance()
{
	if(__instance==NULL)
	__instance = new CSimon();
	return __instance;
}
void CSimon::RenderWeapons(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK)
{
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	if (!knife->getLock()) 
	{
		knife->Render_UI();
	}
	if (!axe->getLock())
	{
		axe->Render_UI();
	}
	if (!holywater->getLock())
	{
		holywater->Render_UI();
	}
	if (!bomerang->getLock())
	{
		bomerang->Render_UI();
	}
	if (this->knife->GetIsBeingThrown() || this->axe->GetIsBeingThrown() || this->holywater->GetIsBeingThrown()||this->bomerang->GetIsBeingThrown()) {
		switch (this->WeaponRange)
		{
		case NUMBER_KNIFE: {
			
			knife->Render(camera->GetX(), SCREEN_WIDTH, SIMON_STATE, this->GetX(), this->GetY(), CROUCHING_ATTACK);
				break;
		}
		case NUMBER_AXE: {
			axe->Render(camera->GetX(), SCREEN_WIDTH, SIMON_STATE, this->GetX(), this->GetY(), CROUCHING_ATTACK);
				break;
		}
		case NUMBER_HOLYWATER: {
			holywater->Render(camera->GetX(), SCREEN_WIDTH, SIMON_STATE, this->GetX(), this->GetY(), CROUCHING_ATTACK);
			break;
		}
		case NUMBER_BOMERANG: {
			bomerang->Render(camera->GetX(), SCREEN_WIDTH, SIMON_STATE, this->GetX(), this->GetY(), CROUCHING_ATTACK);
			break;
		}
		default:
			this->WeaponRange = -1;
			break;
		}
	}

	if (whip->GetBeingAttacking()) {
		switch (this->WeaponMelee)
		{
		case NUMBER_WHIP: {
			whip->Render(camera->GetX(), SCREEN_WIDTH, SIMON_STATE, this->GetX(), this->GetY(), CROUCHING_ATTACK);
			break;
		}
		default:
			this->WeaponMelee = -1;
			break;
		}
	}
}
void CSimon::UpdateWeapons(DWORD dt, vector<LPGAMEOBJECT> *Brick, vector<LPGAMEOBJECT> *colliable_objects,Grid *map)
{
	

	switch (this->WeaponRange)
	{
	case NUMBER_KNIFE: {
		if (knife->GetIsBeingThrown()) {
			knife->Update(dt, this->nx, this->x, this->StartThrown, map, colliable_objects);
			
		}
			break;
	}
	case NUMBER_AXE:
	{

		if (axe->GetIsBeingThrown())
			axe->Update(dt, this->nx, this->x, this->y, this->StartThrown, map, colliable_objects);
		break;
	}
	case NUMBER_HOLYWATER: {
		if (holywater->GetIsBeingThrown())
			holywater->Update(dt, this->nx, this->x, this->y, this->StartThrown, map,Brick, colliable_objects);
		break;
	}
	case NUMBER_BOMERANG: {
		if (bomerang->GetIsBeingThrown())
			bomerang->Update(dt, this->nx, this->x, this->StartThrown, map, colliable_objects);
		break;
	}
	default:
		this->WeaponRange = -1;
		break;
	}

	switch (this->WeaponMelee)
	{
	case NUMBER_WHIP: {
		whip->Update(dt, this->nx, map, colliable_objects);
		break;
	}
	default:
		this->WeaponMelee = -1;
		break;
	}
}
void CSimon::LeverUpWeapons(int vk)
{
	switch (vk)
	{
		case NUMBER_WHIP: {
			whip->LevelUp();

			break;
		}
		case NUMBER_KNIFE: {
		
			break;
		}
		case NUMBER_AXE: {

			break;
		}
		case NUMBER_HOLYWATER: {

			break;
		}
		case NUMBER_BOMERANG: {

			break;
		}
		default:
			break;
	}
}
CSimon::CSimon()
{
	LoadSimon();
	this->Life = SIMON_LIFE_NUMBER;
	ReSetHeathBigBat = false;
	CanUpStair = false;
	CanGoStair = false;
	IDLE = false;
	IdStair = -1;
	MOVE = false;
	FlagDelay = false;
	FlagIdle = false;
	TheendIntro = false;
	TurnOffCBrick = false;
	this->FlagStartIntroTime = false;
	MOVENHERIGHT = false;
	this->HavingCross = false;
	LockFlicker = false;
	EffectGetItem = false;
	EffectInvisible = false;
	DoubleAttacking = false;
	StopWatch = false;
	GetBagMoney = false;
	GetHolyWater = false;
	GetAxe = false;
	GetKnife = false;
	GetBomerang = false;
	TheendBigBat = false;
	ResetPlay = false;
	whip = new Whip();
	max_healthsimon = SIMON_HEALTHMAX;
	healthsimon = max_healthsimon;
	for (int i = 0; i < max_healthsimon;i++) {
		HealthSimon *temp = new HealthSimon();
		temp->SetPosition(56+i * 4,20);
		this->healthsimon_ani.push_back(temp);
	}
	this->whip->SetType(-1);
	X2Attacking = new CDoubleAttacking();
	ResetAttacking();

	EffectWater * water_temp;
	for (int i = 0; i < 3; i++)
	{
		water_temp = new EffectWater();
		water.push_back(water_temp);
	}

}

void CSimon::LoadSimon()
{

	CTextures * textures = CTextures::GetInstance();

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	ifstream in;
	int action;
	int n;
	int left = 0, top = 0, right = 0, bottom = 0, idsprites = 0, idtxt = 0;
	int idAni = 0, defaultTime = 0, nSprites = 0, idSprites = 0;
	in.open(SIMON_INFOR_TXT_PATH);
	string link;
	while (1) 
	{
		in >> action >> n;
		if (action == -1)break;
		switch (action) {
		case 0:// tex 
			int r, g, p;
			int id;
			for (int i = 0; i < n; i++)
			{
				in >> id >> r >> g >> p >> link;
				LPCWSTR s = convStringToLPCWSTR(link);
				textures->Add(id, s, D3DCOLOR_XRGB(r, g, p));
			}
			break;
		case 100://spr
			for (int i = 0; i < n; i++)
			{
				in >> idsprites >> left >> top >> right >> bottom >> idtxt;
				sprites->Add(idsprites, left, top, right, bottom, textures->Get(idtxt));
			}
			break;
		case 200:// ani
			for (int i = 0; i < n; i++)
			{
				in >> idAni >> defaultTime >> nSprites; ;
				ani = new CAnimation(defaultTime);
				for (int j = 0; j < nSprites; j++)
				{
					in >> idSprites;
					ani->Add(idSprites);
				}
				animations->Add(idAni, ani);
				this->AddAnimation(idAni);

			}
			break;
		}
	}	
}

int CSimon::GetTunrnActack()
{
	if (GetTickCount() - TimeUpdate1 > SIMON_TURNATTACK_TIME)
	{
		TimeUpdate1 = GetTickCount();
		int temp = this->TunrnActack;
		this->TunrnActack = 0;
		return temp;

	}
	return 0;
}
void CSimon::Setweapons()
{

	if (GetKnife)
	{

		knife->Unlock(true);
		axe->Unlock(false);
		holywater->Unlock(false);
		bomerang->Unlock(false);
	}
	if (GetAxe)
	{

		knife->Unlock(false);
		axe->Unlock(true);
		holywater->Unlock(false);
		bomerang->Unlock(false);

	}
	if (GetHolyWater)
	{
		knife->Unlock(false);
		axe->Unlock(false);
		holywater->Unlock(true);
		bomerang->Unlock(false);

	}
	if (GetBomerang)
	{
		knife->Unlock(false);
		axe->Unlock(false);
		holywater->Unlock(false);
		bomerang->Unlock(true);
	}
}
void CSimon::ResetAttacking()
{
	isAttacking = false;
	knife = new Knife();
	axe = new CAXE();
	holywater = new CHOLYWATER();
	bomerang = new Bomerang();
}

void CSimon::BricksCollision(vector<LPGAMEOBJECT>* Brick)
{
	if (TurnOffCBrick)
	{
		x += dx;
		y += dy;
	}
	else
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		vector<LPGAMEOBJECT> coObjects;

		for (int i = 0; i < Brick->size(); i++)
			if (dynamic_cast<CBrick *>(Brick->at(i)))
				coObjects.push_back(Brick->at(i));

		CalcPotentialCollisions(&coObjects, coEvents);
	
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

				// block 
				x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.1f;
				
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				
				isFalling = false;
				isJumpingForward = false;
				CanUpStair = false;
			}
		
		// clean up collision events
		for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}



void CSimon::SetCollisionStair(vector<LPGAMEOBJECT>* Objects)
{

	CanGoStair = false;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < Objects->size(); i++)
		if (dynamic_cast<CBrickOnStair *>(Objects->at(i)))
			coObjects.push_back(Objects->at(i));


	//DebugOut(L"So luong cau thanhg: %d\n", coObjects.size());
	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	   //block 
        //x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
        // y -= min_ty * dy + ny * 0.1f;

	    //if (nx != 0) vx = 0;
	    //if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//if ((e->obj))
			if (dynamic_cast<CBrickOnStair *>(e->obj))
			{
				CBrickOnStair *brickonstair = dynamic_cast<CBrickOnStair *>(e->obj);	
				{
					{
						if (abs(x - e->obj->GetX()) < SIMON_DISTANCE_STAIR_X)
						{
							CanUpStair = !CanUpStair;
							CanDownStair = !CanDownStair;
							{
								this->SetPosition(e->obj->GetX(), y);
							}

						}
					}
				}		
				if (e->nx != 0 || e->ny != 0)
				{		
				
					{  
					TurnOffCBrick = !TurnOffCBrick;
							
						{
							CanGoStair = true;
							{
							this->IdStair = brickonstair->GetID();
							if (brickonstair->GetTypeStair() == 0) 
								{
									//this->CanUpStair = true;
								this->CanDownStair = false;

								}
							else
									{
										{
											this->CanUpStair = false;
											this->CanDownStair = true;
										}

									}
							}

							if (StartWalkingStair)
							{
								IsOnStair = true;
								/*if (ChangeDirection)
								{
									this->nx = brickonstair->GetDirection();					
							    }*/
							}

							this->DirectionXStair = brickonstair->GetDirectionXUp();
							this->DirectionYStair = SIMON_DIRECTION_UP_STAIR;
						}
					}
				}
				
				

			}	
	}

	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];


}


void CSimon::ItemsCollision(vector<LPGAMEOBJECT>* Items)
{
	
	//if (HavingCross)
	//{
	//	HavingCross = false;
	//}
	
	//ScoreItem = 0;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < Items->size(); i++)
		if (dynamic_cast<Item *>(Items->at(i)))
			coObjects.push_back(Items->at(i));



	CalcPotentialCollisions(&coObjects, coEvents);

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;
		// Collision logic with items
		if (!GetItem)
		{ 
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{

				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Item *>(e->obj))
				{
					Item *item = dynamic_cast<Item *>(e->obj);
				
					if (e->nx != 0 || e->ny != 0)
					{
						TypeItems = item->GetType();

						switch (TypeItems)
						{
						case ITEM_TYPE_WHIP_UPGRADE:
							this->SetState(SIMON_STATE_EFFECT_RIGHT,0);
							this->LeverUpWeapons(NUMBER_WHIP);
							GetItem = true;
							break;
						case ITEM_TYPE_DAGGER:
							this->SetState(SIMON_STATE_EFFECT_RIGHT, 0);
							ResetAttacking();
							knife->Unlock(true);
							axe->Unlock(false);
							holywater->Unlock(false);
							bomerang->Unlock(false);
							GetItem = true;
							break;
						case ITEM_TYPE_HEART:
							//TimeUpdate = GetTickCount();
							TunrnActack = 5;
							GetItem = true;
							break;
						case ITEM_TYPE_MONEY_BAG:
							//TimeUpdate = GetTickCount();
							GetItem = true;
							GetBagMoney = true;
							break;
							 
						case ITEM_TYPE_HEARTS:
							//TimeUpdate = GetTickCount();
							TunrnActack = 1;
							GetItem = true;
							break;
						case ITEM_TYPE_AXE:
							this->SetState(SIMON_STATE_EFFECT_RIGHT, 0);
							ResetAttacking();
							axe->Unlock(true);
							knife->Unlock(false);
							holywater->Unlock(false);
							bomerang->Unlock(false);
							GetItem = true;
							break;
							
						case ITEM_TYPE_HOLYWATER:
								this->SetState(SIMON_STATE_EFFECT_RIGHT, 0);
								ResetAttacking();
								axe->Unlock(false);
								knife->Unlock(false);
								holywater->Unlock(true);
								bomerang->Unlock(false);
								GetItem = true;
								item->SetFallingStyle(2);
								break;
							
						case ITEM_TYPE_CROSS:
							this->SetState(SIMON_STATE_EFFECT_RIGHT,0);
							LockFlicker = true;
							Flicker = GetTickCount();
							GetItem = true;
							HavingCross = true;
							break;
						case ITEM_TYPE_INVINCIBILITY:
							EffectInvisible = true;
							EfffectInvisibleTime = GetTickCount();
							break;
						case ITEM_TYPE_JEWEL:
							TheendBigBat = true;
							break;
						case ITEM_TYPE_DOUBLEATTACK:
							DoubleAttacking = true;
							break;
						case ITEM_TYPE_POTROAST:
							healthsimon = SIMON_HEALTHMAX;
							break;
						case ITEM_TYPE_STOPWATCH:
							StopWatch = true;
							StopWatchTime = GetTickCount();
							break;
						case ITEM_TYPE_BOMERANG:
							this->SetState(SIMON_STATE_EFFECT_RIGHT, 0);
							ResetAttacking();
							axe->Unlock(false);
							knife->Unlock(false);
							holywater->Unlock(false);
							bomerang->Unlock(true);
							GetItem = true;
							break;
						}
						item->SetDestroy(true);
					}
				}
			}
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];			
	     }
}
void CSimon::FireBallCollision(vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < Objects->size(); i++)
		if (dynamic_cast<FireBall *>(Objects->at(i)))
			coObjects.push_back(Objects->at(i));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//block 
   //x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
   //y += min_ty * dy + ny * 0.1f;

   //if (nx != 0) vx = 0;
   //if (ny != 0) vy = 0;
	if (!BossCantAttacked) 
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<FireBall *>(e->obj))
			{
				FireBall *fireball = dynamic_cast<FireBall *>(e->obj);
				if (e->nx != 0 || e->ny != 0)
				{
					SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
					if (e->nx <= 0)
					{
						BeingAttackRight = true;
					}
					else BeingAttackRight = false;

				}
			}
		}
	}


	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::BossMedusaCollision(vector<LPGAMEOBJECT>* Objects,Grid * map)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;


	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossMedusa *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));


	
	CalcPotentialCollisions(&coObjects, coEvents);
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		 //block 
		//x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//y += min_ty * dy + ny * 0.1f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;
		if (!BossCantAttacked) {
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBossMedusa *>(e->obj))
				{
					CBossMedusa *bossmedusa = dynamic_cast<CBossMedusa *>(e->obj);
					if (e->nx != 0 || e->ny != 0)
					{

						SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
						if (healthsimon > 0)
							healthsimon--;
						if (e->nx <= 0)
						{
							BeingAttackRight = true;
						}
						else BeingAttackRight = false;
					
					}
				}
			}
		}
	

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSimon::BossDogCollision(vector<LPGAMEOBJECT>* Objects, Grid * map)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x / 180);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossDog *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));


	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//block 
   //x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
   //y += min_ty * dy + ny * 0.1f;

	//if (nx != 0) vx = 0;
	//if (ny != 0) vy = 0;

	if (!BossCantAttacked) {
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBossDog *>(e->obj))
			{
				CBossDog *bossdog = dynamic_cast<CBossDog *>(e->obj);
				if (e->nx != 0 || e->ny != 0)
				{
					SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
					if (healthsimon > 0)
						healthsimon-=2;
					
					if (e->nx < 0)
					{
						BeingAttackRight = true;
					}
					else BeingAttackRight = false;
				}
			}
		}
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSimon::BossBatCollision(vector<LPGAMEOBJECT>* Objects, Grid * map)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x / 180);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossBat *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));


	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//block 
   //x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
   //y += min_ty * dy + ny * 0.1f;

	//if (nx != 0) vx = 0;
	//if (ny != 0) vy = 0;

	if (!BossCantAttacked) {
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBossBat *>(e->obj))
			{
				CBossBat *bossbat = dynamic_cast<CBossBat *>(e->obj);
				if (e->nx != 0)
				{
					SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
					if (healthsimon > 0)
						healthsimon-=2;
					if (e->nx < 0)
					{
						BeingAttackRight = true;
					}
					else BeingAttackRight = false;
				}
			}
		}
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSimon::BossFishManCollision(vector<LPGAMEOBJECT>* Objects, Grid * map)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x / 180);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossFishMan *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));


	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//block 
   //x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
   //y += min_ty * dy + ny * 0.1f;

	//if (nx != 0) vx = 0;
	//if (ny != 0) vy = 0;

	if (!BossCantAttacked) 
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBossFishMan *>(e->obj))
			{
				CBossFishMan *bossfishman = dynamic_cast<CBossFishMan *>(e->obj);
				if (e->nx != 0)
				{
					SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
					if (healthsimon > 0)
						healthsimon -= 2;
					if (e->nx < 0)
					{
						BeingAttackRight = true;
					}
					else BeingAttackRight = false;
				}
			}
		}
	}
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::BossBigBatCollision(vector<LPGAMEOBJECT>* Objects, Grid * map)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x / 180);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossBigBat *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));


	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);



	if (!BossCantAttacked)
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBossBigBat *>(e->obj))
			{
				CBossBigBat *bossbigbat = dynamic_cast<CBossBigBat *>(e->obj);
				if (e->nx != 0 || e->ny != 0)
				{
					SetState(SIMON_STATE_BEINGATTACKED_RIGHT,0);
					if (healthsimon > 0)
						healthsimon-=2;
			


					if (e->obj->GetX()>x)
					{
						BeingAttackRight = true;
					}
					else BeingAttackRight = false;
				}
			}
		}
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

bool GetGate(int x) 
{
	if (x > 1500 && x < 1540) {
		return true;
	}
	if (x > 2000 && x < 2040)
	{
		return true;
	}
	return false;
}
void CSimon::SimonIntro(int IdStage)
{
	if (IdStage == 0)
	{

		if (y > 125)
		{
			vy = 0; y = 125.0f; /*vx = 0;*/
			x -= SIMON_MOVE;
			nx = -1;
			if (x < 120)
			{
				if (!FlagStartIntroTime) {
					this->FlagStartIntroTime = true;
					this->DelayIntroTime = GetTickCount();
				}

				if (GetTickCount() - DelayIntroTime > SIMON_DELAY_INTRO_TIME) {
					TheendIntro = true;
					this->FlagStartIntroTime = false;
				}
			}
		}

	}
}
void CSimon::SimonMove(int IdStage, float camera_x)
{

	if (GetGate(x))
	{
		IDLE = true;
		vx = 0;
	}

	if (IdStage == 0)
	{
		MOVE = true;
		if (x < 120)
		{
			MOVE = false;
			x = 120;
		}
	}
	if (IdStage == 1)
	{
		if (x > 665)
		{
			vx = 0;
			MOVE = true;
		}
		
	}
	if (IdStage == 2)
	{
		MOVE = false;
			if (camera_x > 1575 && camera_x < 1700)
			{

				if (x > 1500)
				{

					if (x < 1510) {
						FlagDelay = true;
						DelayMove = GetTickCount();
					}
					MOVE = true;
				}			
			}
			if (camera_x > 1575 && camera_x < 1700)
			{
				if (x > 1580) //cong 1 canh 2
				{
					MOVE = false;
				}
			
			}
			if (camera_x > 2075 && camera_x < 2200)
			{
				if (x > 2010) //cong 2 canh 2
				{
					if (x < 2020) 
					{
						FlagDelay = true;
						DelayMove = GetTickCount();
					}
					MOVE = true;
				}
			}
			if (camera_x > 2075 && camera_x < 2200)
			{
				if (x > 2080)// cong 2 canh 2
				{
					MOVE = false;
					
				}
			}
	}
	
	if (MOVE)
	{
		if (IdStage == 0)
		{
			x -= SIMON_MOVE;
		}
		if (GetTickCount() - DelayMove > SIMON_DELAYSIMON_DOOR_TIME) 
		{
			if(IdStage == 1)
			{
				x += SIMON_MOVE1;
			}
			else x += SIMON_MOVE;
			FlagIdle = false;
		}
		else 
		{
			if (IdStage == 2)
			{
				if (camera_x < 1700) // Cong 1 canh2 
				{
					x = 1511;
				}
				if (camera_x < 2090 && camera_x>1980)// Cong 2 canh 2
				{
					x = 2021;
				}
				vx = 0;
				FlagIdle = true;
			}

		}
		
	}
}
void CSimon::SimonFlicker()
{
	if(LockFlicker)
	{
		if (HavingCross)
		{
			DWORD now1 = GetTickCount();
			if (now1 - 100 > Flicker)
			{
				HavingCross = false;
				Flicker = GetTickCount();

			}
		}
		if (!HavingCross)
		{
			DWORD now2 = GetTickCount();
			if (now2 - 100 > Flicker)
			{
				HavingCross = true;
				Flicker = GetTickCount();
			}
		}
	}
	if (!GetItem)
	{
		LockFlicker = false;
		HavingCross = false;
	}

} // Nhap Nhap khi GetCross
void CSimon::Update(DWORD dt, int IdStage,Grid *map, int background_width, int start, float camera_x, vector<LPGAMEOBJECT> *Objects, vector<LPGAMEOBJECT> *Brick,  vector<LPGAMEOBJECT> *Items)
{

	SimonFlicker();

	CGameObject::Update(dt);

	if (GetItem) return;


	if (vy != 0 && !IsOnStair )
	{
		isFalling = true;
	}

	if (GetTickCount() - StopWatchTime > FISHMAN_DELAY_TIME)
	{
		StopWatch = false;
	}


	if (!IsOnStair)
		vy += GRAVITY * dt;
	if (IsOnStair)
	{
		TurnOffCBrick = true;
	}
	else TurnOffCBrick = false;
	

	// simple fall down

	

	// simple screen edge collision!!!
	if (vx > 0 && x > background_width - 35) { x =  background_width - 35; } //background
	if (vx < 0 && x < start) { x = start; }
	// check attacking time
	DWORD now = GetTickCount();	 //reset không nó sẽ đánh hoài ---
	if (now - SIMON_ATTACKING_TIME > attackingTime)	
	{
		isAttacking = false;
		//rangedweapon->SetIsBeingThrown(false);
		// reset current frame of all attacking animations
		animations[SIMON_STATE_ATTACK_LEFT]->SetCurrentFrame(-1);
		animations[SIMON_STATE_ATTACK_RIGHT]->SetCurrentFrame(-1);		
		animations[SIMON_STATE_CROUCHING_ATTACK_LEFT]->SetCurrentFrame(-1);
		animations[SIMON_STATE_CROUCHING_ATTACK_RIGHT]->SetCurrentFrame(-1);

	}

	
  // Handling Bricks

		BricksCollision(Brick);
		// Handling Item
		ItemsCollision(Items);
		SetCollisionStair(Objects);
		BossMedusaCollision(Objects,map);
		BossDogCollision(Objects, map);
		BossBatCollision(Objects, map);
		BossFishManCollision(Objects, map);
		BossBigBatCollision(Objects, map);
		FireBallCollision(Objects);
		// Move Door
		SimonMove(IdStage, camera_x);
		SimonIntro(IdStage);
		Setweapons();
	// clean up collision events
	this->UpdateWeapons(dt, Brick, Objects, map);
	if (healthsimon <=0)
	{
		ReSetHeathBigBat = true;
	}
	else
	{
		ReSetHeathBigBat = false;
	}
	if (this->healthsimon <= 0)
	{
		Life--;
		this->healthsimon = this->max_healthsimon;
	}
	if (y > 140)
	{
		this->water[0]->Start(WATER1_VX, this->x, this->y, WATER_STEPUP1);
		this->water[1]->Start(WATER2_VX, this->x, this->y, WATER_STEPUP2);
		this->water[2]->Start(WATER3_VX, this->x, this->y, WATER_STEPUP1);
	}

	for (int i = 0; i < water.size(); i++)
		water[i]->Update(dt, Objects);
	
}

void CSimon::Render(float screen_x, int SCREEN_WIDTH)
{
	bool CROUCHING_ATTACK = false;

	int ani = state;

	if ((ani == SIMON_STATE_EFFECT_RIGHT) || (ani == SIMON_STATE_EFFECT_LEFT))
	{
		{
			if (nx > 0) ani = SIMON_STATE_EFFECT_RIGHT;
			else ani = SIMON_STATE_EFFECT_LEFT;
		}
	}
		if (ani == SIMON_STATE_ONSTAIR_UP)
		{
			{
				if (nx > 0)
				{
					ani = SIMON_STATE_ONSTAIR_UP_RIGHT;
				}
				else ani = SIMON_STATE_ONSTAIR_UP_LEFT;
			}
		}

		if (ani == SIMON_STATE_ONSTAIR_DOWN)
		{
			{
				if (nx > 0)
				{
					ani = SIMON_STATE_ONSTAIR_DOWN_RIGHT;
				}
				else ani = SIMON_STATE_ONSTAIR_DOWN_LEFT;
			}
		}
		if (vx!=0&&!IsOnStair)
		{
			if (nx > 0)
			{
				ani = SIMON_STATE_WALKING_RIGHT;
			}
			else ani = SIMON_STATE_WALKING_LEFT;
	      }
		if (vx == 0&& IDLE)
			{
			if (nx > 0) ani = SIMON_STATE_IDLE_RIGHT;
			else ani = SIMON_STATE_IDLE_LEFT;
			}

		if ((ani == SIMON_STATE_CROUCH_RIGHT) || (ani == SIMON_STATE_CROUCH_LEFT))
			{
			

				if (nx > 0) ani = SIMON_STATE_CROUCH_RIGHT;
				else ani = SIMON_STATE_CROUCH_LEFT;
			
			}
			
		
	if (isFalling) ani = SIMON_STATE_JUMP_RIGHT;

	if (isAttacking && ani != SIMON_STATE_CROUCHING_ATTACK_RIGHT && ani != SIMON_STATE_CROUCHING_ATTACK_LEFT) ani = SIMON_STATE_ATTACK_RIGHT;
	if (MOVE)
	{
		if (nx > 0)
		{
			ani = SIMON_STATE_WALKING_RIGHT;
		}
		else ani = SIMON_STATE_WALKING_LEFT;	
	}
	if (y == 125 && !MOVE)
	{
		ani = SIMON_STATE_IDLE_INTRO;
	}

	if ((ani == SIMON_STATE_JUMP_RIGHT) || (ani == SIMON_STATE_JUMP_LEFT) )
	{
		if (nx > 0)
		{
			ani = SIMON_STATE_JUMP_RIGHT;
			if (isJumpingForward) vx = SIMON_WALKING_SPEED;
		}
		else
		{
			ani = SIMON_STATE_JUMP_LEFT;
			if (isJumpingForward) vx = -SIMON_WALKING_SPEED;
		}
	}


	if (vx == 0 && vy == 0 && IsOnStair)
	{
		if (nx > 0) 
		{
			if (BeingDownStair) 
			{
				ani = SIMON_STATE_ONSTAIR_UP_IDLE_LEFT;//up left
			}
			else 
			{
				ani = SIMON_STATE_ONSTAIR_UP_IDLE_RIGHT;//dung sprite
			}
		}
		else 
		{
			if (BeingDownStair)
			{
				ani = SIMON_STATE_ONSTAIR_DOWN_IDLE_LEFT;//dung sprite
			}
			else 
			{
				ani = SIMON_STATE_ONSTAIR_DOWN_IDLE_RIGHT;//down right
			}

		}
	}
//	DebugOut(L"Lock onS:%d\n", this->IsOnStair);
	if (/*(ani == SIMON_STATE_ATTACK_RIGHT) || (ani == SIMON_STATE_ATTACK_LEFT)*/isAttacking)
	{
		if (!IsOnStair) 
		{
			if (nx > 0) ani = SIMON_STATE_ATTACK_RIGHT;
			else ani = SIMON_STATE_ATTACK_LEFT;
		}
		else {
			if (nx > 0) 
			{
				if (BeingDownStair)
				{
					ani = SIMON_STATE_ONSTAIR_UP_ATTACK_LEFT;//up left
				}
				else {
					ani = SIMON_STATE_ONSTAIR_UP_ATTACK_RIGHT;//dung sprite
				}
			}
			else {
				if (BeingDownStair)
				{
					ani = SIMON_STATE_ONSTAIR_DOWN_ATTACK_LEFT;//dung sprite
				}
				else
				{
					ani = SIMON_STATE_ONSTAIR_DOWN_ATTACK_RIGHT;//down right
				}

			}
		}
	}


	if (/*(ani == SIMON_STATE_CROUCHING_ATTACK_RIGHT) || (ani == SIMON_STATE_CROUCHING_ATTACK_LEFT)*/isAttacking &&!IDLE&&!IsOnStair)
	{
		CROUCHING_ATTACK = true;
		if (nx > 0) ani = SIMON_STATE_CROUCHING_ATTACK_RIGHT;
		else ani = SIMON_STATE_CROUCHING_ATTACK_LEFT;
	}
	state = ani;
	// Rendering depends on screen
	
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);

	if (EffectInvisible)
	{
		ani += 31;
		BossCantAttacked = false;
		BeingAttacked = false;
		if (GetTickCount() - EfffectInvisibleTime > SIMON_INVISIBLE_TIME)
		{
			EffectInvisible = false;
		}
	}

	 if (BeingAttacked) 
	 {
		//isJumpingForward = true;

		 if (IsOnStair)
		 {
			 vx = 0; vy = 0;
		 }
		 else
		 {
			 if (BeingAttackRight)
			 {
				 ani = SIMON_STATE_BEINGATTACKED_RIGHT;
				 vx = -SIMON_JUMPINGFORWARD_SPEED;
				 vy = -SIMON_JUMPINGFORWARD_SPEED_Y;
			 }
			 else
			 {
				 ani = SIMON_STATE_BEINGATTACKED_LEFT;
				 vx = SIMON_JUMPINGFORWARD_SPEED;
				 vy = -SIMON_JUMPINGFORWARD_SPEED_Y;
			 }
		 }
		 /*if(Invisible)
		 {
			 if (BeingAttackRight)
			 {
				 vx = -SIMON_JUMPINGFORWARD_SPEED;
			 }
			 else
			 {
				 vx = SIMON_JUMPINGFORWARD_SPEED;
			 }
			 vy = -SIMON_JUMPINGFORWARD_SPEED_Y;
		 }*/
		 if (GetTickCount() - CantBeingAttacked > SIMON_BEINGATTACKED_TIME) 
		 {
			 BeingAttacked = false;
			
		 }	
	 }
	 if (!BeingAttacked)
	 {
		 if (BossCantAttacked)
		 {
			 ani += SIMON_STATE_INVISIBLE;
		 }
		 if (GetTickCount() - CantBeingAttacked > SIMON_NOTBEINGATTACKED_TIME)
		 {
			 this->BossCantAttacked = false;
		 }
	 }
	  

	  //if (IDLE)
	  //{
		 // //if (vy != 0)
		 // {
			//  if ((ani==SIMON_STATE_WALKING_RIGHT)||(ani==SIMON_STATE_WALKING_LEFT))

			//  {
			//	  if (isFalling)
			//	  {
			//		  if (nx > 0)
			//		  {
			//			  ani = SIMON_STATE_JUMP_RIGHT;
			//		  }
			//		  else ani = SIMON_STATE_JUMP_LEFT;
			//	  }
			//  }
		 // }
	  //}
	  if (FlagIdle) {
		  ani = SIMON_STATE_IDLE_RIGHT;
	  }

	  if (GetItem)
	  {
		  isAttacking = false;
		  if (nx > 0)
		  {
			  ani = SIMON_STATE_EFFECT_RIGHT;
		  }
		  else
		  {
			  ani = SIMON_STATE_EFFECT_LEFT;
		  }
		  if (GetTickCount() - CantBeingAttacked > SIMON_EFFECT_TIME) 
		  {
			  this->GetItem = false;
		  }
	  }
	  //if (isFalling)
	  if (Life == 0)
	  {
		  ani = SIMON_STATE_DIE;
		  BeingAttacked = false;
		  vx = 0;
	  }
	  if (TheendBigBat)
	  {
		  this->SetPosition(2780, 65);

			  ani = SIMON_STATE_KILL_BIGBAT;
			  ResetPlay = true;
			  vy = 0;
			  animations[ani]->Render(pos.x, pos.y + 52);


	  }
	  else
	  {
		  if ((ani < animations.size()))
			  animations[ani]->Render(pos.x, pos.y + 55);
	  }

	//animations[ani]->Render((screen_x - SCREEN_WIDTH / 2), y+55);
	if (IsOnStair&&isAttacking)
	{
		if (nx>0)
			RenderWeapons(camera->GetX(), SCREEN_WIDTH, SIMON_STATE_ATTACK_RIGHT, this->GetX(), this->GetY(), CROUCHING_ATTACK);
		else
			RenderWeapons(camera->GetX(), SCREEN_WIDTH, SIMON_STATE_ATTACK_LEFT, this->GetX(), this->GetY(), CROUCHING_ATTACK);
	}else
	RenderWeapons(camera->GetX(), SCREEN_WIDTH, this->state , this->GetX(), this->GetY(), CROUCHING_ATTACK);

	for (int i = 0; i < healthsimon; i++)
	{
		healthsimon_ani[i]->Render(0);
	}
	for (int i = healthsimon; i < max_healthsimon; i++) {
		healthsimon_ani[i]->Render(1);
	}
	if (DoubleAttacking)
	{
		X2Attacking->Render_UI();
	}

	if (y > SIMON_FALLING_STAGE3_Y)
	{
		for (int i = 0; i < water.size(); i++)
		{
			water[i]->Render(camera->GetX(), SCREEN_WIDTH, this->GetX(), this->GetY());
		}
	}

}

void CSimon::SetState(int state, int TurnAttack)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case SIMON_STATE_WALKING_RIGHT:
		if (IsOnStair) return;
		//if (!axe->getDangBay())
		if (!MOVE /*&& !LockMoveLeftDoor&&!LockMoveRightDoor*/)
		{
			if (!BeingAttacked)
			{
				nx = 1;
				vx = SIMON_WALKING_SPEED;
			}
		}
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (IsOnStair)return;
		if (!MOVE /*&& !LockMoveLeftDoor&&!LockMoveRightDoor*/)
		{
			if (!BeingAttacked)
			{
				nx = -1;

				vx = -SIMON_WALKING_SPEED;

			}
		}
		/*}*/
		break;
	case SIMON_STATE_JUMP_LEFT:
		if (IsOnStair)break;
		/*if (!IsGoStair)
		{*/
		if (!MOVE)
		{
			if (!isFalling)
			{
				isFalling = true;
				vy = -SIMON_JUMP_SPEED_Y;
			}
		}
		//}
		break;
	case SIMON_STATE_JUMP_RIGHT:

		if (IsOnStair) {
			vx = 0;
			vy = 0;
			break;
		}

		//if (!IsGoStair)
		if (!MOVE)

		{
			if (!isFalling)
			{
				isFalling = true;
				vy = -SIMON_JUMP_SPEED_Y;
			}
		}
		break;
	case SIMON_STATE_IDLE_RIGHT:
		if (IsOnStair)
		{
			vx = 0;
			vy = 0;
			break;
		}
		/*if (!IsGoStair)*/
		{
			IDLE = true;
			vx = 0;

			//nx = 1;
		}
	
		break;
	case SIMON_STATE_IDLE_LEFT:
		if (IsOnStair) {
			vx = 0;
			vy = 0;
			break;
		}
		/*if (!IsGoStair)*/
		{
			IDLE = true;
			vx = 0;

			//vy = 0;
			//nx = -1;
		}
		break;
	case SIMON_STATE_CROUCH_RIGHT:
		if (IsOnStair)break;
		/*if (!IsGoStair)*/

		{
			//CROUCHING = true;
			IDLE = false;
			vx = 0;
			//nx = 1;
		}
		break;
	case SIMON_STATE_CROUCH_LEFT:
		if (IsOnStair)break;
		/*if (!IsGoStair)*/
		{
			IDLE = false;
			//CROUCHING = true;
			vx = 0;
			//nx = -1;
		}
		break;
	case SIMON_STATE_ATTACK_RIGHT:
		/*if (!isJumpingForward) vx = 0;
		isAttacking = true;
		attackingTime = GetTickCount();
		break;*/
	case SIMON_ACTTACK_MELEE:
		//if (IsOnStair)break;
		CGameObject::SetState(SIMON_STATE_ATTACK_LEFT);
		isAttacking = true;
		if (WeaponMelee > 0) {
			if (this->whip->GetBeingAttacking()) {
				return;
			}
		}

		this->whip->Attacking();
		/////////////////

		if (!isJumpingForward) vx = 0;
		if (IsOnStair) vx = 0, vy = 0;
		attackingTime = GetTickCount();

		break;
	case SIMON_ACTTACK_RANGE:
		//if (IsOnStair)break;
		CGameObject::SetState(SIMON_STATE_ATTACK_LEFT);
		isAttacking = true;
		if (this->knife->getLock() && this->axe->getLock() && holywater->getLock()&&bomerang->getLock())return;
		if (TurnAttack <= 0)return;
		if (WeaponRange > 0) {
			if (this->knife->GetIsBeingThrown()) return;
			if (this->axe->GetIsBeingThrown()) return;
			if (this->holywater->GetIsBeingThrown()) return;
			if (this->bomerang->GetIsBeingThrown()) return;

		}

		/////////////////
		this->StartThrown = true;
		TunrnActack = -1;
		TimeUpdate1 = GetTickCount();
		if (WeaponRange == NUMBER_KNIFE)
		{
			this->knife->SetPosition(this->x, this->y+5);
			if (this->knife->getLock())return;
			if (knife->GetIsBeingThrown() == false)
			{
				//this->knife->Phong();
				knife->SetIsBeingThrown(true);
			}


		}
		if (WeaponRange == NUMBER_AXE)
		{
			this->axe->SetPosition(this->x, this->y - 5);
			if (this->axe->getLock())return;
			if (axe->GetIsBeingThrown() == false)
			{
				//this->axe->Phong();
				axe->SetIsBeingThrown(true);
			}

		}
		if (WeaponRange == NUMBER_HOLYWATER)
		{

			this->holywater->SetPosition(this->x, this->y + 5);
			if (this->holywater->getLock())return;
			if (holywater->GetIsBeingThrown() == false)
			{
				//this->holywater->Phong();
				holywater->SetIsBeingThrown(true);
			}
		}
		if (WeaponRange == NUMBER_BOMERANG)
		{
			this->bomerang->SetPosition(this->x, this->y + 5);
			if (this->bomerang->getLock())return;
			if (bomerang->GetIsBeingThrown() == false)
			{
				//this->knife->Phong();
				bomerang->SetIsBeingThrown(true);
				//	TunrnActack = -1;
			}


		}
		if (!isJumpingForward) vx = 0;
		if (IsOnStair) vx = 0, vy = 0;
		attackingTime = GetTickCount();
		holywater->SetTurnOffFireTime(GetTickCount());
		break;
	case SIMON_STATE_CROUCHING_ATTACK_RIGHT:

	case SIMON_ACTTACK_CROUCH_MELEE:
		CGameObject::SetState(SIMON_STATE_CROUCHING_ATTACK_LEFT);
		isAttacking = true;
		IDLE = false;
		if (WeaponMelee > 0) {
			if (this->whip->GetBeingAttacking()) {
				return;
			}
		}

		this->whip->Attacking();

		if (!isJumpingForward) vx = 0;
		if (IsOnStair) vx = 0, vy = 0;
		attackingTime = GetTickCount();

		break;
	case SIMON_ACTTACK_CROUCH_RANGE:
		CGameObject::SetState(SIMON_STATE_CROUCHING_ATTACK_LEFT);
		if (TurnAttack <= 0)return;
		isAttacking = true;
		IDLE = false;
		TunrnActack = -1;
		TimeUpdate1 = GetTickCount();
		if (WeaponRange > 0) {
			if (this->knife->GetIsBeingThrown()) return;
			if (this->axe->GetIsBeingThrown()) return;
			if (this->holywater->GetIsBeingThrown()) return;
			if (this->bomerang->GetIsBeingThrown()) return;

		}

		this->StartThrown = true;
		if (WeaponRange == NUMBER_KNIFE)
		{
			this->knife->SetPosition(this->x, this->y + 15);
			if (this->knife->getLock())return;
			if (knife->GetIsBeingThrown() == false)
			{
				knife->SetIsBeingThrown(true);
			}


		}
		if (WeaponRange == NUMBER_AXE)
		{
			this->axe->SetPosition(this->x, this->y + 8);
			if (this->axe->getLock())return;
			if (axe->GetIsBeingThrown() == false)
			{
				axe->SetIsBeingThrown(true);
			}

		}
		if (WeaponRange == NUMBER_HOLYWATER)
		{
			this->holywater->SetPosition(this->x, this->y+10 );
			if (this->holywater->getLock())return;
			if (holywater->GetIsBeingThrown() == false)
			{
				holywater->SetIsBeingThrown(true);
			}
		}
		if (WeaponRange == NUMBER_BOMERANG)
		{
			this->bomerang->SetPosition(this->x, this->y + 15);
			if (this->bomerang->getLock())return;
			if (bomerang->GetIsBeingThrown() == false)
			{
				bomerang->SetIsBeingThrown(true);
			}


		}
		if (!isJumpingForward) vx = 0;
		if (IsOnStair) vx = 0, vy = 0;
		attackingTime = GetTickCount();
		holywater->SetTurnOffFireTime(GetTickCount());
		break;
	case SIMON_STATE_EFFECT_RIGHT:
		if (IsOnStair)break;
		nx = 1;
		this->CantBeingAttacked = GetTickCount();
		break;
	case SIMON_STATE_EFFECT_LEFT:
		if (IsOnStair)break;
		nx = -1;
		this->CantBeingAttacked = GetTickCount();
		break;
	case SIMON_STATE_BEINGATTACKED_RIGHT:
		//vx =0;
		nx = 1;
		this->BeingAttacked = true;
		this->BossCantAttacked = true;
		this->CantBeingAttacked = GetTickCount();
		break;
	case SIMON_STATE_BEINGATTACKED_LEFT:
		//vx =0;
		nx = -1;
		this->BeingAttacked = true;
		this->BossCantAttacked = true;
		this->CantBeingAttacked = GetTickCount();
		break;
	case SIMON_STATE_ONSTAIR_UP:
			if (this->CanGoStair == false && StartWalkingStair == false) return;
			this->StartWalkingStair = true;
			this->IsOnStair = true;
			if (!this->CanUpStair)// Tat di cau thang
			{
				this->StartWalkingStair = false;
				this->IsOnStair = false;
				return;
			}
			this->CanDownStair = true;
			this->BeingDownStair = false;
			//if (!DoiHuong)
			this->nx = DirectionXStair;
			if (this->nx > 0)
			{
				this->vx = SIMON_ONSTAIR_SPEED;
			}
			else 
			{
				if (this->nx < 0) {
					this->vx = -SIMON_ONSTAIR_SPEED;
				}
			}
			this->ny = DirectionYStair;
			if (this->ny > 0) 
			{
				this->vy = SIMON_ONSTAIR_SPEED;
			}
			else 
			{
				if (this->ny < 0) {
					this->vy = -SIMON_ONSTAIR_SPEED;
				}
			}
			break;
	case SIMON_STATE_ONSTAIR_DOWN:

		if (this->CanGoStair == false && StartWalkingStair == false) return;
			this->StartWalkingStair = true;
			this->IsOnStair = true;
			if (!this->CanDownStair)
			{
				this->StartWalkingStair = false;
				this->IsOnStair = false;
				return;
			}
			this->CanUpStair = true;
			this->BeingDownStair = true;
			////////////////////
			//if (!DoiHuong)
			this->nx = -1 * DirectionXStair;
			if (this->nx > 0) 
			{
				this->vx = SIMON_ONSTAIR_SPEED;
			}
			else {
				if (this->nx < 0) {
					this->vx = -SIMON_ONSTAIR_SPEED;
				}
			}
			this->ny = -1 * DirectionYStair;

			if (this->ny > 0) {
				this->vy = SIMON_ONSTAIR_SPEED;
			}
			else {
				if (this->ny < 0) {
					this->vy = -SIMON_ONSTAIR_SPEED;
				}
			}
		
		break;
	case SIMON_STATE_DIE:
		break;
	case SIMON_STATE_ONSTAIR_UP_IDLE_RIGHT:

		/*	vx = 0;
			nx = 1;*/
		break;
	case SIMON_STATE_ONSTAIR_DOWN_IDLE_LEFT:


		break;
	case SIMON_STATE_ONSTAIR_UP_ATTACK_RIGHT:

		break;
	case SIMON_STATE_ONSTAIR_DOWN_ATTACK_LEFT:

		break;
	case SIMON_STATE_ONSTAIR_UP_ATTACK_LEFT:

		break;
	case SIMON_STATE_ONSTAIR_DOWN_ATTACK_RIGHT:

		break;
	case SIMON_STATE_IDLE_INTRO:
		break;
	case SIMON_STATE_KILL_BIGBAT:
		
		break;
	}
	
}
void CSimon::SetWeaponRange(int vk)
{
	if (!this->knife->GetIsBeingThrown()||!this->axe->GetIsBeingThrown()||!this->holywater->GetIsBeingThrown()||!this->bomerang->GetIsBeingThrown()) // đang bay thì không được đổi vũ khí!
		this->WeaponRange = vk;
	if (vk == NUMBER_KNIFE)
		{
			if (!this->knife->GetIsBeingThrown())
				this->knife->SetPosition(x, y);
		}
	if (vk == NUMBER_AXE)
	{
		if (!this->axe->GetIsBeingThrown())
			this->axe->SetPosition(x, y);

	}
	if (vk == NUMBER_HOLYWATER)
	{
		if (!this->holywater->GetIsBeingThrown())
			this->holywater->SetPosition(x, y);

	}
	if (vk == NUMBER_BOMERANG)
	{
		if (!this->bomerang->GetIsBeingThrown())
			this->bomerang->SetPosition(x, y);
	}
	if (vk == SIMON_RESETWEAPONS)
	{
		knife->Unlock(false);
		axe->Unlock(false);
		holywater->Unlock(false);
		bomerang->Unlock(false);
	}
}
void CSimon::SetWeaponMelee(int vk)
{
	this->WeaponMelee = vk;
}
void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SIMON_WALKING_BBOX_WIDTH;
	bottom = y + SIMON_WALKING_BBOX_HEIGHT;
}

