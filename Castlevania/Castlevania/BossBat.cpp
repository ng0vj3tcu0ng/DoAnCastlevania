#include "BossBat.h"

#define BAT_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSABat.txt"

CBossBat::CBossBat(int x, int y)
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
	in.open(BAT_INFOR_TXT_PATH);
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


	//this->SetType(24);
	this->SetState(BAT_STATE_IDLE);


	SetPosition(x, y);
	this->Type = TYPE_BAT;
	Normal = true;
	Destroy = false;
	OnScreen = true;
}

void CBossBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y + 5;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBossBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, float camera_x,int state,float simon_x,float simon_y)
{
	
	CGameObject::Update(dt);
	if (!Normal) return;
	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d > 250)
	{
		return;
	}
	else 
	{
		SetState(BAT_STATE_FLYING_LEFT);
		x += vx*dt ;
		vy = sin(x*PI/60)*BAT_FLYING_SPEEDY;
		y += vy*dt; 
	}
	int d1 = sqrt((simon_x - x)*(simon_x - x) + (simon_y - y)*(simon_y - y));
	if (d1 >150 && x < simon_x)
	{
		OnScreen = false;
	}
	

	//BricksCollision(Brick);
}

void CBossBat::Render(float camera_x, int SCREEN_WIDTH)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	if (Normal)
	{
		if (vx == 0)
		{
			ani = BAT_STATE_IDLE;
		}
		else
		{
			if (nx > 0)
			{
				ani = BAT_STATE_FLYING_RIGHT;

			}
			else ani = BAT_STATE_FLYING_LEFT;

				

			this->StartDestroy = GetTickCount();
		}
	}
	else {
		ani = BAT_STATE_EFFECT;
	}
	animations[ani]->Render(pos.x, pos.y + 55);
	if (!Normal&&GetTickCount() - this->StartDestroy > BAT_DESTROY_TIME) {
		Destroy = true;
	}
}



void CBossBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_IDLE:
		vx = 0;
		break;

	case BAT_STATE_FLYING_RIGHT:
		vx = BAT_WALKING_SPEED;
		nx = 1;
		break;
	case BAT_STATE_FLYING_LEFT:
		vx = -BAT_WALKING_SPEED;
		nx = -1;
		break;
	case BAT_STATE_EFFECT:

		break;
	}
}
bool CBossBat::DoesExist()
{
	return !(!OnScreen);
}
