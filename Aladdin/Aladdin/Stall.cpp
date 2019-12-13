#include "Stall.h"

Stall::Stall()
{
	isDead = false;
	canTrade = true;
	direction = true;
	objType = OBJStall;
}

void Stall::LoadResources()
{
	LPDIRECT3DTEXTURE9 texPeddler = Textures::GetInstance()->Get(ID_TEX_PEDDLER);

	animationDefault = new Animation("Stall", XML_PEDDLER_ANIMATION_PATH, texPeddler, 100);	

	currentAnimation = animationDefault;
}

void Stall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (currentAnimation->GetCurrentFrame() == 5)
		animationDefault->SetFrame(5, 5);

	if (!canTrade && currentAnimation->GetCurrentFrame() == 0)
		animationDefault->SetFrame(1, 5);
}

void Stall::Trade()
{
	Aladdin::GetInstance()->numRubies -= 10;
	Aladdin::GetInstance()->numLifes += 5;
	canTrade = false;

	animationDefault->SetFrame(4, 0);
}

void Stall::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->GetState() == Aladdin::LOOK_UP && Aladdin::GetInstance()->numRubies >= 10)
			if (canTrade)
				Trade();
	}
}

Stall::~Stall()
{
}
