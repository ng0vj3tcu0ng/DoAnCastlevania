#include "Whip.h"

#define WHIP_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAWhip.txt"

void Whip::Attacking()
{
	this->BeingAttacking = true;
}

Whip::Whip()
{
	LoadWeapon(0);
	this->Level = 0;
}

void Whip::LoadWeapon(int WeaponType)
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
	in.open(WHIP_INFOR_TXT_PATH);
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

void Whip::LevelUp()
{
	if (this->Level<WHIP_MAXLEVER)
		Level++;
}
void Whip::Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y,bool CROUCHING_ATTACK)
{	

	SetState(SIMON_STATE);
	if (state % 2 == 1) SetPosition(simon_x - 43, simon_y);
		else SetPosition(simon_x - 16, simon_y);	
	
	if (state < 8 || state >11 )
	{
		this->BeingAttacking = false;
		// reset all animations when simon doesn't attack
		animations[WHIP_ANI_LEVE1_RIGHT]->SetCurrentFrame(-1);
		animations[WHIP_ANI_LEVE1_LEFT]->SetCurrentFrame(-1);
		animations[WHIP_ANI_LEVE2_RIGHT]->SetCurrentFrame(-1);
		animations[WHIP_ANI_LEVE2_LEFT]->SetCurrentFrame(-1);
		animations[WHIP_ANI_LEVE3_RIGHT]->SetCurrentFrame(-1);
		animations[WHIP_ANI_LEVE3_LEFT]->SetCurrentFrame(-1);
		return;

	}
	if (CROUCHING_ATTACK) SetPosition(x, y + 7);
	int ani = state % 2 + this->Level * 2;
	animations[ani]->Render(x - (screen_x - SCREEN_WIDTH / 2), y+55);
}
void Whip::CandelCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < Objects->size(); i++)
		if (dynamic_cast<Candle *>(Objects->at(i)))
			coObjects.push_back(Objects->at(i));*/

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
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::BrickHiddenCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < Objects->size(); i++)
		if (dynamic_cast<BrickHidden *>(Objects->at(i)))
			coObjects.push_back(Objects->at(i));

	CalcPotentialCollisions(&coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<BrickHidden *>(e->obj))
		{
			BrickHidden *brickhidden = dynamic_cast<BrickHidden *>(e->obj);
			if (e->nx != 0 || e->ny != 0)
			{
				brickhidden->SetNormal(false);
			}
		}
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::BossMedusaCollision(Grid *map,vector<LPGAMEOBJECT>* Objects)
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
			}

		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void Whip::BossDogCollision(Grid *map,vector<LPGAMEOBJECT>* Objects)
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
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::BossBatCollision(Grid *map,vector<LPGAMEOBJECT>* Objects)
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
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::BossFishManCollision(Grid *map,vector<LPGAMEOBJECT>* Objects)
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
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::BossBigBatCollision(Grid *map,vector<LPGAMEOBJECT>* Objects)
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

				//bossbigbat->SetBlood(bossbigbat->GetBlood() + 1);
				bossbigbat->SetBeingAttacking(true);
			}

		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Whip::FireBallCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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

void Whip::Update(DWORD dt, int nx,Grid *map, vector<LPGAMEOBJECT> *Objects)
{
	//if (state < 8 || state > 11) return;
	if (Level == 0 || Level == 1)
	{
		if (animations[state % 2 + Level * 2]->GetCurrentFrame() != 2) return;
	}
	else
	{
		if (animations[state % 2 + Level * 2]->GetCurrentFrame() != 4) return;
	}


		// Collision logic with candles
	BossMedusaCollision(map, Objects);
	BossBatCollision(map, Objects);
	BossDogCollision(map, Objects);
	CandelCollision(map,Objects);
	BossFishManCollision(map, Objects);
	BossBigBatCollision(map, Objects);
	BrickHiddenCollision(map, Objects);
	FireBallCollision(map, Objects);
	// clean up collision events
	//dogcollision(Dogg);
}

void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	int ani = state % 2+this->Level*2;
	switch (ani) {
	case 0:
		{
			left = x + 16 + 16;
			top = y + 6;
			right = left + 28;
			bottom = y + 8;
			break;
		}
	case 1:
		{
			left = x;
			top = y + 6;
			right = left + 28;
			bottom = top + 8;
			break;
		}
	case 2:
		{
			left = x + 16 + 16;
			top = y + 6;
			right = left + 28;
			bottom = top + 8;
			break;
		}
	case 3:
		{
			left = x;
			top = y + 6;
			right = left + 28;
			bottom = top + 8;
			break;
		}
	case 4:
		{
			left = x /*+ 16 */+ 40;
			top = y + 6;
			right = left+30;
			bottom = top + 8;
			break;
		}
	case 5:
		{
			left = x-5;
			top = y + 6;
			right = left + 30;
			bottom = top + 8;
			break;
		}
	}
}

