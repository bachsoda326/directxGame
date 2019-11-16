#pragma once
#include <vector>
#include "Aladdin.h"
#include "debug.h"

struct Cell
{
	std::vector<CAladdin*> listBalls;
};

class CGrid
{
public:
	CGrid(int width, int height, int cellSize);
	~CGrid();

	// Add ball to listBalls of a suitable cell 
	void AddBall(CAladdin *ball);

	// Get Cell based on cell coordinates
	Cell& GetCell(int x, int y);
	// Get Cell based on window obj coordinates
	Cell& GetCell(D3DXVECTOR3& pos);

	// Calculate objects that can be collited (Calculate cells need to be updated with camera's potition)
	void CalcColliableObjs(CCamera *camera, vector<LPGAMEOBJECT>& coObjects);
private:
	int width, height;
	int cellSize;
	std::vector<Cell> listCells;
	int numXCells, numYCells;
};

