#include "BossScene.h"
#include "SceneManager.h"

BossScene::BossScene()
{
	GameSound::getInstance()->stop(NEXT_MUSIC);
	GameSound::getInstance()->play(GAME2_MUSIC, true);
	LoadResources();
}

void BossScene::LoadResources()
{
	grid = new Grid(BOSSMAP_WIDTH, BOSSMAP_HEIGHT, CELL_SIZE);

	LoadObj("txt\\ObjBoss_obj.txt");
	LoadGridObj("txt\\ObjBoss_grid.txt");

	aladdin->SetPosition(ALADDIN_POTISION_BOSSMAP_X, ALADDIN_POTISION_BOSSMAP_Y);
	aladdin->xInit = ALADDIN_POTISION_BOSSMAP_X_INIT;
	aladdin->yInit = ALADDIN_POTISION_BOSSMAP_Y_INIT;
	aladdin->SetState(Aladdin::STANDING);
	aladdin->vx = 0;
	
	boss->LoadResources();

	bossMap = new TileMap();
	bossMap->LoadTileMap(ID_TEX_TILESHEET_BOSSMAP, TEX_TILESHEET_BOSSMAP_PATH, TXT_TILEMAP_BOSSMAP_PATH);

	for (int i = 0; i < listFireCarpets.size(); i++)
	{
		listFireCarpets[i]->LoadResources();
	}
	for (int i = 0; i < listLeftApples.size(); i++)
	{
		listLeftApples[i]->LoadResources();
		listLeftApples[i]->isDie = true;
		listLeftApples[i]->isDead = true;
	}
	for (int i = 0; i < listRightApples.size(); i++)
	{
		listRightApples[i]->LoadResources();
		listRightApples[i]->isDie = true;
		listRightApples[i]->isDead = true;
	}
}

void BossScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjs)
{
	Scene::UpdateKey();
	UpdateCamera(CAMERA_BOSSMAP_WIDTH, CAMERA_BOSSMAP_HEIGHT);
	
	coObjects.clear();
	coObjects.push_back(baseGround);
	// tính toán những obj nằm trong vùng camera rồi đưa vào list coObjects
	grid->CalcColliableObjs(Camera::GetInstance(), coObjects);		

	aladdin->Update(dt);
	boss->Update(dt);
	bloodBar->Update(dt);

	// khi Aladdin hết táo thì có thể tạo táo khi màn k còn táo
	if (aladdin->numApples == 0)
	{		
		canCreateApple = true;
		for (int i = 0; i < listLeftApples.size(); i++)
		{
			if (!listLeftApples[i]->isDead)
			{
				canCreateApple = false;
				break;
			}			
		}
		for (int i = 0; i < listRightApples.size(); i++)
		{
			if (!listRightApples[i]->isDead)
			{
				canCreateApple = false;
				break;
			}			
		}
	}

	if (canCreateApple && aladdin->numApples == 0)
	{
		canCreateApple = false;
		if (!boss->direction)
		{
			for (int i = 0; i < listLeftApples.size(); i++)			
			{				
				listLeftApples[i]->ResetProper();
			}
		}
		else
		{
			for (int i = 0; i < listRightApples.size(); i++)			
			{				
				listRightApples[i]->ResetProper();
			}
		}
	}

	// set lại gía trị va chạm nx, ny của Aladdin
	aladdin->nx = 0;
	aladdin->ny = 0;
	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt);
		// va chạm Aladdin vs các obj
		Collision::CheckCollision(aladdin, coObjects[i]);
		// va chạm táo Aladdin vs các obj
		for (int j = 0; j < aladdin->GetList()->size(); j++)
		{
			Collision::CheckCollision(aladdin->GetList()->at(j), coObjects[i]);
		}
		// va chạm của lửa tạo bởi thảm lửa vs Aladdin
		switch (coObjects[i]->id)
		{
		case 5: case 6: case 7: case 8:				// 5,6,7,8 là id của thảm lửa
		{
			for (int k = 0; k < coObjects[i]->GetList()->size(); k++)
			{
				Collision::CheckCollision(coObjects[i]->GetList()->at(k), aladdin);
			}
			break;
		}
		}		
	}	
	Collision::CheckCollision(aladdin, boss);
	// va chạm táo của Aladdin vs Boss
	for (int i = 0; i < aladdin->GetList()->size(); i++)
	{
		Collision::CheckCollision(aladdin->GetList()->at(i), boss);		
	}
	// va chạm sao hoặc lửa của Boss vs Aladdin, nền đất, cột
	for (int j = 0; j < boss->GetList()->size(); j++)
	{
		Collision::CheckCollision(boss->GetList()->at(j), aladdin);
		Collision::CheckCollision(boss->GetList()->at(j), baseGround);
		for (int i = 0; i < listPillars.size(); i++)
		{
			Collision::CheckCollision(boss->GetList()->at(j), listPillars[i]);
		}
	}	

	// chuyển màn khi Boss chết
	if (boss->isDead || isKey1Up)
	{
		SceneManager::GetInstance()->ReplaceScene(new NextScene(4));
		return;
	}	
	if (aladdin->isDead)
	{
		SceneManager::GetInstance()->ReplaceScene(new OpenScene());
		return;
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
		coObjects.clear();		
		// tính toán những obj nằm trong vùng camera rồi đưa vào list coObjects
		grid->CalcColliableObjs(Camera::GetInstance(), coObjects);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (aladdin->isDead)
		{
			GameSound::getInstance()->stop(GAME2_MUSIC);
			return;
		}
		if (!aladdin->isDie)
		{
			bossMap->Render(Camera::GetInstance());
			boss->Render();
			for (int i = 0; i < coObjects.size(); i++)
			{
				coObjects[i]->Render();
			}			
		}
		else
			Abu::GetInstance()->Render();
		aladdin->Render();		
		Scene::Render();

		spriteHandler->End();
		DrawFonts();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}

