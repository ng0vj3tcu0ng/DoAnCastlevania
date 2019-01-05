#include "IntroSource.h"

IntroSource::IntroSource(int x, int y)
{
	SetPosition(x, y);
}



void IntroSource::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (nx>0)
	{
		x += MOVE_X1;
		y -= MOVE_Y;
	}
	else x -= MOVE_X2;
	
}
void IntroSource::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
void IntroSource::Render(float camera_x, int SCREEN_WIDTH)
{
	Camera *camera = Camera::GetInstance();
	Point pos = camera->PositionOnCamera(x, y);
	animations[0]->Render(pos.x, pos.y+55);
}