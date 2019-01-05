#include "Candle.h"
#include "Textures.h"


#define CANDELS_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSACandles.txt"

Candle::Candle(int x, int y, int itemType ,int CandleType)
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
	int typeOfCandles;
	in.open(CANDELS_INFOR_TXT_PATH);
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
				in >> typeOfCandles;
				if (typeOfCandles == CandleType)
				{
					animations->Add(idAni, ani);
					this->AddAnimation(idAni);
				}
			}
			break;
		}
	}
	
	SetPosition(x, y);
	this->Type = TYPE_CANDLE;
	this->itemType = itemType;


	Normal = true;
	Destroy = false;
	OnScreen = true;
}

void Candle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + CANDLE_BBOX_WIDTH;
	bottom = top + CANDLE_BBOX_HEIGHT;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects,float camera_x, int SCREEN_WIDTH)
{
	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d > 250)
	{
		return;
	}
	if (x < camera_x- SCREEN_WIDTH/2)
	{
		OnScreen = false;
	}
	if (camera_x > 1550)
	{
		if (x < 1550)
		{
			OnScreen = false;
		}
	}
}

void Candle::Render(float camera_x, int SCREEN_WIDTH)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);

	int d = sqrt((camera_x - x)*(camera_x - x) + (0 - y)*(0 - y));
	if (d < 250)
	{
		if (Normal) {
			ani = CANDLE_STATE_NORMAL;
			this->StartDestroy = GetTickCount();
		}
		else
		{
			ani = CANDLE_STATE_DESTROY;
		}
		animations[ani]->Render(pos.x, pos.y + 60);
		if (!Normal&&GetTickCount() - this->StartDestroy > CANDLE_DESTROY_TIME) {
			Destroy = true;
		}

	}
	//DebugOut(L"pos X %f\n", pos.x);
}
bool Candle::DoesExist()
{
	return !(!OnScreen);
}

