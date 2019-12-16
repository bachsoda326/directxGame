#include "Scene.h"

Scene::Scene()
{
	bloodBar = new BloodBar();
	bloodBar->SetPosition(0, 10);
	face = new AladdinFace();
	face->SetPosition(10, 220);
	aladdinApple = new Apple();
	aladdinApple->collType = CollUnknown;
	aladdinApple->SetPosition(317, 230);
	aladdinRuby = new Ruby();
	aladdinRuby->collType = CollUnknown;
	aladdinRuby->SetPosition(280, 230);

	LoadResources();
}

void Scene::LoadResources()
{
	Textures * textures = Textures::GetInstance();
	// tạo texture lớn từ đường dẫn và add vào instance"textures"
	textures->Add(ID_TEX_ALADDIN, TEX_ALADDIN_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM, TEX_ITEMS_PATH, D3DCOLOR_XRGB(248, 0, 248));
	textures->Add(ID_TEX_PEDDLER, TEX_PEDDLER_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BRICK_TRAP, TEX_BRICK_TRAP_PATH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GUARDS, TEX_GUARDS_PATH, D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_BAT, TEX_BAT_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOOMSKELETON, TEX_BOOMSKELETON_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMYDEAD, TEX_ENEMYDEAD_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_ENEMYEXPLOSION, TEX_ENEMYEXPLOSION_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_ITEMACTIVED, TEX_ITEMACTIVED_PATH, D3DCOLOR_XRGB(255, 4, 253));
	textures->Add(ID_TEX_BLOODBAR, TEX_BLOODBAR_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOSS, TEX_BOSS_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_BBOX, TEX_BBOX_PATH, D3DCOLOR_XRGB(255, 255, 255));

	LoadFont();
	Aladdin::GetInstance()->LoadResources();
	bloodBar->LoadResources();
	face->LoadResources();
	aladdinApple->LoadResources();
	aladdinRuby->LoadResources();	
}

void Scene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*CheckCameraAndWorldMap();*/

	bloodBar->Update(dt);	
}

void Scene::Render()
{
	bloodBar->Render();
	face->Render();
	aladdinApple->Render();
	aladdinRuby->Render();
}

void Scene::CheckCameraAndWorldMap(int mapWidth, int mapHeight)
{
	// test Camera move when Mario is not on center screen
	//mCamera->SetPosition(mPlayer->GetPosition() + D3DXVECTOR3(100,0,0));
	Camera::GetInstance()->SetPosition(Aladdin::GetInstance()->GetPosition());

	if (Camera::GetInstance()->GetBound().left < 0)
	{
		//vi position cua Camera::GetInstance() ma chinh giua Camera::GetInstance()
		//luc nay o vi tri goc ben trai cua the gioi thuc
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetWidth() / 2, Camera::GetInstance()->GetPosition().y);
	}

	if (Camera::GetInstance()->GetBound().right > mapWidth)
	{
		//luc nay cham goc ben phai cua the gioi thuc
		Camera::GetInstance()->SetPosition(mapWidth - Camera::GetInstance()->GetWidth() / 2,
			Camera::GetInstance()->GetPosition().y);
	}

	if (Camera::GetInstance()->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetHeight() / 2);
	}

	if (Camera::GetInstance()->GetBound().bottom > mapHeight)
	{
		//luc nay cham day cua the gioi thuc
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition().x,
			mapHeight - Camera::GetInstance()->GetHeight() / 2);
	}
}

void Scene::LoadFont()
{
	ZeroMemory(&desc, sizeof(D3DXFONT_DESC));
	desc.Height = 13;
	desc.Width = 8;
	desc.Weight = 200;
	desc.MipLevels = D3DX_DEFAULT;
	desc.Italic = false;
	desc.CharSet = 0;
	desc.OutputPrecision = 0;
	desc.Quality = 0;
	desc.PitchAndFamily = 0;
	//strcpy_s(desc.FaceName, "Times New Roman"); // name will be something like "Arial"
	strcpy_s(desc.FaceName, "Arial");
	D3DXCreateFontIndirect(Game::GetInstance()->GetDirect3DDevice(), &desc, &numApples);
	D3DXCreateFontIndirect(Game::GetInstance()->GetDirect3DDevice(), &desc, &numRubies);
	D3DXCreateFontIndirect(Game::GetInstance()->GetDirect3DDevice(), &desc, &numLifes);
	desc.Height = 20;
	desc.Width = 10;
	desc.Weight = 400;
	D3DXCreateFontIndirect(Game::GetInstance()->GetDirect3DDevice(), &desc, &score);
}

void Scene::DrawFont(LPD3DXFONT font, float x, float y, float width, float height, int value)
{
	// set position of font 
	RECT rect;
	rect.top = (int)y;
	rect.left = (int)x;
	rect.bottom = (int)y + height;
	rect.right = (int)x + width;
		
	char intStr[20];
	_itoa_s(value, intStr, 10);
	//strcpy_s(intStr, status.c_str());
	if (font != score)
		font->DrawText(NULL, intStr, -1, &rect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	else
		font->DrawText(NULL, intStr, -1, &rect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));
}

void Scene::DrawFonts()
{
	DrawFont(score, 280, 10, 35, 25, Aladdin::GetInstance()->score);
	DrawFont(numLifes, 35, 230, 35, 25, Aladdin::GetInstance()->numLifes);
	DrawFont(numRubies, 285, 230, 35, 25, Aladdin::GetInstance()->numRubies);
	DrawFont(numApples, 318, 230, 35, 25, Aladdin::GetInstance()->numApples);
}

Scene::~Scene()
{
}
