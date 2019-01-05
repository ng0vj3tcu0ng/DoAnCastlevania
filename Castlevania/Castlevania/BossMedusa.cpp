#include "BossMedusa.h"


#define MEDUSA_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAMedusa.txt"

CBossMedusa::CBossMedusa(int x, int y)
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
	in.open(MEDUSA_INFOR_TXT_PATH);
	string link;
	while (1) {
		in >> action>>n;
		if (action == -1)break;
		switch (action) {
		case 0:// tex 
			int r, g, p;
			int id;
			for (int i = 0; i < n; i++) 
			{
				in >> id>>r>>g>>p>>link;
				LPCWSTR s = convStringToLPCWSTR(link);
				textures->Add(id, s, D3DCOLOR_XRGB(r,g,p));
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



	this->SetState(MEDUSA_STATE_IDLE);
	SetPosition(x, y);
	this->Type = TYPE_MEDUSA;
	Normal = true;
	Destroy = false;
	flag = true;
	Active = false;
	OnScreen = true;
	Delete = false;
	First = false;
}

void CBossMedusa::BricksCollision(vector<LPGAMEOBJECT>* Brick)
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
		x += 0;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0)
		{
			if (vx > 0)
			{
				SetState(MEDUSA_STATE_WALKING_LEFT);
			}
			else SetState(MEDUSA_STATE_WALKING_RIGHT);		
		}
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBossMedusa::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MEDUSA_BBOX_WIDTH;
	bottom = y + MEDUSA_BBOX_HEIGHT;
}

void CBossMedusa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> *Brick, float camera_x,int state, float simon_x,float simon_y)
{
	{
		CGameObject::Update(dt);
		vy += GRAVITYMEDUSA * dt;
		int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
		if (vx != 0)
		{
			Active = true;
		}
		if (!Normal) return;

		if (d < MEDUSA_DISTANCE_UPDATE_RENDER && !First)
		{
			First = true;
			SetState(MEDUSA_STATE_WALKING_LEFT);
		}
		if (Active)
		{
			if (abs(x-camera_x)>300)
			{
				OnScreen = false;
			}
		}

		if (camera_x > 1550)
		{
			if (x < 1550)
			{
				if (abs(x - camera_x) > MEDUSA_DISTANCE_UPDATE_RENDER)
				{
					OnScreen = false;
				}
			}
		}
		BricksCollision(Brick);
	}
}
void CBossMedusa::Render(float camera_x, int SCREEN_WIDTH)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d < MEDUSA_DISTANCE_UPDATE_RENDER)
	{
		if (Normal) 
		{
			if (vx == 0)
			{
				ani = MEDUSA_STATE_IDLE;
			}
			else
			{
				if (nx > 0)
				{
					ani = MEDUSA_STATE_WALKING_RIGHT;
				}
				else
				{
					ani = MEDUSA_STATE_WALKING_LEFT;
				}
			}
			
			this->StartDestroy = GetTickCount();
		}
		else {
			ani = MEDUSA_STATE_EFFECT;
		}
		animations[ani]->Render(pos.x, pos.y + 55);

		if (!Normal&&GetTickCount() - this->StartDestroy > MEDUSA_DESTROY_TIME) {
			Destroy = true;
		}
	}
}



void CBossMedusa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MEDUSA_STATE_IDLE:

		break;
	case MEDUSA_STATE_WALKING_RIGHT:	
		vx = MEDUSA_WALKING_SPEED;
		nx = 1;
		break;
	case MEDUSA_STATE_WALKING_LEFT:
		vx = -MEDUSA_WALKING_SPEED;
		nx = -1;
		break;
	}
}
bool CBossMedusa::DoesExist()
{
	return !(Active&&!OnScreen);
}