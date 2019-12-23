#include "Apple.h"
#include "Textures.h"

Apple::Apple()
{
	isDead = false;	
	collType = CollApple;
	objType = OBJApple;
}

Apple::Apple(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	
	direction = true;
	isDead = false;	
	collType = CollItem;
	objType = OBJApple;
}

void Apple::LoadResources()
{	
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texAladdin = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	LPDIRECT3DTEXTURE9 texItemActived = Textures::GetInstance()->Get(ID_TEX_ITEMACTIVED);
	
	animationBig = new Animation("Animation_Big", XML_ITEMAPLLE_ANIMATION_PATH, texItems, 100);
	animationItem = new Animation("Animation_Small", XML_ITEMAPLLE_ANIMATION_PATH, texItems, 100);
	animationBurst_1 = new Animation("Burst_1", XML_APPLE_ANIMATION_PATH, texAladdin, 100);
	animationSplit_Half = new Animation("Split_Half", XML_APPLE_ANIMATION_PATH, texAladdin, 100);
	animationItemActived = new Animation("Animation", XML_ITEMACTIVED_ANIMATION_PATH, texItemActived, 100);

	xInit = x;
	yInit = y;
	
	if (collType == CollItem)
	{
		x = xDraw + 5;
		y = yDraw + 6;
		SetState(NOTMOVING);
		isActived = false;
		direction = true;
		currentAnimation = animationItem;
	}
	else if (collType == CollApple)
	{
		x = xDraw + 7;
		y = yDraw + 6;
		SetState(FLING);
		typeSplit_Half = true;
		currentAnimation = animationBurst_1;
		animationBurst_1->SetFrame(0, 0);
	}
	else
	{		
		state = NOTMOVING;		
		currentAnimation = animationBig;
	}

	isDie = false;
	isDead = false;
	nx = 0.0f;
	ny = 0.0f;
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead)
		return;

	GameObject::Update(dt);
	// cập nhật vị trí của táo
	x += dx;
	y += dy;

	// k.tra nếu táo xa Aladdin quá (vượt xa camera) thì xóa táo
	if (x - Aladdin::GetInstance()->x > 270 || x - Aladdin::GetInstance()->x < -270)
		Aladdin::GetInstance()->DeleteApple(this);

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

	// trọng lực cho táo rơi
	if (collType == CollApple)
		vy += 0.015f;
}

void Apple::Render()
{
	if (collType == CollUnknown)
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));
	else if (!isDead)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
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
	case ANI_ACTIVED:
	{
		currentAnimation = animationItemActived;
		currentAnimation->ResetFrame();
		break;
	}
	}
}

void Apple::OnCollision(GameObject * obj, float nx, float ny)
{
	switch (obj->collType)
	{
	case CollGround: case CollFence:
		Collision::PreventMove(this, obj, nx, ny);
		//Burst();
		break;
	}
}

void Apple::OnIntersect(GameObject * obj)
{
	if (collType == CollApple && obj->collType != CollItem)
	{
		/*if (obj->objType == OBJSword)
		{
			Split_Half();
		}*/
		if (obj->objType != OBJStoneBrick && obj->objType != OBJBallTrap && obj->objType != OBJSharpTrap && obj->collType != CollChains)
		{
			/*if (!(vy < 0))
			{
				Burst();
				GameSound::getInstance()->play(APPLE_POP_MUSIC);
			}*/

			Burst();
			GameSound::getInstance()->play(APPLE_POP_MUSIC);
		}		
	}
	if (collType == CollItem && obj->collType == CollAladdin)
	{	
		GameSound::getInstance()->play(APPLE_MUSIC);
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
	switch (state)
	{
	case ACTIVED:
	{
		if (currentAnimation->isActionFinish())
		{
			isDead = true;
			//Aladdin::GetInstance()->score += 5;
		}
		break;
	}
	default:
	{
		SetState(ACTIVED);
		SetAnimation(ANI_ACTIVED);
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

void Apple::Split_Half()
{
}

void Apple::ResetProper()
{
	SetState(NOTMOVING);
	isDie = false;
	isDead = false;
	isActived = false;
	currentAnimation = animationItem;
}

Apple::~Apple()
{
}
