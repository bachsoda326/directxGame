#include "BallTrap.h"
#include "Textures.h"


BallTrap::BallTrap(float left, float top, float width, float height)
{
	x = left;
	y = top;
	isDead = false;
	direction = true;
	collType = CollUnknown;
	objType = OBJBallTrap;	
	srand(time(0));
}

void BallTrap::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBallTrap = Textures::GetInstance()->Get(ID_TEX_BRICK_TRAP);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_BALLTRAP_ANIMATION_PATH, texBallTrap, 100);
	// animation ban đầu
	currentAnimation = animationDefault;
	// random animation khởi tạo
	int ranFrame = rand() % 15;
	animationDefault->SetFrame(ranFrame, 14);
}

void BallTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
}

void BallTrap::Render()
{	
	// lấy frame animation hiện tại
	int i = currentAnimation->GetCurrentFrame();	
	// khi frame là frame đầu hoặc cuối thì cho animation đi ngược lại
	if (i == 0)
		animationDefault->SetFrame(1, 14);
	if (i == 14)
		animationDefault->SetFrame(13, 0);

	GameObject::Render();
	//RenderBoundingBox();
}

BallTrap::~BallTrap()
{
}
