#pragma once

#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include<map>
using namespace std;
#include"Resource.h"


struct SpriteInfo
{
	D3DXVECTOR3         spriteCenter;
	IDirect3DTexture9*	Texture;
};

class SpriteClass
{
private:
	ID3DXSprite*		Sprite;
	map<LPCWSTR, SpriteInfo*> spriteList;
public:
	SpriteClass();
	~SpriteClass();
	void CreateSprite(IDirect3DDevice9* DirectDevice);
	void LoadSprite(IDirect3DDevice9* DirectDevice, LPCWSTR fileName);
	void StartRender();
	void Render(LPCWSTR name, D3DXMATRIX worldMat, float color[3]);
	void EndRender();
	void Shutdown();
	IDirect3DTexture9* ReturnSpriteTex(LPCWSTR name);
};