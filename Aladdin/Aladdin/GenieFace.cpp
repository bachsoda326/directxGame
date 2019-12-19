#include "GenieFace.h"

GenieFace::GenieFace(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 19;
	y = yDraw + 25;
	direction = true;
	collType = CollItem;
	objType = OBJGenieFace;
}

void GenieFace::LoadResources()
{
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texEnemyExplosion = Textures::GetInstance()->Get(ID_TEX_ENEMYEXPLOSION);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_GENIEFACE_ANIMATION_PATH, texItems, 170);
	animationExplosion_Actived = new Animation("Explosion_Actived", XML_ENEMYEXPLOSION_ANIMATION_PATH, texEnemyExplosion, 40);
	// animation ban đầu
	currentAnimation = animationDefault;
	
	Item::LoadResources();
}

void GenieFace::Active()
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
		SetState(ACTIVED);
		currentAnimation = animationExplosion_Actived;		
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

void GenieFace::NonActive()
{
	if (currentAnimation->isActionFinish())
	{
		// sau t giây sẽ set animation chuyển động 
		DWORD endWait = GetTickCount();
		if (endWait - startWait > 1500)
		{
			animationDefault->SetFrame(0, 3);
			startWait = GetTickCount();
		}
		else
		{
			animationDefault->SetFrame(0, 0);
		}
	}
}

GenieFace::~GenieFace()
{
}
