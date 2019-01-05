#include "HealthBoss.h"

#define ID_TEX_HEALTHBOSS 210
#define HEALTHBOSS_TEXTURE_PATH    L"Backgrounds\\blackboard.png"
#define HEALTHBOSS_TEXTURE_BACKGROUND_COLOR D3DCOLOR_XRGB(255, 0, 255)


#define HEALTHBOSSBIGBAT_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAHealthBigBat.txt"

//Big Bat

HealthBoss::HealthBoss()
{
	SetSpeed(0, 0);
	ani = HEALTHBOSS_STATE_ON;

	LoadHealth();
}
void HealthBoss::LoadHealth()
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
	in.open(HEALTHBOSSBIGBAT_INFOR_TXT_PATH);
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

void HealthBoss::Render(int type)
{
	ani = HEALTHBOSS_STATE_ON;
	if (type == HEALTHBOSS_STATE_OFF)
	{
		ani = HEALTHBOSS_STATE_OFF;
	}
	animations[ani]->Render(x, y);
}
