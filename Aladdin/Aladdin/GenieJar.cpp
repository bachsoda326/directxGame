#include "GenieJar.h"
#include "Textures.h"

GenieJar::GenieJar(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 9;
	y = yDraw + 33;
	direction = true;
	collType = CollItem;
	objType = OBJGenieJar;
}

void GenieJar::LoadResources()
{
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_GENIEJAR_ANIMATION_PATH, texItems, 100);
	// animation ban đầu
	currentAnimation = animationDefault;
	animationDefault->SetFrame(0, 0);	

	Item::LoadResources();
}

void GenieJar::Active()
{
	switch (state)
	{
	case ACTIVED:
	{
		if (currentAnimation->isActionFinish())
			animationDefault->SetFrame(9, 9);
		break;
	}
	default:
	{
		GameSound::getInstance()->play(COMEOUT_MUSIC);
		SetState(ACTIVED);
		animationDefault->SetFrame(1, 9);
		vy = 0;
		vx = 0;
		isDie = true;
		isActived = true;
		break;
	}
	}
}

void GenieJar::NonActive()
{
}

GenieJar::~GenieJar()
{
}
