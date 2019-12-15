#include "BlueHeart.h"

BlueHeart::BlueHeart(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 9;
	y = yDraw - 10;
	direction = true;
	collType = CollItem;
	objType = OBJBlueHeart;
}

void BlueHeart::LoadResources()
{
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);

	animationDefault = new Animation("Animation", XML_BLUEHEART_ANIMATION_PATH, texItems, 100);

	currentAnimation = animationDefault;	

	Item::LoadResources();
}

void BlueHeart::Active()
{
	switch (state)
	{
	case ACTIVED:
	{
		//Thực hiện animation actived xong đặt isDead = true để xóa item ra khỏi danh sách
		if (currentAnimation->isActionFinish())
			isDead = true;
		break;
	}
	default:
	{
		GameSound::getInstance()->play(BLUEHEART_MUSIC);
		SetState(ACTIVED);
		currentAnimation = animationItemActived;
		vy = 0;
		vx = 0;
		x = (this->Left() + this->Right()) / 2;
		y = (this->Top() + this->Bottom()) / 2;
		isDie = true;
		isActived = true;
		break;
	}
	}
}

void BlueHeart::NonActive()
{
	if (currentAnimation->isActionFinish())
	{
		DWORD endWait = GetTickCount();
		if (endWait - startWait > 2500)
		{
			animationDefault->SetFrame(0, 7);
			startWait = GetTickCount();
		}
		else
		{
			animationDefault->SetFrame(0, 0);
		}
	}
}

BlueHeart::~BlueHeart()
{
}
