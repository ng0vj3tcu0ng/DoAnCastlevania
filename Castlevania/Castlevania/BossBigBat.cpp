#include "BossBigBat.h"



#define BIGBAT_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSABigBat.txt"

CBossBigBat::CBossBigBat(float x, float y,int itemType)
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
	in.open(BIGBAT_INFOR_TXT_PATH);
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


	this->SetState(BIGBAT_STATE_IDLE);





	SetPosition(x, y);
	this->itemType = itemType;
	this->Type = TYPE_BIGBAT;
	status = 0;
	XDes = x;
	YDes = y;
	Normal = true;
	ReSetHeath = false;
	BeingAttacking = false;
	DoubleAttacking = 1;
	Active = false;
	max_healthboss = BIGBAT_HEALTHMAX;
	Blood = max_healthboss;
	for (int i = 0; i < max_healthboss; i++) 
	{
		HealthBoss *temp = new HealthBoss();
		temp->SetPosition(56 + i * 4, 30);
		this->healthB_ani.push_back(temp);
	}
}


void CBossBigBat::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects, int SCREEN_WIDTH, float camera_x, float simon_x, float simon_y, bool DoubleAttack, bool ReSetHeath)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
	if (DoubleAttack)
	{
		DoubleAttacking = 2;
	}

	if (simon_x - x > BIGBAT_DISTANCE_ACTIVE)
	{
		Active = true;
	}
	if (BeingAttacking||!Normal) // Dung Im
	{
		SetSpeed(0, 0);
	}
	else
	{
		SetSpeed(newVx, newVy);
	}



	if (Active)
	{
		switch (status)
		{
		case 0:
			if ((abs(x - XDes) < 5) && abs(y - YDes) < 5) // Bay Tren Dau cua Simon
			{
				XDes = simon_x - 20;
				YDes = simon_y - 90;
				newVx = (XDes - x) / BIGBAT_FLYING_TIME1; //v=s/t
				newVy = (YDes - y) / BIGBAT_FLYING_TIME1;
				SetSpeed(newVx, newVy);
				status = 1;

			}
		case 1:
			if ((abs(x - XDes) < 5) && abs(y - YDes) < 5)  // Bay qua Ben Trai cua Simon
			{
				XDes = max(simon_x - 70, camera_x - SCREEN_WIDTH / 2 - 20);
				YDes = simon_y - 60;
				newVx = (XDes - x) / BIGBAT_FLYING_TIME2;
				newVy = (YDes - y) / BIGBAT_FLYING_TIME2;
				SetSpeed(newVx, newVy);
				status++;
			}
		case 2:
			if ((abs(x - XDes) < 5) && abs(y - YDes) < 5)  // Bay vao Simon
			{
				timerandom = rand() % 401 + 600;
				XDes = simon_x - 10;
				YDes = simon_y + 20;
				newVx = (XDes - x) / timerandom;
				newVy = (YDes - y) / timerandom;
				SetSpeed(newVx, newVy);
				status++;
			}
		case 3:
			if ((abs(x - XDes) < 5) && abs(y - YDes) < 5) // Bay qa phai Simon
			{
				XDes = min(simon_x + 50, camera_x - SCREEN_WIDTH / 2 + 220);
				YDes = simon_y - 60;
				newVx = (XDes - x) / BIGBAT_FLYING_TIME2;
				newVy = (YDes - y) / BIGBAT_FLYING_TIME2;
				SetSpeed(newVx, newVy);
				status = rand() % 2 + 0;
			}
		}
	}
	if (Blood <= 0)
	{
		Normal = false;
	}
	if (Blood == 1)
	{
		DoubleAttacking = 1;
	}
	if (ReSetHeath)
	{
		Blood = BIGBAT_HEALTHMAX;
		ReSetHeath = false;
	}
}

void CBossBigBat::Render(float camera_x, int SCREEN_WIDTH)
{

	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	if (!BeingAttacking && Active)
	{
		state = BIGBAT_STATE_FLYING;
		TurnOffAttacking = GetTickCount();
	}
	if (BeingAttacking)
	{
		state = BIGBAT_STATE_BEATTACKING;
		
	}
	if (BeingAttacking&&GetTickCount() - this->TurnOffAttacking > BIGBAT_BEINGATTACKING_TIME)
	{
		BeingAttacking = false;
		if (Blood >0)
			Blood-= DoubleAttacking;
		
	}

	if (Normal)
	{
		StartDestroy = GetTickCount();
	}
	else
	{
		state = BIGBAT_STATE_EFFECT;
		vx = 0;
		vy = 0;
	}
	
	if (!Normal&&GetTickCount() - this->StartDestroy > BIGBAT_DESTROY_TIME) 
	{

		Destroy = true;
	}	
	animations[state]->Render(pos.x, pos.y + 55);

	for (int i = 0; i < Blood; i++)
	{
		healthB_ani[i]->Render(0);
	}
	for (int i = Blood; i < max_healthboss; i++) 
	{
		healthB_ani[i]->Render(1);
	}
}


void CBossBigBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 16;
	top = y;
	right = left + BIGBAT_BBOX_WIDTH;
	bottom = top + BIGBAT_BBOX_HEIGHT;
}
void CBossBigBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BIGBAT_STATE_IDLE:

		break;
	case BIGBAT_STATE_FLYING:

		break;
	case BIGBAT_STATE_BEATTACKING:
		break;

	case BIGBAT_STATE_EFFECT:
		break;

	}
}
