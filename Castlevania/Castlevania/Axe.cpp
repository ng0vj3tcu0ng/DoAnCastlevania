#include "Axe.h"

#define ID_TEX_AXE_WEAPONS 30
#define AXE_WEAPONS_TEXTURE_PATH    L"Objects\\Items.png"
#define AXE_WEAPONS_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(128, 0, 0)

#define AXE_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAAxe.txt"

CAXE::CAXE()
{
	isBeingThrown = false;
	
	LoadWeapon();
	lock = true;
	//this->isBeingFly = false;
}
void CAXE::LoadWeapon()
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
	in.open(AXE_INFOR_TXT_PATH);
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
void CAXE::CandelCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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
void CAXE::BossMedusaCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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
void CAXE::BossDogCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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
void CAXE::BossBatCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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
void CAXE::BossFishManCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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

void CAXE::BossBigBatCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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

void CAXE::FireBallCollision(Grid *map, vector<LPGAMEOBJECT>* Objects)
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
void CAXE::Update(DWORD dt, int nx, int xx,int yy, bool &StartThrown,Grid *map, vector<LPGAMEOBJECT> *Objects)
{
	vy += GRAVITYAXE * dt;
	if (StartThrown) {
		this->nx = nx;
		StartThrown = false;
	}
	if (y> AXE_RESET_Y && isBeingThrown) {
		isBeingThrown = false;
		//this->isBeingFly = false;
		vx = 0;
		return;
	}

	if (vx==0)
	{
			if (this->nx > 0)
			{
				vx = AXE_SPEED_X;
			}
			else 
			{
				vx = -AXE_SPEED_X;		
			}
			vy = -AXE_SPEED_Y;

	}
	CGameObject::Update(dt);
	

	if (!lock) {
		// No collision occured, proceed normally
			x += dx;
			y += dy;
			BossMedusaCollision(map, Objects);
			BossBatCollision(map, Objects);
			BossDogCollision(map, Objects);
			CandelCollision(map, Objects);
			BossMedusaCollision(map, Objects);
			BossBigBatCollision(map, Objects);
			BossFishManCollision(map, Objects);
			FireBallCollision(map, Objects);
		//reset 
		if (!isBeingThrown) 
		{
			return;
		}

		// clean up collision events
	}
}

void CAXE::Render(float screen_x, int SCREEN_WIDTH, int SIMON_STATE, float simon_x, float simon_y, bool CROUCHING_ATTACK)
{
	if (!lock) {

		SetState(SIMON_STATE);
		//if (state % 2 == 0) CGameObject::SetPosition(simon_x, simon_y);
		//else CGameObject::SetPosition(simon_x + 9, simon_y);
		//if (CROUCHING_ATTACK) CGameObject::SetPosition(x, y + 7);
		int ani = state;
		if (isBeingThrown)
		{
			if (nx > 0)
			{
				ani = AXE_STATE_THROW_RIGHT;
				
			}
			else
			{
				ani = AXE_STATE_THROW_LEFT;
			}
			animations[ani]->Render(x - (screen_x - SCREEN_WIDTH / 2), y + 60);

		}
		else 
		{
			ani = AXE_STATE_IDLE;
			animations[ani]->Render(x, y+60 );
			/*animations[0]->Render(x, y + 60);*/
		}


	}
}
void CAXE::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case AXE_STATE_IDLE:
		break;
	case AXE_STATE_THROW_RIGHT:
		nx = 1;
		break;
	case AXE_STATE_THROW_LEFT:
		nx = -1;
		break;
	}
}
void CAXE::Render_UI()
{
	animations[AXE_STATE_IDLE]->Render(130, 22);
}
void CAXE::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y + 10;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}