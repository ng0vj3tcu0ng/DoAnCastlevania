#include "BrickOnStair.h"

CBrickOnStair::CBrickOnStair(int x, int y, int TypeStair, int DirectionUpOrDown,int DirectionXUp)
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BRICKSTAIR, BRICKSTAIR_TEXTURE_PATH, BRICKSTAIRTEXTURE_BACKGROUND_COLOR);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texBrickStair = textures->Get(ID_TEX_BRICKSTAIR);
	sprites->Add(19005, 36, 0, 44, 8, texBrickStair);
	LPANIMATION ani;
	ani = new CAnimation(100);		// brick
	ani->Add(19005);
	animations->Add(195, ani);
	if (this->animations.empty())
	{
		this->AddAnimation(195);		
		
	}
	SetPosition(x, y);
	this->TypeStair = TypeStair;
	this->DirectionUpOrDown = DirectionUpOrDown;
	this->DirectionXUp = DirectionXUp;
	this->Type = TYPE_BRICK_ON_STAIR;
}
void CBrickOnStair::Render(float screen_x, int SCREEN_WIDTH)
{
	//Camera *camera = Camera::GetInstance();
	//Point pos = camera->PositionOnCamera(x, y);
	//animations[0]->Render(pos.x, pos.y+55);
}
void CBrickOnStair::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{	
		left = x;
		top = y;
		right = x + BRICKONSTAIR_BBOX_WIDTH;
		bottom = y + BRICKONSTAIR_BBOX_HEIGHT;
}