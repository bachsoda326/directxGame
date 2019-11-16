#include "Grid.h"

CGrid::CGrid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize)
{
	numXCells = ceil((float)this->width / cellSize);
	numYCells = ceil((float)this->height / cellSize);

	//Allocate all the Cells
	listCells.resize(numXCells*numYCells);
}

CGrid::~CGrid()
{
}

void CGrid::AddBall(CAladdin * ball)
{
	Cell &cell = GetCell(ball->GetPosition());
	cell.listBalls.push_back(ball);
}

Cell & CGrid::GetCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= numXCells) x = numXCells;
	if (y < 0) y = 0;
	if (y >= numYCells) y = numYCells;

	return listCells[x + y*numXCells];
}

Cell & CGrid::GetCell(D3DXVECTOR3 & pos)
{
	int cellX = pos.x / cellSize;
	int cellY = pos.y / cellSize;

	return GetCell(cellX, cellY);
}

void CGrid::CalcColliableObjs(CCamera *camera, vector<LPGAMEOBJECT>& coObjects)
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
				coObjects.push_back(colliableCell.listBalls[i]);
			}
		}
	}
}
