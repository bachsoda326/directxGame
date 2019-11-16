#include "Apple.h"
#include "Textures.h"

CApple::CApple()
{
	isDead = false;
	objType = OBJApple;
	currentAnimation = new CAnimation(100);
}

void CApple::SetObjectFromID()
{
	if (id == 6)
		collType = CollApple;
	else
		collType = CollItem;
}

void CApple::LoadResources()
{
	LPDIRECT3DTEXTURE9 texAladdin = CTextures::GetInstance()->Get(ID_TEX_ALADDIN);

	animationBurst_1 = new CAnimation("Burst_1", XML_APPLE_ANIMATION_PATH, texAladdin, 100);
	animationSplit_Half = new CAnimation("Split_Half", XML_APPLE_ANIMATION_PATH, texAladdin, 100);

	xInit = x;
	yInit = y;

	if (collType == CollApple)
	{
		x = xDraw + 7;
		y = yDraw + 6;
		state = FLING;
		typeSplit_Half = true;
		currentAnimation = animationBurst_1;
		animationBurst_1->SetFrame(0, 0);
	}
	else
	{
		x = xDraw + 5;
		y = yDraw + 6;
		state = NOTMOVING;
		isActived = false;
		direction = true;
		currentAnimation = animationBurst_1;
		animationBurst_1->SetFrame(0, 0);
	}

	isDie = false;
	isDead = false;
	nx = 0.0f;
	ny = 0.0f;
}

void CApple::ProcessInput()
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

void CApple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	//simulate fall down (gravity)
	if (collType == CollApple)
		vy += 0.015f;
}

void CApple::Render()
{
	if (true)
	{
		// Vector trans to support move camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - CCamera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - CCamera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, direction, trans);
	}
	else
		currentAnimation->Render(x, y, xDraw, yDraw, direction, D3DXVECTOR2(0, 0));
}

void CApple::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


CApple::~CApple()
{
}

void CApple::Move()
{
	if (collType == CollApple)
		state = FLING;
	else
	{
		vy = 0;
		vx = 0;
	}
}

void CApple::Burst()
{
	switch (state)
	{
	case BURST:
	{
		if (currentAnimation->isActionFinish())
		{
			isDead = true;
			CAladdin::GetInstance()->DeleteApple(this);
		}
		break;
	}
	default:
	{
		state = BURST;
		currentAnimation = animationBurst_1;
		currentAnimation->SetFrame(1, 5);
		isDie = true;
		vx = 0;
		vy = 0;
		break;
	}
	}
}

void CApple::Active()
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
		/*status = ACTIVED;
		xmlFilePath = ITEMACTIVED_XMLFILEPATH;
		apple_image->setImage(TextureManager::GetInstance()->GetItemActivedTexture());
		apple_image->setFrame(0, 3);
		animation_rate = 10;
		vy = 0;
		vx = 0;
		arx = (this->left() + this->right()) / 2;
		ary = (this->top() + this->bottom()) / 2;
		isDie = true;
		isActive = true;
		break;*/
	}
	}
}

void CApple::Split_Half()
{
	/*switch (status)
	{
	case SPLIT_HALF:
	{
		if (apple_image->getIndex() == 6)
		{
			apple_image->setFrame(7, 10);
			apple_image->setIndex(8);
			Apple*obj = new Apple();
			obj->id = 6;
			obj->x = this->x;
			obj->y = this->y;
			obj->direction = this->direction;
			if (direction)
				obj->vx = -0.7f;
			else
				obj->vx = 0.7f;
			obj->vy = -1.2f;
			obj->setObjectFromID();
			obj->LoadResources();
			Aladdin::GetInstance()->createApple(obj);
			obj->typeSplit_Half = false;
			obj->Split_Half();
		}
		break;
	}
	default:
	{
		if (typeSplit_Half)
		{
			status = SPLIT_HALF;
			apple_image->setFrame(6, 10);
			animation_rate = 5;
			if (direction)
				vx = -1.0f;
			else
				vx = 1.0f;
			vy = -1.5f;
		}
		else
		{
			status = SPLIT_HALF;
			apple_image->setFrame(7, 8);
			animation_rate = 5;
		}
		break;
	}
	}*/
}
