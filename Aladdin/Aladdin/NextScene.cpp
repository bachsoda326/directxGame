#include "NextScene.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "EndScene.h"

NextScene::NextScene(int sceneId)
{
	GameSound::getInstance()->stop(GAME1_MUSIC);
	GameSound::getInstance()->stop(GAME2_MUSIC);
	GameSound::getInstance()->play(NEXT_MUSIC);
	LoadResources();

	this->sceneId = sceneId;
}

void NextScene::LoadResources()
{	
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_NEXTSCENE);
	nextMap = new Sprite(ID_TEX_NEXTSCENE, 0, 0, 340, 250, 0, 0, texture);

	Camera::GetInstance()->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	aladdin->direction = true;
	aladdin->SetPosition(350, 220);
	aladdin->RunNextScene();
	abu->SetPosition(300, 220);
	abu->beginStat = 1;
	abu->LoadResources();
}

void NextScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	aladdin->Update(dt);
	abu->Update(dt);

	if (aladdin->x + 50 <= 0)
	{
		if (sceneId == 3)
			SceneManager::GetInstance()->ReplaceScene(new BossScene());
		else if (sceneId == 4)
			SceneManager::GetInstance()->ReplaceScene(new EndScene());
		return;
	}
}

void NextScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		nextMap->Draw(0, 0, D3DXVECTOR2(0, 0));
		aladdin->Render();
		abu->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}

NextScene::~NextScene()
{
}
