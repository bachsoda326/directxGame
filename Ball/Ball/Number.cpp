#include "Number.h"

CNumber::CNumber()
{
}

CNumber::~CNumber()
{
}

void CNumber::Render()
{
	animations[num]->Render(x, y);
}

void CNumber::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

void CNumber::IncreaseNum()
{
	if (num == 9)
		num = 0;
	else
		num++;
}
