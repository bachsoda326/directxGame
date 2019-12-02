#include "ThinGuard.h"
#include "Textures.h"

ThinGuard::ThinGuard(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 20;
	y = yDraw + 62;
	direction = true;
	collType = CollEnemy;
}

void ThinGuard::LoadResources()
{
	LPDIRECT3DTEXTURE9 texGuards = Textures::GetInstance()->Get(ID_TEX_GUARDS);

	animationRun = new Animation("Run", XML_THINGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_1 = new Animation("Cut_1", XML_THINGUARD_ANIMATION_PATH, texGuards, 100);
	animationHurt = new Animation("Hurt", XML_THINGUARD_ANIMATION_PATH, texGuards, 100);
	animationDie = new Animation("Animation", XML_ENEMYDEAD_ANIMATION_PATH, texGuards, 100);
	
	currentAnimation = animationCut_1;
	animationCut_1->SetFrame(5, 5);
}

void ThinGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

void ThinGuard::Render()
{
	if (true)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
	else
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));

	//RenderBoundingBox();
}

void ThinGuard::SetAnimation(ThinGuardAnimations ani)
{
	switch (ani)
	{
	case ANI_RUN:
	{
		//reset frame when press event
		currentAnimation = animationRun;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_1:
	{
		currentAnimation = animationCut_1;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_HURT:
	{
		currentAnimation = animationHurt;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE:
	{
		currentAnimation = animationDie;
		//currentAnimation->ResetFrame();
		break;
	}
	}
}

ThinGuard::~ThinGuard()
{
}
