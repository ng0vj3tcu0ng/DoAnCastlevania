#include "Item.h"

#define ITEMS_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSAItems.txt"

Item::Item(int x, int y, int TypeOfItems, int FallingStyle)
{
	//CTextures * textures = CTextures::GetInstance();
	//CSprites * sprites = CSprites::GetInstance();
	//CAnimations * animations = CAnimations::GetInstance();
	//LPANIMATION ani;
	//ifstream in;
	//int action;
	//int n;
	//int idtexItems;
	//int left = 0, top = 0, right = 0, bottom = 0, idsprites = 0, idtxt = 0; //sprites
	//int idAni = 0, defaultTime = 0, nSprites = 0, idSprites = 0; //ani
	//in.open(ITEMS_INFOR_TXT_PATH);
	//in >> action;
	//if (action == ID_ACTION_TEXTURES)
	//{

	//	in >> idtexItems;
	//	textures->Add(idtexItems, ITEMS_TEXTURE_PATH, ITEMS_TEXTURE_BACKGROUND_COLOR); //texture

	//}
	//in >> action;
	//if (action == ID_ACTION_SPRITES)
	//{
	//	in >> n;
	//	for (int i = 0; i < n; i++)
	//	{
	//		in >> idsprites >> left >> top >> right >> bottom >> idtxt;
	//		sprites->Add(idsprites, left, top, right, bottom, textures->Get(idtxt));
	//	}
	//}
	//in >> action;
	//if (action == ID_ACTION_ANI)
	//{
	//	in >> n;
	//	for (int i = 0; i < n; i++)
	//	{
	//		in >> idAni >> defaultTime >> nSprites; ;
	//		ani = new CAnimation(defaultTime);
	//		for (int j = 0; j < nSprites; j++)
	//		{	
	//			in >> idSprites;
	//			ani->Add(idSprites);
	//		}
	//		animations->Add(idAni, ani);
	//	}
	//}
	//in.close();
	//cin.ignore();
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
	in.open(ITEMS_INFOR_TXT_PATH);
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

			}
			break;
		}
	}
	this->Type = TypeOfItems;
	this->AddAnimation(TypeOfItems);
	SetPosition(x, y);
	CollisionBrick = false;
	this->FallingStyle = FallingStyle;
	//CTextures * textures = CTextures::GetInstance();

	//textures->Add(ID_TEX_ITEMS, ITEMS_TEXTURE_PATH, ITEMS_TEXTURE_BACKGROUND_COLOR);

	//CSprites * sprites = CSprites::GetInstance();
	//CAnimations * animations = CAnimations::GetInstance();

	//LPDIRECT3DTEXTURE9 texItems = textures->Get(ID_TEX_ITEMS);

	//// Whip Upgrade
	//sprites->Add(18001, 0, 0, 17, 17, texItems);
	//// Dagger
	//sprites->Add(18011, 17, 0, 34, 17, texItems);
	//// Heart
	//sprites->Add(18021, 0, 17, 17, 34, texItems);
	//// Money Bag
	//sprites->Add(18031, 0, 34, 17, 51, texItems);
	//// HeartS
	//sprites->Add(18041, 17, 17, 34, 34, texItems);
	////Axe
	//sprites->Add(18051, 60, 2, 74, 15, texItems);
	////Holy Water
	//sprites->Add(18061, 17, 35, 32, 51, texItems);
	////CROSS
	//sprites->Add(18071, 80, 34, 95, 51, texItems);
	////Invincibility
	//sprites->Add(18081, 96, 37, 106, 51, texItems);
	////Jewel
	//sprites->Add(18091, 78, 51, 92, 66, texItems);
	//sprites->Add(18101, 93, 51, 107, 66, texItems);
	////Double Attacking
	//sprites->Add(18102, 110, 50, 122, 67, texItems);
	////Pot Roast
	//sprites->Add(18103, 110, 38, 125, 50, texItems);
	////Stop Watch
	//sprites->Add(18104, 49, 35, 62, 50, texItems);
	////Bomerang
	//sprites->Add(18105, 140, 75, 164, 89, texItems);

	//LPANIMATION ani;

	//// Whip Upgrade
	//ani = new CAnimation(100);
	//ani->Add(18001);
	//animations->Add(180, ani);

	//// Dagger
	//ani = new CAnimation(100);
	//ani->Add(18011);
	//animations->Add(181, ani);

	//// Heart
	//ani = new CAnimation(100);
	//ani->Add(18021);
	//animations->Add(182, ani);

	//// Money Bag
	//ani = new CAnimation(100);
	//ani->Add(18031);
	//animations->Add(183, ani);
	//// HeartS
	//ani = new CAnimation(100);
	//ani->Add(18041);
	//animations->Add(184, ani);
	//// AXE
	//ani = new CAnimation(100);
	//ani->Add(18051);
	//animations->Add(185, ani);
	//// HOLYWATER
	//ani = new CAnimation(100);
	//ani->Add(18061);
	//animations->Add(186, ani);
	////CROSS
	//ani = new CAnimation(100);
	//ani->Add(18071);
	//animations->Add(187, ani);
	////Invincibility
	//ani = new CAnimation(100);
	//ani->Add(18081);
	//animations->Add(188, ani);
	////Jewel
	//ani = new CAnimation(50);
	//ani->Add(18091);
	//ani->Add(18101);
	//animations->Add(189, ani);
	////double attaking
	//ani = new CAnimation(100);
	//ani->Add(18102);
	//animations->Add(190, ani);
	////Pot roast
	//ani = new CAnimation(100);
	//ani->Add(18103);
	//animations->Add(191, ani);
	////Stop Watch
	//ani = new CAnimation(100);
	//ani->Add(18104);
	//animations->Add(192, ani);
	////Bomerang
	//ani = new CAnimation(100);
	//ani->Add(18105);
	//animations->Add(193, ani);

}
void Item::BricksCollision(vector<LPGAMEOBJECT>* Brick)
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
			y += 0;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 

			x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.1f;

			//if (nx != 0) vx = 0;
			if (ny != 0||nx!=0 )
			{
				vx = 0;
				vy = 0;
				CollisionBrick = true;
			}
		}

		// clean up collision events
		for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects)
{
	CGameObject::Update(dt, Objects);


	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	if (!CollisionBrick)
	{
		if (FallingStyle == 1)
		{
			vy = ITEM_VY;
			vx = sin(y*PI / 30)*ITEM_VY;
			y += dy;
			x += dx;
		}
		else
		{
			vy = ITEM_VY * 2;
			vx = 0;
			y += dy;
			x += dx;
		}
	}
	BricksCollision(Objects);


	

}
void Item::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 5;
	top = y;
	right = left + ITEM_TYPE_BBOXSS_WIDTH;
	bottom = top + ITEM_TYPE_BBOXSS_HEIGHT+8;
}

void Item::Render(float camera_x, int SCREEN_WIDTH)
{
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);

	animations[0]->Render(pos.x, pos.y + 55);
	
}