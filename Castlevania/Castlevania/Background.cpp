#include "Background.h"

Background * Background::__instance = NULL;



Background * Background::GetInstance()
{
	return __instance;
}

Background * Background::GetInstance(int stage,int ID_TEX_BACKGROUND, LPCWSTR BACKGROUND_TEXTURE_PATH, D3DCOLOR BACKGROUND_TEXTURE_BACKGROUND_COLOR, int SCREEN_WIDTH, LPCWSTR LinkMap)
{
	__instance = new Background(stage,ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR, SCREEN_WIDTH, LinkMap);
	return __instance;
}

Background::Background(int stage, int ID_TEX_BACKGROUND, LPCWSTR BACKGROUND_TEXTURE_PATH, D3DCOLOR BACKGROUND_TEXTURE_BACKGROUND_COLOR , int SCREEN_WIDTH,LPCWSTR LinkMap)
{
	this->Stage = stage;
	CTextures * textures = CTextures::GetInstance();
	NextMap = false;
	textures->Add(ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR);
	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texBackground = textures->Get(ID_TEX_BACKGROUND);
	switch (stage)
	{
	case STAGEINTRO:
	{
		textures->Add(ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR);

		sprites->Add(21000, 0,0,256,250 , texBackground);
		setWidth(360, SCREEN_WIDTH);
		break;
	}
	case STAGE1:
	{
		textures->Add(ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR);

		for (int i = 0; i < 51; i++)
			sprites->Add(21000 + i , i * 16, 0, (i + 1) * 16, 16, texBackground);
		setWidth(864, SCREEN_WIDTH);
		break;
	}
	case STAGE2:
	{
		textures->Add(ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR);

		for (int i = 0; i < 97; i++)
			sprites->Add(21000 + i+1 , i * 16, 0, (i + 1) * 16, 16, texBackground);
		setWidth(2928, SCREEN_WIDTH);
		break;
	}
	case STAGE3:
	{
		textures->Add(ID_TEX_BACKGROUND, BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE_BACKGROUND_COLOR);

		for (int i = 0; i < 22; i++)
			sprites->Add(21000 + i	+1, i * 16, 0, (i + 1) * 16, 16, texBackground);
		setWidth(2158, SCREEN_WIDTH);
		break;
	}

	}
	if (stage != STAGEINTRO)
	{
		ifstream infile;
		infile.open(LinkMap);
		infile >> w >> h;
		Map = new int*[h];
		for (int i = 0; i < h; i++) {
			Map[i] = new int[w];
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				infile >> Map[i][j];
			}
		}
		int soluongCong;
		infile >> soluongCong;
		for (int i = 0; i < soluongCong; i++) {
			Door doortemp;
			infile >> doortemp.id;
			infile >> doortemp.x;
			infile >> doortemp.y;
			infile >> doortemp.MapNext;
			infile >> doortemp.x_next;
			infile >> doortemp.y_next;
			door.push_back(doortemp);
		}

		infile.close();
	}
} 

void Background::Update(float simon_x,float simon_y, vector<LPGAMEOBJECT>* Brick, float camera_x)
{
	for (int i = 0; i < door.size(); i++) {
		int d = sqrt((simon_x - door[i].x)*(simon_x - door[i].x) + (simon_y - door[i].y)*(simon_y - door[i].y));
		if (d < 10)
		{
			NextMap = true;
			this->Stage = door[i].MapNext;
			NewXSimon = door[i].x_next;
			NewYSimon = door[i].y_next;
		}
	}	
}
void Background::Render(float camera_x )
{
	CSprites * sprites = CSprites::GetInstance();

	if (Stage == STAGEINTRO)
	{
		sprites->Get(21000)->Draw(0, 10);
	}
	else
	{
		int jj, ii;
		x = screen_width / 2;
		for (int i = 0; i < h; i++)
		{
			ii = i * 16 + 55;
			for (int j = camera_x / 16 - 12; j < camera_x / 16 + 5; j++)  
			{
				{
					jj = -camera_x + j * 16 + x;
					if (jj > -16 && jj < screen_width)
					{
						sprites->Get(21000 + Map[i][j])->Draw(jj, ii);
					}
				}
			}
		}
	}
	//CSprites * sprites = CSprites::GetInstance();



}