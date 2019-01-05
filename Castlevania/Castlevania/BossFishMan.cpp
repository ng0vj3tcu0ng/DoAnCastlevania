#include "BossFishMan.h"



#define FISHMAN_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAFishMan.txt"


void CBossFishMan::RenderFireBall(float screen_x, int SCREEN_WIDTH, int FISHMAN_STATE, float fishman_x, float fishman_y)
{
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	if (this->fireball->GetIsBeingThrown())
	{
		
			fireball->Render(camera->GetX(), SCREEN_WIDTH, FISHMAN_STATE, this->GetX(), this->GetY());
	}
}

void CBossFishMan::UpdateFireBall(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (fireball->GetIsBeingThrown())
	{
		fireball->Update(dt, this->nx, this->x,this->DAttackingRight, colliable_objects);
	}
}

CBossFishMan::CBossFishMan(int x, int y)
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
	in.open(FISHMAN_INFOR_TXT_PATH);
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

	


	SetPosition(x, y);
	this->Type = TYPE_FISHMAN;
	Normal = true;
	Destroy = false;
	fireball = new FireBall();
	isAttacking = false;
	flag1 = true;
	DAttackingRight = false;
	isBeingThrown = false;
	OnMap = true;
	FirstAttacking = true;
	EffectWater *water_temp;

	for (int i = 0; i < 6; i++)
	{
		water_temp = new EffectWater();
		Water.push_back(water_temp);
	}
}

void CBossFishMan::BricksCollision(vector<LPGAMEOBJECT>* Brick)
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
		if (nx != 0) vx = -vx,nx=-nx;
		if (ny != 0&&y>60) y = 85;
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBossFishMan::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y ;
	right = x + FISHMAN_BBOX_WIDTH;
	bottom = y + FISHMAN_BBOX_HEIGHT;
}

