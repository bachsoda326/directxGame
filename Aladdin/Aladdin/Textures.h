#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
Manage texture database
*/
class Textures
{
	static Textures * __instance;
	// kiểu như listTextures
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	float width, height;

	Textures();
	// Add texture vào instance"textures"
	void Add(int id, LPCSTR filePath, D3DCOLOR transparentColor);
	// Get texture theo id trong instance"textures"
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static Textures * GetInstance();
};