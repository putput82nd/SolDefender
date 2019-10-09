//#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include<vector>
#include<string>
#include"Vertex.h"
#include<map>
#include"Physics.h"
#pragma once
#include"Resource.h"
using namespace std;





struct Model
{
	ID3DXMesh*			mesh;
	vector<Mtrl>		mtrls;
	vector<IDirect3DTexture9*> texs;
	AABB				boundingBox;
	BoundingSphere		boundingSphere;
};


class MeshClass
{
private:
	map<LPCWSTR, Model*> modelList;
public:
	MeshClass();
	~MeshClass();
	void InitMeshClass(IDirect3DDevice9* gd3dDevice);
	void LoadXFile(LPCWSTR filename, IDirect3DDevice9* gd3dDevice);
	void ComputeBoundingBox(LPCWSTR fileName);
	void ComputeBoundingSphere(LPCWSTR fileName);
	void Render(LPCWSTR fileName, IDirect3DDevice9* gd3dDevice, UINT i);
	void DeleteMesh(LPCWSTR fileName);
	IDirect3DTexture9* ReturnTexture(LPCWSTR fileName, UINT i);
	Mtrl ReturnMaterial(LPCWSTR fileName, UINT i);
	DWORD ReturnNumMtrls(LPCWSTR fileName);
};