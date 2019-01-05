#include "BreakingWall.h"


#define BREAKINGWALL_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSABreakingWall.txt"


EffectBWall::EffectBWall()
{
	LoadEffect();
	SetSpeed(0, 0);
	//this->isBeingThrown = true;
	isFalling = false;
	this->flag_Start = false;
	nx = 0;
	StarThrown = 0;
	vx = 0;
	vy = 0;

}
void EffectBWall::Start(float vx, int x, int y, int StepUp)
{
	if (!this->flag_Start)
	{
		this->flag_Start = true;
		this->vx = vx;
		this->x = x;
		this->y = y;
		this->StepUp = StepUp;
		StarThrown = 1;
	}
}
void EffectBWall::LoadEffect()
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
	in.open(BREAKINGWALL_INFOR_TXT_PATH);
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


void EffectBWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	CGameObject::Update(dt);

	this->y += dy;
	this->x += dx;

	if (!isFalling)
		vy -= GRAVITYBWALL * StarThrown*dt;
	else {
		vy += GRAVITYBWALL * StarThrown*dt;
	}

	
	if (y < StepUp)
	{
		if (!isFalling)
		{
			isFalling = true;
		}
	}


}
void EffectBWall::Render(float camera_x, int SCREEN_WIDTH, float fishman_x, float fishman_y)
{

	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d < 200)
	{
		animations[0]->Render(x - (camera_x - SCREEN_WIDTH / 2), y + 60);
	}


}
void EffectBWall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}