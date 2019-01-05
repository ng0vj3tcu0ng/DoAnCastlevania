#include "CDoor.h"


#define DOOR_INFOR_TXT_PATH L"Backgrounds\\TexturesSpritesAni\\TSADoor.txt"

CDoor::CDoor(int x, int y)

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
	in.open(DOOR_INFOR_TXT_PATH);
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


	this->SetState(DOOR_STATE_IDLE);



	SetPosition(x, y);

}
void CDoor::Render(float simon_x, int camera_x)
{
	int ani = state;
	state = ani;
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);

	ChangeStatusDoor = false;

	if (GetTickCount() - now > DOOR_TIME_OPENCLOSE) 
	{
		now = GetTickCount();
		ChangeStatusDoor = true;
	}

		if (camera_x > x+40)  // so toi thieu, de lon hon camera luc dung yen , x=1526
		{
			////////open

			if (simon_x > x-26 && simon_x < x-10) //1500-1510
			{
				FlagOpen = true;
				//flag_Opening = false;
			}
			/*else 
			{
				flag_Opening = false;
			}*/

			if (FlagOpen /*&& !flag_Opening*/)	 
			{

				if (state < 3) 
				{
					if (ChangeStatusDoor)
						state++;
				}

			}
		/*	else 
			{
				flag_Open = false;
			}*/
			if (simon_x > x+43 && simon_x < x+53) //1569-1579
			{
				FlagClose = true;
				//flag_Closing = false;
			}
		/*	else 
			{
				flag_Closing = false;
			}*/

			if (FlagClose /*&& !flag_Closing*/) 
			{

				if (state < 8)
				{

					if (ChangeStatusDoor)
						state++;
				}
			}
			//else
			//{
			//	flag_Close = false;

			//	//state = 0;
			//}
		}
		animations[state]->Render(pos.x, pos.y + 55);


}



void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOOR_STATE_IDLE:
		break;
	case DOOR_STATE_OPEN:

		break;
	case DOOR_STATE_CLOSE:

		break;
	}
}


