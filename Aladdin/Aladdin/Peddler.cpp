#include "Peddler.h"
#include "Textures.h"

Peddler::Peddler(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 6;
	y = yDraw + 52;
	isDead = false;
	canCreate = true;
	direction = true;
	collType = CollUnknown;
	objType = OBJPeddler;
}

void Peddler::LoadResources()
{
	/*stall->LoadResources();*/

	LPDIRECT3DTEXTURE9 texPeddler = Textures::GetInstance()->Get(ID_TEX_PEDDLER);

	animationStand = new Animation("Stand", XML_PEDDLER_ANIMATION_PATH, texPeddler, 100);
	animationCreate = new Animation("Create", XML_PEDDLER_ANIMATION_PATH, texPeddler, 62);

	currentAnimation = animationStand;
	SetState(STANDING);
}

void Peddler::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/

	switch (state)
	{
	case CREATING:
		Create();
		break;
	default:
		Stand();
		break;
	}

	if (stall != nullptr)
	{
		stall->Update(dt);

		Collision::CheckCollision(Aladdin::GetInstance(), stall);
	}
}

void Peddler::Render()
{
	GameObject::Render();

	if (stall != nullptr)
		stall->Render();	
}

void Peddler::SetAnimation(PeddlerAnimations ani)
{
	switch (ani)
	{
	case ANI_STAND:
	{
		//reset frame when press event
		currentAnimation = animationStand;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CREATE:
	{
		currentAnimation = animationCreate;
		//currentAnimation->ResetFrame();
		break;
	}
	}
}

void Peddler::Stand()
{
	switch (state)
	{
	case STANDING:
	{
		int i = currentAnimation->GetCurrentFrame();
		if (i == 13)
			animationStand->SetFrame(12, 0);
		if (i == 3)
			animationStand->SetFrame(4, 13);
		break;
	}
	default:
		SetState(STANDING);
		SetAnimation(ANI_STAND);
		break;
	}	
}

void Peddler::Create()
{
	switch (state)
	{
	case CREATING:
	{
		if (currentAnimation->isActionFinish())
		{
			GameSound::getInstance()->play(PEDDLERSTALL_MUSIC);
			CreateStall();
			SetState(DONE);
			SetPosition(x + 65, y);
		}
		break;
	}
	default:
		SetState(CREATING);
		SetAnimation(ANI_CREATE);
		break;
	}
}

void Peddler::CreateStall()
{	
	stall = new Stall();
	stall->LoadResources();
	stall->SetPosition(x, y);

	canCreate = false;
}

void Peddler::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		if (canCreate)
			Create();
	}
}

Peddler::~Peddler()
{
}
