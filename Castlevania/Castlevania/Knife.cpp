#include "Knife.h"


#define KNIFE_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAKnife.txt"

Knife::Knife()
{
	isBeingThrown = false;
	
	LoadWeapon();
	lock = true;
	//this->isBeingFly = false;
}
void Knife::LoadWeapon()
{
	CTextures * textures = CTextures::GetInstance();

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	//LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPANIMATION ani;
	ifstream in;
	int action;
	int n;
	int left = 0, top = 0, right = 0, bottom = 0, idsprites = 0, idtxt = 0;
	int idAni = 0, defaultTime = 0, nSprites = 0, idSprites = 0;
	in.open(KNIFE_INFOR_TXT_PATH);
	string link;
	while (1) {
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

void Knife::CandelCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<Candle *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<Candle *>(e->obj))
		{
			Candle *candle = dynamic_cast<Candle *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				candle->SetNormal(false);
				isBeingThrown = true;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Knife::BossMedusaCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBossMedusa *>(e->obj))
			{
				CBossMedusa *bossmedusa = dynamic_cast<CBossMedusa *>(e->obj);
				if (e->nx != 0 || e->ny != 0)
				{
					bossmedusa->SetNormal(false);
					isBeingThrown = true;
				}
			}
		}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Knife::BossDogCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossDog *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CBossDog *>(e->obj))
		{
			CBossDog *bossdog = dynamic_cast<CBossDog *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				bossdog->SetNormal(false);
				isBeingThrown = true;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Knife::BossBatCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossBat *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CBossBat *>(e->obj))
		{
			CBossBat *bossbat = dynamic_cast<CBossBat *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				bossbat->SetNormal(false);
				isBeingThrown = true;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Knife::BossFishManCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossFishMan *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CBossFishMan *>(e->obj))
		{
			CBossFishMan *bossfishman = dynamic_cast<CBossFishMan *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				bossfishman->SetNormal(false);
				isBeingThrown = true;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Knife::BossBigBatCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<CBossBigBat *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CBossBigBat *>(e->obj))
		{
			CBossBigBat *bossbigbat = dynamic_cast<CBossBigBat *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				bossbigbat->SetBeingAttacking(true);
				isBeingThrown = true;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Knife::FireBallCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<int> ID = map->GetIdInGrid(this->x/SCREEN_WIDTH_HALF);
	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < ID.size(); i++)
		if (ID[i] < Objects->size())
			if (dynamic_cast<FireBall *>(Objects->at(ID[i])))
				coObjects.push_back(Objects->at(ID[i]));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<FireBall *>(e->obj))
		{
			FireBall *fireball = dynamic_cast<FireBall *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				fireball->SetNormal(false);
			}

		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Knife::Render_UI()
{
 
	animations[KNIFE_STATE_IDLE]->Render(130, 22);
	//animations[1]->Render(132, 23);
}

void Knife::Update(DWORD dt, int nx,int xx, bool &StartThrown, Grid *map, vector<LPGAMEOBJECT> *Objects)
{	
	//if (Unlock)
	//{
	//	
	//}
	if (StartThrown) {
		this->nx = nx;
		StartThrown = false;
	}
	if (abs(xx - this->x) > KNIFE_RESET_X && isBeingThrown ) {
		isBeingThrown = false;
		vx = 0;
		return;
	}
	if (vx == 0)
	{
		if (nx > 0) {
			vx = KNIFE_SPEED_X;
		}
		else {
			vx = -KNIFE_SPEED_X;
		}
		vy = -KNIFE_SPEED_Y;

	}
	CGameObject::Update(dt);
	
	if (!lock) {


		// No collision occured, proceed normally
			x += dx;
			y += dy;
			BossMedusaCollision(map,Objects);
			BossBatCollision(map, Objects);
			BossDogCollision(map, Objects);
			CandelCollision(map, Objects);
			BossMedusaCollision(map, Objects);
			BossBigBatCollision(map, Objects);
			BossFishManCollision(map, Objects);
			FireBallCollision(map, Objects);
		//reset 
		if (!isBeingThrown) {
			//SetPosition(100, -30);
			//this->isBeingFly = false;
			return;
		}
		    
		// clean up collision events
	}
}

void Knife::Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y,bool CROUCHING_ATTACK)
{

	if (!lock) 
	{
		SetState(SIMON_STATE);

		int ani = state % 2;
		if (isBeingThrown)
		{

			if (nx > 0)
			{
				ani = KNIFE_STATE_THROW_RIGHT;
			}
			else
			{
				ani = KNIFE_STATE_THROW_LEFT;
				//animations[2]->Render(x - (screen_x - SCREEN_WIDTH / 2), y + 60);
			}

			animations[ani]->Render(x - (screen_x - SCREEN_WIDTH / 2), y+50 );

		}
		else		
		{
			ani = KNIFE_STATE_IDLE;
			animations[ani]->Render( x, y+50);
		}
	}
}

void Knife::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KNIFE_BBOX_WIDTH;
	bottom = y + KNIFE_BBOX_HEIGHT;
}