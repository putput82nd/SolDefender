#include"Light.h"



LightClass::LightClass()
{

}

LightClass::~LightClass()
{
	
}

void LightClass::CreateLight(IDirect3DDevice9* gd3dDevice, float ambient[4], float diffuse[4],
		float specular[4], float range, float pos[3], float direction[3], string lightName)
{
	Light light;

	ZeroMemory(&light, sizeof(light));
	// Ambient light color emitted from this light
	light.Ambient.r = ambient[0];
	light.Ambient.g = ambient[1];
	light.Ambient.b = ambient[2];
	light.Ambient.a = ambient[3];
	// Diffuse light color emitted from this light
	light.Diffuse.r = diffuse[0];
	light.Diffuse.g = diffuse[1];
	light.Diffuse.b = diffuse[2];
	light.Diffuse.a = diffuse[3];
	// Specular light color emitted from this light
	light.Specular.r = specular[0];
	light.Specular.g = specular[1];
	light.Specular.b = specular[2];
	light.Specular.a = specular[3];
	// Light Position
	light.Position.x = pos[0];
	light.Position.y = pos[1];
	light.Position.z = pos[2];
	// Range of Light
	light.Range = range;
	// Light Attenuation
	light.Attenuation0 = 0.0f;	// Constant
	light.Attenuation1 = 0.05f;	// Linear
	light.Attenuation2 = 0.0f;	// Quadratic
	//Light Direction
	light.Direction.x = direction[0];
	light.Direction.y = direction[1];
	light.Direction.z = direction[2];
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, (D3DXVECTOR3*)&light.Direction);//this step may not be needed when using FX shaders
	//Put light in list
	lightList[lightName] = light;
}

void LightClass::DeleteLight(IDirect3DDevice9* gd3dDevice, string lightName)
{
	lightList.erase(lightName);
}

Light LightClass::ReturnLight(string lightName)
{
	return lightList[lightName];
}