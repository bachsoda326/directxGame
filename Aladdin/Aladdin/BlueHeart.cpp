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
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_BLUEHEART_ANIMATION_PATH, texItems, 100);
	// animation ban đầu
	currentAnimation = animationDefault;	

	Item::LoadResources();
}

void BlueHeart::Active()
{
	switch (state)
	{
	case ACTIVED:
	{		
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
		// set vị trí bị hủy ở chính giữa item
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
		// sau t giây sẽ set animation chuyển động
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
