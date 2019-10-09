#pragma once
#include<d3dx9.h>
#include<map>
#include<string>
#include"Resource.h"
using namespace std;
#include"Light.h"

struct FX
{
	ID3DXEffect* gFX;
	D3DXHANDLE   ghTech;
	D3DXHANDLE   ghWVP;
	D3DXHANDLE   ghWorldInvTrans;
	D3DXHANDLE   ghEyePos;
	D3DXHANDLE   ghWorld;
	D3DXHANDLE   ghTex;
	D3DXHANDLE	 ghLightVecW;
	D3DXHANDLE	 ghDiffuseMtrl;
	D3DXHANDLE	 ghDiffuseLight;
	D3DXHANDLE	 ghAmbientMtrl;
	D3DXHANDLE	 ghAmbientLight;
	D3DXHANDLE	 ghSpecularMtrl;
	D3DXHANDLE	 ghSpecularLight;
	D3DXHANDLE	 ghSpecularPower;
};

class EffectsClass
{
private:
	map<LPCWSTR, FX*> fxList;
public:
	EffectsClass();
	~EffectsClass();
	void LoadEffects(LPCWSTR fxName, IDirect3DDevice9* gd3dDevice);
	void DeleteEffects(LPCWSTR fileName);
	void Begin(LPCWSTR fileName, UINT numPasses);
	void BeginPass(LPCWSTR fileName, UINT i);
	void SetFX(LPCWSTR fileName, D3DXMATRIX camViewProj, D3DXMATRIX world);
	void SetLight(LPCWSTR fileName, Light light);
	void SetFXMaterial(LPCWSTR fileName, Mtrl mtrl);
	void SetFXTexture(LPCWSTR fileName, IDirect3DTexture9* tex);
	void End(LPCWSTR fileName);
	void EndPass(LPCWSTR fileName);
	void Reset(LPCWSTR fileName);
	void SetCamPos(LPCWSTR fileName, D3DXVECTOR3 camPos);
	void SetTech(LPCWSTR fileName);
};