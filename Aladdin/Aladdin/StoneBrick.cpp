#include "StoneBrick.h"
#include "Textures.h"

StoneBrick::StoneBrick(float left, float top, float width, float height)
{
	x = left;
	y = top;
	/*xDraw = left;
	yDraw = top;
	w = width;
	h = height;	*/
	isDead = false;
	direction = true;
	collType = CollBrick;
	objType = OBJStoneBrick;
}

void StoneBrick::LoadResources(bool check)
{
	LPDIRECT3DTEXTURE9 texBrickTrap = Textures::GetInstance()->Get(ID_TEX_BRICK_TRAP);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_STONEBRICK_ANIMATION_PATH, texBrickTrap, 200);
	// animation ban đầu
	currentAnimation = animationDefault;
	// biến check để khởi tạo animation ban đầu ngược nhau của các gạch đá
	if (check)
		animationDefault->SetFrame(0, 4);
	else
		animationDefault->SetFrame(4, 0);

	startTime = GetTickCount();
}

void StoneBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
}

void StoneBrick::Render()
{
	DWORD startWait = GetTickCount();
	int i = currentAnimation->GetCurrentFrame();
	if (i == 0)
	{
		animationDefault->SetFrame(0, 0);
		// sau t giây thì lồi ra
		if (startWait - startTime > 2200)
		{
			GameSound::getInstance()->play(STONEBRICK_MUSIC);
			animationDefault->SetFrame(1, 4);
			startTime = GetTickCount();
		}
	}
	if (i == 4)
	{
		animationDefault->SetFrame(4, 4);
		// sau t giây thì thụt vào
		if (startWait - startTime > 2200)
		{
			animationDefault->SetFrame(3, 0);
			startTime = GetTickCount();
		}
	}

	GameObject::Render();

	//RenderBoundingBox();
}

void StoneBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = xDraw;
	top = yDraw;
	right = xDraw + w - 3;
	bottom = yDraw + 15;
}

StoneBrick::~StoneBrick()
{
}
