#include "BossScene.h"

BossScene::BossScene()
{
	GameSound::getInstance()->play(GAME2_MUSIC, true);
}

void BossScene::LoadResources()
{
	aladdin->SetPosition(300, 100);
	aladdin->xInit = 300;
	aladdin->yInit = 100;
	boss = new Boss();
	boss->SetPosition(465, 262);
	boss->LoadResources();

	bossMap = new TileMap();
	bossMap->LoadTileMap(ID_TEX_TILESHEET_BOSSMAP, TEX_TILESHEET_BOSSMAP_PATH, TXT_TILEMAP_BOSSMAP_PATH);

	baseGround = new Ground(100, 361, 755, 56);
	baseGround->collType = CollGround;

	leftPillar = new Ground(96, 0, 37, 403);
	leftPillar->collType = CollFence;
	rightPillar = new Ground(834, 0, 37, 403);
	rightPillar->collType = CollFence;

	car1 = new FireCarpet();
	car1->SetPosition(141, 300);
	car1->w = 98;
	car1->h = 48;
	car1->LoadResources();
	car2 = new FireCarpet();
	car2->SetPosition(337, 300);
	car2->w = 98;
	car2->h = 48;
	car2->LoadResources();
	car3 = new FireCarpet();
	car3->SetPosition(533, 300);
	car3->w = 98;
	car3->h = 48;
	car3->LoadResources();
	car4 = new FireCarpet();
	car4->SetPosition(729, 300);
	car4->w = 98;
	car4->h = 48;
	car4->LoadResources();

}

void BossScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CheckCameraAndWorldMap(CAMERA_BOSSMAP_WIDTH, CAMERA_BOSSMAP_HEIGHT);

	aladdin->Update(dt);
	boss->Update(dt);
	car1->Update(dt);
	car2->Update(dt);
	car3->Update(dt);
	car4->Update(dt);
	Scene::Update(dt);

	aladdin->nx = 0;
	aladdin->ny = 0;
	Collision::CheckCollision(aladdin, baseGround);
	Collision::CheckCollision(aladdin, leftPillar);
	Collision::CheckCollision(aladdin, rightPillar);
	Collision::CheckCollision(aladdin, boss);
	Collision::CheckCollision(aladdin, car1);
	Collision::CheckCollision(aladdin, car2);
	Collision::CheckCollision(aladdin, car3);
	Collision::CheckCollision(aladdin, car4);
	for (int i = 0; i < aladdin->GetListApples()->size(); i++)
	{
		Collision::CheckCollision(aladdin->GetListApples()->at(i), boss);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), baseGround);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), leftPillar);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), rightPillar);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), car1);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), car2);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), car3);
		Collision::CheckCollision(aladdin->GetListApples()->at(i), car4);
	}
	for (int j = 0; j < boss->GetList()->size(); j++)
	{
		Collision::CheckCollision(boss->GetList()->at(j), aladdin);
		Collision::CheckCollision(boss->GetList()->at(j), baseGround);
		Collision::CheckCollision(boss->GetList()->at(j), leftPillar);
		Collision::CheckCollision(boss->GetList()->at(j), rightPillar);
	}
}

void BossScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		/*coObjects.clear();
		coObjects.push_back(baseGround);
		coObjects.push_back(basePillar);
		grid->CalcColliableObjs(Camera::GetInstance(), coObjects);*/

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		bossMap->Render();
		/*for (int i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Render();
		}*/
		boss->Render();
		car1->Render();
		car2->Render();
		car3->Render();
		car4->Render();
		aladdin->Render();		
		Scene::Render();

		spriteHandler->End();
		DrawFonts();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}


BossScene::~BossScene()
{
}
