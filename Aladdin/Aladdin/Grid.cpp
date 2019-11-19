#include "Grid.h"

CGrid::CGrid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize)
{
	numXCells = ceil((float)this->width / cellSize);
	numYCells = ceil((float)this->height / cellSize);

	// resize lại listCells
	listCells.resize(numXCells*numYCells);
}

CGrid::~CGrid()
{
}

void CGrid::AddObjToCell(CGameObject * obj)
{
	Cell &cell = GetCell(obj->GetPosition());
	cell.listBalls.push_back(obj);
}

Cell & CGrid::GetCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= numXCells) x = numXCells;
	if (y < 0) y = 0;
	if (y >= numYCells) y = numYCells;

	return listCells[x + y*numXCells];
}

Cell & CGrid::GetCell(D3DXVECTOR3 & posObj)
{
	int cellX = posObj.x / cellSize;
	int cellY = posObj.y / cellSize;

	return GetCell(cellX, cellY);
}

void CGrid::CalcColliableObjs(CCamera *camera, vector<LPGAMEOBJECT>& coObjs)
{
	int xTopLeftCamera = camera->GetPosition().x - SCREEN_WIDTH / 2;
	int yTopLeftCamera = camera->GetPosition().y - SCREEN_HEIGHT / 2;
	int xBotRightCamera = camera->GetPosition().x + SCREEN_WIDTH / 2;
	int yBotRightCamera = camera->GetPosition().y + SCREEN_HEIGHT / 2;

	int xTopLeftCell = xTopLeftCamera / cellSize;
	int yTopLeftCell = yTopLeftCamera / cellSize;
	int xBotRightCell = xBotRightCamera / cellSize;
	int yBotRightCell = yBotRightCamera / cellSize;
	/*DebugOut(L"[KT] Camera x topleft: %d\n", xTopLeftCell);
	DebugOut(L"[KT] Camera y topleft: %d\n", yTopLeftCell);
	DebugOut(L"[KT] Camera x botright: %d\n", xBotRightCell);
	DebugOut(L"[KT] Camera y botright: %d\n", yBotRightCell);*/

	for (int x = xTopLeftCell; x <= xBotRightCell; x++)
	{
		for (int y = yTopLeftCell; y <= yBotRightCell; y++)
		{
			Cell colliableCell = GetCell(x, y);

			for (int i = 0; i < colliableCell.listBalls.size(); i++)
			{
				coObjs.push_back(colliableCell.listBalls[i]);
			}
		}
	}
}
