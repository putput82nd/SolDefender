#ifndef LIGHT_H
#define LIGHT_H

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include<map>
#include<string>
using namespace std;


struct Light
{
    D3DXCOLOR		Diffuse;
    D3DXCOLOR		Specular;
    D3DXCOLOR	    Ambient;
    D3DXVECTOR3     Position;
    D3DXVECTOR3     Direction;
    float           Range;            /* Cutoff range */
    float           Falloff;          /* Falloff */
    float           Attenuation0;     /* Constant attenuation */
    float           Attenuation1;     /* Linear attenuation */
    float           Attenuation2;     /* Quadratic attenuation */
    float           Theta;            /* Inner angle of spotlight cone */
    float           Phi;              /* Outer angle of spotlight cone */
};



class LightClass
{
private:
	map<string, Light> lightList;
public:
	LightClass();
	~LightClass();
	void CreateLight(IDirect3DDevice9* gd3dDevice, float ambient[4], float diffuse[4],
		float specular[4], float range, float pos[3], float direction[3], string lightName);
	void DeleteLight(IDirect3DDevice9* gd3dDevice, string lightName);
	Light ReturnLight(string lightName);
};
#endif