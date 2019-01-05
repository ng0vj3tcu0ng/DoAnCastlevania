//#include "IntroStart.h"
//
//IntroStart * IntroStart::__instance = NULL;
//
//
//IntroStart * IntroStart::GetInstance()
//{
//	return __instance;
//}
//
//IntroStart * IntroStart::GetInstance(int ID_TEX_INTROSTART, LPCWSTR INTROSTART_TEXTURE_PATH, D3DCOLOR INTROSTART_TEXTURE_BACKGROUND_COLOR)
//{
//	__instance = new IntroStart(ID_TEX_INTROSTART, INTROSTART_TEXTURE_PATH, INTROSTART_TEXTURE_BACKGROUND_COLOR);
//	return __instance;
//}
//IntroStart::IntroStart(int ID_TEX_INTROSTART, LPCWSTR INTROSTART_TEXTURE_PATH, D3DCOLOR INTROSTART_TEXTURE_BACKGROUND_COLOR)
//{
//	ID_TEX = ID_TEX_INTROSTART;
//	textures = CTextures::GetInstance();
//	textures->Add(ID_TEX_INTROSTART, INTROSTART_TEXTURE_PATH, INTROSTART_TEXTURE_BACKGROUND_COLOR);
//	LoadIntroStart();
//	//this->isBeingFly = false;
//}
//void IntroStart::LoadIntroStart()
//{
//	CSprites * sprites = CSprites::GetInstance();
//	LPDIRECT3DTEXTURE9 texIntroStart = textures->Get(ID_TEX);
//	CAnimations * animations = CAnimations::GetInstance();
//	sprites->Add(33000, 139, 0, 165, 17, texIntroStart);
//	sprites->Add(33001, 17, 0, 34, 17, texIntroStart);
//	sprites->Add(33002, 34, 0, 51, 17, texIntroStart);
//
//	LPANIMATION ani;
//	ani = new CAnimation(100);
//	ani->Add(60000);
//	animations->Add(600, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(60001);
//	animations->Add(601, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(60002);
//	animations->Add(602, ani);
//	if (this->animations.empty())
//	{
//
//		AddAnimation(600);
//		AddAnimation(601);
//		AddAnimation(602);
//
//	}
//}
//
//void IntroStart::Render(float camera_x, int SCREEN_WIDTH)
//{
//}
