#include "BrickHidden.h"



#define HIDDENBRICK_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAHiddenBrick.txt"

BrickHidden::BrickHidden(int x, int y, int itemType,int HiddenBrickType,int BrickDelete)
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
	int typeOfHiddenBrick;
	in.open(HIDDENBRICK_INFOR_TXT_PATH);
	string link;
	while (1) {
		in >> action >> n;
		if (action == -1)break;
		switch (action) 
		{
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

				in >> typeOfHiddenBrick;
				if (typeOfHiddenBrick == HiddenBrickType)
				{
					animations->Add(idAni, ani);
					this->AddAnimation(idAni);
				}
			}
			break;
		}
	}
	




	SetPosition(x, y);
	this->Type = TYPE_BRICKHIDDEN;
	this->BrickDelete = BrickDelete;
	this->itemType = itemType;
	Normal = true;
	Destroy = false;
	EffectBWall *bwall_temp;
	for (int i = 0; i < 4; i++)
	{
		bwall_temp = new EffectBWall();
		BreakingWall.push_back(bwall_temp);
	}

}

void BrickHidden::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y+10;
	right = left + BRICKHIDDEN_BBOX_WIDTH;
	bottom = top + BRICKHIDDEN_BBOX_HEIGHT;
}

void BrickHidden::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects)
{
	if (!Normal)
	{
		this->BreakingWall[0]->Start(BREAKINGWALL1_VX, this->x, this->y, y - 5);
		this->BreakingWall[1]->Start(BREAKINGWALL2_VX, this->x, this->y, y - 2);
		this->BreakingWall[2]->Start(BREAKINGWALL3_VX, this->x, this->y, y - 10);
		this->BreakingWall[3]->Start(BREAKINGWALL4_VX, this->x, this->y, y - 5);
	}
	for (int i = 0; i < BreakingWall.size(); i++)
	{
		BreakingWall[i]->Update(dt, Objects);
	}	
	
}
void BrickHidden::Render(float camera_x, int SCREEN_WIDTH)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);

		if (Normal) 
		{
			ani = BRICKHIDDEN_STATE_NORMAL;
			this->StartDestroy = GetTickCount();
		}
		else 
		{
			ani = BRICKHIDDEN_STATE_DESTROY;
			for (int i = 0; i < BreakingWall.size(); i++)
			{
				BreakingWall[i]->Render(camera->GetX(), SCREEN_WIDTH, this->GetX(), this->GetY());
			}
		}
		animations[ani]->Render(pos.x, pos.y + 60);
		if (!Normal&&GetTickCount() - this->StartDestroy > BRICKHIDDEN_DESTROY_TIME) {
			Destroy = true;
		}

	

}




