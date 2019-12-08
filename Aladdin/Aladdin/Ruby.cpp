#include "Ruby.h"
#include "Textures.h"

Ruby::Ruby(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 8;
	y = yDraw + 8;
	isDead = false;
	direction = true;
	collType = CollItem;
	objType = OBJRuby;
}

void Ruby::LoadResources()
{
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);

	animationDefault = new Animation("Animation", XML_RUBY_ANIMATION_PATH, texItems, 100);

	currentAnimation = animationDefault;	

	Item::LoadResources();
}

void Ruby::Active()
{
	Item::Active();
}

void Ruby::NonActive()
{
	if (currentAnimation->isActionFinish())
	{
		DWORD endWait = GetTickCount();
		if (endWait - startWait > 3500)
		{
			animationDefault->SetFrame(0, 8);
			startWait = GetTickCount();
		}
		else
		{
			animationDefault->SetFrame(0, 0);
		}
	}
}

Ruby::~Ruby()
{
}
