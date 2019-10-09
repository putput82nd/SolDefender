#ifndef RESOURCE_H
#define RESOURCE_H
#pragma once
#include<string>
#include <d3dx9.h>
using namespace std;

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);

#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}


struct Mtrl
{
	Mtrl()
		:ambient(WHITE), diffuse(WHITE), spec(WHITE), specPower(8.0f){}
	Mtrl(const D3DXCOLOR& a, const D3DXCOLOR& d, 
		 const D3DXCOLOR& s, float power)
		:ambient(a), diffuse(d), spec(s), specPower(power){}

	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR spec;
	float specPower;
};
/*
LPCWSTR StringToLPCWSTR(string name);

LPCWSTR StringToLPCWSTR(string name)
{
	int len = 0;
	len = (int)strlen(name.c_str()) + 1;
	wchar_t *ucString = new wchar_t[len];
	mbstowcs(ucString, name.c_str(), len);
	LPCWSTR filename = (LPCWSTR)ucString;
	return filename;
}*/
#endif