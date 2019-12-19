#include "Enemy.h"
#include "Aladdin.h"

Enemy::Enemy()
{
	LoadResources();
}

void Enemy::LoadResources()
{
	LPDIRECT3DTEXTURE9 texEnemyDead = Textures::GetInstance()->Get(ID_TEX_ENEMYDEAD);
	// khởi tạo các animation
	animationDie = new Animation("Animation", XML_ENEMYDEAD_ANIMATION_PATH, texEnemyDead, 50);
}

void Enemy::Die()
{
	if (!isDie)
	{
		currentAnimation = animationDie;
		vy = 0;
		vx = 0;
		y = (this->Top() + this->Bottom()) / 2;
		isDie = true;
	}
	else
	{		
		if (currentAnimation->isActionFinish())
		{
			isDead = true;			
		}
	}
}

Enemy::~Enemy()
{
}