void BossScene::LoadObj(string path)
{
	GameObject *obj = 0;

	fstream fs;
	fs.open(path);

	int numObjs = 0;
	fs >> numObjs;

	int index;
	string name;
	int xDraw, yDraw, width, height;

	for (int i = 0; i < numObjs; i++)
	{
		fs >> index;
		fs >> name;
		fs >> xDraw;
		fs >> yDraw;
		fs >> width;
		fs >> height;

		if (name == "Boss")
		{			
			boss->x = xDraw + 22;
			boss->y = yDraw + 71;
			boss->w = width;
			boss->h = height;
			boss->id = index;
		}
		else if (name == "Ground")
		{
			baseGround = new Ground(xDraw, yDraw, width, height);
			baseGround->id = index;
			baseGround->collType = CollGround;
		}
		else if (name == "Pillar")
		{
			obj = new Ground(xDraw, yDraw, width, height);
			obj->id = index;
			obj->collType = CollFence;
			listPillars.push_back(obj);
		}
		else if (name == "FireCarpet")
		{
			obj = new FireCarpet(xDraw, yDraw, width, height);
			obj->id = index;
			listFireCarpets.push_back(obj);
		}
		else if (name == "LeftApple")
		{
			obj = new Apple(xDraw, yDraw, width, height);
			obj->id = index;
			obj->collType = CollItem;
			listLeftApples.push_back(obj);
		}
		else if (name == "RightApple")
		{
			obj = new Apple(xDraw, yDraw, width, height);
			obj->id = index;
			obj->collType = CollItem;
			listRightApples.push_back(obj);
		}
	}

	fs.close();
}

void BossScene::LoadGridObj(string path)
{
	GameObject *objGround = 0;

	fstream fs;
	fs.open(path);	

	int cellIndex = 0;;
	int objIndex = 0;

	string line;					// dòng 1
	while (getline(fs, line))
	{
		istringstream iss(line);	// tạo 1 string stream từ dòng 1	
		vector<int> listId;
		for (int n; iss >> n;)		// đọc số nguyên từ stream vào mảng a
			listId.push_back(n);

		cellIndex = listId[0];
		for (int i = 1; i < listId.size(); i++)
		{			
			// biến k.tra xem đã thêm obj với objIndex đang xét chưa, true thì xét objIndex mới tiếp
			bool isAdded = false;

			objIndex = listId[i];			
			for (int t = 0; t < listPillars.size(); t++)
			{
				if (isAdded == true) break;
				if (listPillars[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listPillars[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listFireCarpets.size(); t++)
			{
				if (isAdded == true) break;
				if (listFireCarpets[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listFireCarpets[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listLeftApples.size(); t++)
			{
				if (isAdded == true) break;
				if (listLeftApples[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listLeftApples[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listRightApples.size(); t++)
			{
				if (isAdded == true) break;
				if (listRightApples[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listRightApples[t]);
					isAdded = true;
					break;
				}
			}			
		}
	}

	fs.close();
}

BossScene::~BossScene()
{
}
