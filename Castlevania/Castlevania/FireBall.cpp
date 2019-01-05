#include "FireBall.h"


#define FIREBALL_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAFireBall.txt"


FireBall::FireBall()
{
	LoadWeapon();
	isBeingThrown = false;
	Normal = true;
	Destroy = false;
	this->Type = TYPE_FIREBALL;

}
void FireBall::LoadWeapon()
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
	in.open(FIREBALL_INFOR_TXT_PATH);
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


void FireBall::Update(DWORD dt, int nx, int xx, bool &Direction, vector<LPGAMEOBJECT>* coObjects)
{
	if (abs(xx - this->x) > 650)
	{
		isBeingThrown = false;
		vx = 0;
		return;
	}
	if (!Normal)
	{
		return;
	}
	{
		if (vx == 0 )
		{
			if (Direction)
			{
				vx = FIREBALL_SPEED_X;
			}
			else vx = -FIREBALL_SPEED_X;
			vy = FIREBALL_SPEED_Y;
		}
		CGameObject::Update(dt);


		// No collision occured, proceed normally
		x += vx * dt;

		//y += dy;

		//reset 
		if (!isBeingThrown) {

			return;
		}
	

		// clean up collision events
	}
	//DebugOut(L"fireball y %f\n", this->y);
}
void FireBall::Render(float screen_x, int SCREEN_WIDTH, int FISHMAN_STATE,float fishman_x, float fishman_y)
{ 
	SetState(FISHMAN_STATE);

	int ani = state % 2;
	if (y < 80)
	{
		if (Normal)
		{
			if (isBeingThrown)
			{
				if (nx > 0)
				{
					ani = FIREBALL_STATE_THROW_RIGHT;
				}
				else
				{
					ani = FIREBALL_STATE_THROW_LEFT;
					//animations[2]->Render(x - (screen_x - SCREEN_WIDTH / 2), y + 60);
				}

				animations[ani]->Render(x - (screen_x - SCREEN_WIDTH / 2), y + 55);
			}
		}
		if (!Normal&&GetTickCount() - this->StartDestroy > FIREBALL_DESTROY_TIME)
		{
			ani = FIREBALL_STATE_EFFECT;
			Destroy = true;
			animations[ani]->Render(x - (screen_x - SCREEN_WIDTH / 2), y + 45);
		}

		

	}
}
void FireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + FIREBALL_BBOX_WIDTH;
	bottom = y + FIREBALL_BBOX_HEIGHT;
}