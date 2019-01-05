#include "Camera.h"

Camera *Camera::__instance = NULL;

Camera *Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	
	return __instance;
}

void Camera::Update(int SCREEN_WIDTH, int Background_Width,float simon_x, float simon_y, bool MOVE,int IdStage)
{
	//camera cong 1 1467
	//camera cong 2 1980
	//camera cuoi 2 2748
	//flag_delay = true;
	SetWidth(Background_Width, SCREEN_WIDTH);
	switch (IdStage)
	{
	case STAGEINTRO:
		Start = 0;
		if (simon_x + 55 < this->Start + Screen_Width / 2)
		{
			x = this->Start + Screen_Width / 2;
		}
		else
		{
			x = min(simon_x + 55, Background_Width - Screen_Width / 2); //1647
		}
		break;
	case STAGE1:
		if (simon_x + 55 < this->Start + Screen_Width / 2)
		{
			x = this->Start + Screen_Width / 2;
		}
		else
		{
			x = min(simon_x + 55, Background_Width - Screen_Width / 2); //1647
		}
		break;
	case STAGE2:
		if (x < 1468)
		{
			if (simon_x + 55 < Screen_Width / 2) x = Screen_Width / 2;
			else x = min(simon_x + 55, 1647 - Screen_Width / 2);// 1647 cho dung lai canh 2

		}
		if (simon_x > 1500 && simon_x < 1600 && simon_y < 35)
		{
			x += CAMERA_MOVE;
			CameraMove = true;
			if (MOVE)
			{
				x = 1580;
			}
		}
		if (x > 1710 && x < 1981)
		{
			CameraMove = false;
			Start = 1536;
			if (simon_x + 55 < this->Start + Screen_Width / 2)
			{
				x = this->Start + Screen_Width / 2;
			}
			else
			{
				x = min(simon_x + 55, 2160 - Screen_Width / 2);
			}
		}

		if (simon_x > 2010 && simon_x < 2100 && simon_y < 35)
		{
			x += CAMERA_MOVE;
			CameraMove = true;
			if (MOVE)
			{
				x = 2080;
			}
		}
		if (x > 2215 && x < 2748)
		{
			CameraMove = false;
			Start = 2040;
			if (simon_x + 55 < Start + Screen_Width / 2)
			{
				x = Start + Screen_Width / 2;
			}
			else
			{
				x = min(simon_x + 55, Background_Width - Screen_Width / 2);
			}
			if (x > 2746)
			{
				Start = 2568;
			}
		}
		break;
	case STAGE3:
		Start = 1536;
		if (simon_x + 55 < this->Start + Screen_Width / 2)
		{
			x = this->Start + Screen_Width / 2;
		}
		else
		{
			x = min(simon_x + 55, Background_Width - Screen_Width / 2);
		}
		break;

	default:
		break;
	}

}
Point Camera::PositionOnCamera(float x, float y)
{
	Point point;
	point.x = x - (this->x - Screen_Width / 2);
	point.y = y;
	return point;
}