void CBossFishMan::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects, vector<LPGAMEOBJECT> *Brick, float simon_x,float simon_y, int stage)
{
	{
		CGameObject::Update(dt);
		if (isAttacking&&FirstAttacking)
		{
			FirstAttacking = false;
			Objects->push_back(fireball);
		}
		if (!Normal) return;
		int d = sqrt((simon_x - x)*(simon_x - x) + (simon_y - y)*(simon_y - y));
		if (!fireball->GetIsBeingThrown() && d > 50)
		{
			isAttacking = true;
			SetState(FISHMAN_STATE_ATTACKING_RIGHT);
			attackingTime = GetTickCount();
		}
		if (simon_x > x)
		{
			DAttackingRight = true;
		}
		else DAttackingRight = false;
		if (isAttacking)
		{
			DWORD now = GetTickCount();
			if (d < 200)
			{
				if (now - FISHMAN_DELAY_ATTACKING1 > attackingTime)
				{
					isAttacking = false;
					if (DAttackingRight)
					{
						SetState(FISHMAN_STATE_WALKING_RIGHT);
					}
					else SetState(FISHMAN_STATE_WALKING_LEFT);
				}
			}
			else
			{
				if (now - FISHMAN_DELAY_ATTACKING2 > attackingTime)
				{
					isAttacking = false;
					if (DAttackingRight)
					{
						SetState(FISHMAN_STATE_WALKING_RIGHT);
					}
					else SetState(FISHMAN_STATE_WALKING_LEFT);

				}
			}
		}
		if (d < 130 && flag)
		{
			flag = false;
			vy = FISHMAN_STEPUP_Y;// cung cap van toc y de bay len
			this->Water[0]->Start(WATER1_VX, this->x, this->y, WATER_STEPUP1);
			this->Water[1]->Start(WATER2_VX, this->x, this->y, WATER_STEPUP2);
			this->Water[2]->Start(WATER3_VX, this->x, this->y, WATER_STEPUP1);		
			if (Right)
			{
				SetState(FISHMAN_STATE_WALKING_RIGHT);
			}
			else SetState(FISHMAN_STATE_WALKING_LEFT);
		}
		if (y > 145)
		{
			this->Water[3]->Start(WATER1_VX, this->x, this->y, WATER_STEPUP1);
			this->Water[4]->Start(WATER2_VX, this->x, this->y, WATER_STEPUP2);
			this->Water[5]->Start(WATER3_VX, this->x, this->y, WATER_STEPUP1);
		}
		if (x > 1980)
		{
			SetState(FISHMAN_STATE_WALKING_LEFT);
		}
		if (y < 45)
		{
			vy += GRAVITYFISHMAN * dt;
		}
		if (vx > 0)
		{
			nx = 1;
		}
		if (vx < 0)
		{
			nx = -1;
		}
		if (stage == 2 || stage == 1)
		{
			OnMap = false;
		}
		BricksCollision(Brick);
		this->UpdateFireBall(dt, Objects);

		
		for (int i = 0; i < Water.size(); i++)
		{
			Water[i]->Update(dt, Objects);
		}
	}
}
void CBossFishMan::Render(float camera_x, int SCREEN_WIDTH)
{

	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	if (y < 120)
	{
		if (Normal)
		{
			
			if (vx == 0)
			{
				if (nx > 0)
				{
					ani = FISHMAN_STATE_IDLE_RIGHT;
				}
				else
					ani = FISHMAN_STATE_IDLE_LEFT;

			}
			else
			{

				if (nx > 0)
				{
					ani = FISHMAN_STATE_WALKING_RIGHT;
					vx = FISHMAN_WALKING_SPEED;
				}
				else
				{
					ani = FISHMAN_STATE_WALKING_LEFT;
					vx = -FISHMAN_WALKING_SPEED;
				}
			}
			if (isAttacking)
			{
				vx = 0;
				if (DAttackingRight)
				{
					ani = FISHMAN_STATE_ATTACKING_RIGHT;
				}
				else
				{
					ani = FISHMAN_STATE_ATTACKING_LEFT;
				}
			}
			
			this->StartDestroy = GetTickCount();
		}
		else {
			ani = FISHMAN_STATE_EFFECT_DIE;
		}
		animations[ani]->Render(pos.x, pos.y + 55);
		
	}
	if (!Normal&&GetTickCount() - this->StartDestroy > FISHMAN_DESTROY_TIME) {
		Destroy = true;
	}
	if (isAttacking)
	{
		RenderFireBall(camera->GetX(), SCREEN_WIDTH, this->state, this->GetX(), this->GetY());
	}
	
		for (int i = 0; i < Water.size(); i++)
		{
			Water[i]->Render(camera->GetX(),SCREEN_WIDTH,this->GetX(),this->GetY());
		}
}


void CBossFishMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISHMAN_STATE_IDLE_RIGHT:
		vx = 0;
		nx = 1;
		Right = true;
		break;
	case FISHMAN_STATE_IDLE_LEFT:
		vx = 0;
		nx = -1;
		Right = false;
		break;
	case FISHMAN_STATE_WALKING_RIGHT:
		vx = FISHMAN_WALKING_SPEED;
		nx = 1;
		break;
	case FISHMAN_STATE_WALKING_LEFT:

		vx = -FISHMAN_WALKING_SPEED;
		nx = -1;
		break;
	case FISHMAN_STATE_ATTACKING_RIGHT:
		IDLE = false;

		nx = 1;
			this->fireball->SetPosition(this->x + 15, this->y+5);
			if (fireball->GetIsBeingThrown() == false)
			{
				fireball->SetIsBeingThrown(true);
			}
			attackingTime = GetTickCount();
		
		break;
	case FISHMAN_STATE_ATTACKING_LEFT:
		IDLE = false;
		nx = -1;
			this->fireball->SetPosition(this->x+15, this->y+5);
			if (fireball->GetIsBeingThrown() == false)
			{
				fireball->SetIsBeingThrown(true);
			}
			attackingTime = GetTickCount();
		
		break;
	}
}
bool CBossFishMan::DoesExist()
{
	return !(!OnMap);
}
