#include "BloodBar.h"

BloodBar::BloodBar()
{
}

void BloodBar::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBloodBar = Textures::GetInstance()->Get(ID_TEX_BLOODBAR);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_BLOODBAR_ANIMATION_PATH, texBloodBar, 100);
	// animation ban đầu
	currentAnimation = animationDefault;
	animationDefault->SetFrame(1, 4);

	x = xDraw + 20;
	y = yDraw + 13;
	direction = true;	
	isDead = false;
	nx = 0.0f;
	ny = 0.0f;
	vx = 0;
	vy = 0;
	isBlink = 0;
	// máu của thanh máu
	oldBlood = Aladdin::GetInstance()->blood;
	startBlink = GetTickCount();	
	// set animation ban đầu từ máu hiện tại của Aladdin
	switch (oldBlood)
	{
	case 1:
		animationDefault->SetFrame(0, 0);
		break;
	case 2:
		animationDefault->SetFrame(22, 23);
		break;
	case 3:
		animationDefault->SetFrame(20, 21);
		break;
	case 4:
		animationDefault->SetFrame(17, 19);
		break;
	case 5:
		animationDefault->SetFrame(13, 16);
		break;
	case 6:
		animationDefault->SetFrame(9, 12);
		break;
	case 7:
		animationDefault->SetFrame(5, 8);
		break;
	}	
}

void BloodBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBlink != 0)
	{
		// xử lý nhấp nháy (mờ nhiều lần)
		DWORD endBlink = GetTickCount();
		if (endBlink - startBlink > 350)
		{
			isBlink = isBlink % 2 + 1;
			startBlink = endBlink;
		}
	}
	// update animtion của thanh máu khi máu Aladdin thay đổi
	if (oldBlood != Aladdin::GetInstance()->blood)
	{
		switch (Aladdin::GetInstance()->blood)
		{
		case 1:
		{
			animationDefault->SetFrame(0, 0);
			isBlink = 1;			
			break;
		}
		case 2:
		{
			animationDefault->SetFrame(22, 23);
			isBlink = 1;			
			break;
		}
		case 3:
		{
			animationDefault->SetFrame(20, 21);
			isBlink = 0;			
			break;
		}
		case 4:
		{
			animationDefault->SetFrame(17, 19);
			isBlink = 0;			
			break;

		}
		case 5:
		{
			animationDefault->SetFrame(13, 16);
			isBlink = 0;			
			break;
		}
		case 6:
		{
			animationDefault->SetFrame(9, 12);
			isBlink = 0;			
			break;
		}
		case 7:
		{
			animationDefault->SetFrame(5, 8);
			isBlink = 0;			
			break;
		}
		default:
		{
			if (!Aladdin::GetInstance()->isDie)
			{
				animationDefault->SetFrame(1, 4);
				isBlink = 0;
			}			
			break;
		}
		}
		oldBlood = Aladdin::GetInstance()->blood;
	}
	/*if (animationDefault->isActionFinish())
	{
		int firstFrame, lastFrame;
		firstFrame = animationDefault->GetFirstFrame();
		lastFrame = animationDefault->GetLastFrame();
		animationDefault->SetFrame(lastFrame, firstFrame);
	}*/
}

void BloodBar::Render()
{	
	// vẽ phần khói (máu) của thanh máu
	if (currentAnimation->GetCurrentFrame() > 0)
	{
		x += 29;
		y -= 7;
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0), isBlink);

		x -= 29;
		y += 7;
	}
	// vẽ phần đèn của thanh máu
	int currentIndex;
	currentIndex = currentAnimation->GetCurrentFrame();
	currentAnimation->SetCurrentFrame(0);	
	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0), isBlink);
	currentAnimation->SetCurrentFrame(currentIndex);
}

BloodBar::~BloodBar()
{
}
