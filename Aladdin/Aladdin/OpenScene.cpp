#include "OpenScene.h"
#include "SceneManager.h"

OpenScene::OpenScene()
{
	GameSound::getInstance()->stop(GAME1_MUSIC);
	GameSound::getInstance()->stop(GAME2_MUSIC);
	GameSound::getInstance()->stop(NEXT_MUSIC);
	GameSound::getInstance()->stop(BACKGROUND_MUSIC);
	GameSound::getInstance()->play(BACKGROUND_MUSIC, true);

	LoadResources();
}

void OpenScene::LoadResources()
{
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_OPENSCENE);
	openMap = new Sprite(ID_TEX_OPENSCENE, 0, 0, 340, 250, 0, 0, texture);

	Camera::GetInstance()->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void OpenScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Scene::UpdateKey();

	if (isKeyEnterUp)
	{
		SceneManager::GetInstance()->ReplaceScene(new DungeonScene());
		return;
	}
}

void OpenScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		openMap->Draw(0, 0, D3DXVECTOR2(0, 0));		

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}

OpenScene::~OpenScene()
{
}
