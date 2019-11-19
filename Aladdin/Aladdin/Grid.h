#pragma once
#include <vector>
#include "Aladdin.h"
#include "debug.h"

/*
Grid có chiều dài, rộng = map và gồm nhiều cell, mỗi cell chứa 1 listObj
*/

struct Cell
{
	std::vector<CGameObject*> listBalls;
};

class CGrid
{
public:
	CGrid(int width, int height, int cellSize);
	~CGrid();

	// Thêm obj vào listObjs của cell thích hợp
	void AddObjToCell(CGameObject * obj);

	// Get Cell dựa trên vị trí của cell
	Cell& GetCell(int x, int y);
	// Get Cell dựa trên vị trí của obj
	Cell& GetCell(D3DXVECTOR3& posObj);

	// Tính toán các obj có thể bị va chạm (Tính toán các cell cần đc update với vị trí của camera)
	void CalcColliableObjs(CCamera *camera, vector<LPGAMEOBJECT>& coObjs);
private:
	int width, height;
	int cellSize;
	std::vector<Cell> listCells;
	int numXCells, numYCells;
};

