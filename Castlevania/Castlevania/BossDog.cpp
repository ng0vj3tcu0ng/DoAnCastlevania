#include "BossDog.h"


#define DOG_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSADog.txt"

CBossDog::CBossDog(int x, int y)
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
	in.open(DOG_INFOR_TXT_PATH);
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

	this->SetState(DOG_STATE_IDLE_LEFT);
	//this->SetType(43);
	this->SetSpeed(0, 0);



	SetPosition(x, y);
	this->Type = TYPE_DOG;
	Normal = true;
	Destroy = false;
	flag = true;
	flag1 = true;
	Active = false;
	OnScreen = true;
	ChangeDirec = false;
}

void CBossDog::BricksCollision(vector<LPGAMEOBJECT>* Brick)
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

		if (nx != 0) flag1=false;
		if (ny != 0) vy=0;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBossDog::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y+5 ;
	right = x + DOG_BBOX_WIDTH;
	bottom = y + DOG_BBOX_HEIGHT;
}

void CBossDog::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *Brick, float simon_x,float simon_y, int state)
{
	
	{

		CGameObject::Update(dt);
		vy += GRAVITYDOG * dt;
		x += dx;
		if (!Normal) return;
		//if (Active)
		/*{
			vy += 0.003f;
		}*/
		int d = sqrt((simon_x - x)*(simon_x - x) + (simon_y - y)*(simon_y - y));
		if (d < DOG_DISTANCE_UPDATE_RENDER && flag)
		{
			flag = false;
			SetState(DOG_STATE_WALKING_LEFT);
		}
		if (y>143)
		{
			SetState(DOG_STATE_WALKING_RIGHT);
			vy = 0;
		}
		if (Active)
		{
			if (x>simon_x+200)
			{
				OnScreen = false;
			}
		}


		BricksCollision(Brick);
	}
}

void CBossDog::Render(float camera_x, int SCREEN_WIDTH)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d < DOG_DISTANCE_UPDATE_RENDER*3)
	{
		if (Normal)
		{
			if (vx == 0)
			{
				if (nx > 0)
				{
					ani = DOG_STATE_IDLE_RIGHT;
					vy = 0;

				}
				else {
					vy = 0;
					ani = DOG_STATE_IDLE_LEFT;
				}
			}
			else
			{
					if (nx > 0)
					{
						ani = DOG_STATE_WALKING_RIGHT;
					}
					else
					{
						ani = DOG_STATE_WALKING_LEFT;
						
					}		
			}
	
			if (y < 142 && y>80)
				{
					ani = DOG_STATE_FALLING;
				}
			

				this->StartDestroy = GetTickCount();

			animations[ani]->Render(pos.x, pos.y + 55);
		}
		else
		{
			ani = DOG_STATE_EFFECT;
			vx = 0;
			vy = 0;
			animations[ani]->Render(pos.x, pos.y + 45);
		}
	}

	if (!Normal&&GetTickCount() - this->StartDestroy > DOG_DESTROY_TIME) {
		Destroy = true;
	}	
}



void CBossDog::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOG_STATE_IDLE_RIGHT:
		vx = 0;
		break;
	case DOG_STATE_IDLE_LEFT:
		vx = 0;
		break;
	case DOG_STATE_WALKING_RIGHT:
		vx = DOG_WALKING_SPEED;
		nx = 1;
		break;
	case DOG_STATE_WALKING_LEFT:
		Active = true;
		vx = -DOG_WALKING_SPEED;
		nx = -1;
		break;

	}
}
bool CBossDog::DoesExist()
{
	return !(Active&&!OnScreen);
}
