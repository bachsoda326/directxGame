#include "EndScene.h"
#include "SceneManager.h"
#include "OpenScene.h"

EndScene::EndScene()
{
	GameSound::getInstance()->stop(GAME2_MUSIC);
	GameSound::getInstance()->play(BACKGROUND_MUSIC, true);

	LoadResources();
}

void EndScene::LoadResources()
{
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ENDSCENE);
	endMap = new Sprite(ID_TEX_ENDSCENE, 0, 0, 340, 250, 0, 0, texture);

	Camera::GetInstance()->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	aladdin->SetPosition(ALADDIN_POTISION_ENDSCENE_X, ALADDIN_POTISION_ENDSCENE_Y);
	// Aladdin lúc đầu bay từ trái qua
	aladdin->Fly();
}

void EndScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Scene::UpdateKey();
	aladdin->Update(dt);
	// khi bay hết thì chuyển qua ôm
	if (aladdin->x >= ENDSCENE_PASS_FLY_X)
	{
		aladdin->SetPosition(ALADDIN_POTISION_ENDSCENE_HUG_X, ALADDIN_POTISION_ENDSCENE_HUG_Y);
		aladdin->Hug();
	}

	// k.tra nhấn phím chuyển màn
	if (isKey1Up)
	{
		SceneManager::GetInstance()->ReplaceScene(new OpenScene());
		return;
	}
}

void EndScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		endMap->Draw(0, 0, D3DXVECTOR2(0, 0));
		aladdin->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}


EndScene::~EndScene()
{
}
