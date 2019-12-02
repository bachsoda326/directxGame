#include "Apple.h"
#include "Textures.h"

Apple::Apple()
{
	isDead = false;
	objType = OBJApple;
	collType = CollApple;
}

Apple::Apple(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	
	direction = true;
	isDead = false;
	objType = OBJApple;
}

void Apple::LoadResources()
{	
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texAladdin = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	animationItem = new Animation("Animation_Small", XML_ITEMAPLLE_ANIMATION_PATH, texItems, 100);
	animationBurst_1 = new Animation("Burst_1", XML_APPLE_ANIMATION_PATH, texAladdin, 100);
	animationSplit_Half = new Animation("Split_Half", XML_APPLE_ANIMATION_PATH, texAladdin, 100);

	xInit = x;
	yInit = y;
	
	if (collType == CollItem)
	{
		x = xDraw + 5;
		y = yDraw + 6;
		state = NOTMOVING;
		isActived = false;
		direction = true;
		currentAnimation = animationItem;
	}
	else
	{
		x = xDraw + 7;
		y = yDraw + 6;
		state = FLING;
		typeSplit_Half = true;
		currentAnimation = animationBurst_1;
		animationBurst_1->SetFrame(0, 0);
	}

	isDie = false;
	isDead = false;
	nx = 0.0f;
	ny = 0.0f;
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	// cập nhật vị trí của táo
	x += dx;
	y += dy;

	// trọng lực cho táo rơi
	if (collType == CollApple)
		vy += 0.015f;
}

void Apple::Render()
{
	if (true)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
	else
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));
}

void Apple::SetAnimation(AppleAnimations ani)
{
	switch (ani)
	{
	case ANI_BURST:
	{
		//reset frame when press event
		currentAnimation = animationBurst_1;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_SPLIT_HALF:
	{
		currentAnimation = animationSplit_Half;
		currentAnimation->ResetFrame();
		break;
	}	
	}
}

void Apple::ProcessInput()
{
	switch (state)
	{
	case SPLIT_HALF:
		Split_Half();
		break;
	case BURST:
		Burst();
		return;
	case ACTIVED:
		Active();
		break;
	default:
		Move();
		break;
	}
}

void Apple::OnCollision(GameObject * obj, float nx, float ny)
{
	switch (obj->collType)
	{
	case CollGround: case CollFence:
		Collision::PreventMove(this, obj, nx, ny);
		Burst();
		break;
	}
}

void Apple::OnInterSerct(GameObject * obj)
{
	if (collType == CollApple && obj->collType != CollItem)
	{
		if (obj->objType == OBJSword)
		{
			Split_Half();
		}
		else
		{
			if (!(vy < 0))
				Burst();
		}
	}
	if (collType == CollItem && obj->collType == CollAladdin)
	{		
		Active();
	}
}

void Apple::Move()
{
	if (collType == CollApple)
		SetState(FLING);
	else
	{
		vy = 0;
		vx = 0;
	}
}

void Apple::Burst()
{
	switch (state)
	{
	case BURST:
	{
		if (currentAnimation->isActionFinish())
		{
			isDead = true;
			Aladdin::GetInstance()->DeleteApple(this);
		}
		break;
	}
	default:
	{
		SetState(BURST);
		SetAnimation(ANI_BURST);
		animationBurst_1->SetFrame(1, 5);
		isDie = true;
		vx = 0;
		vy = 0;
		break;
	}
	}
}

void Apple::Active()
{
}

void Apple::Split_Half()
{
}

Apple::~Apple()
{
}
