#pragma once
#include <string>
#include <list>
#include <map>
#include<Windows.h>
#include"Physics.h"

enum ObjectType
{
	 audioType, effectsType, fontType, meshType, spriteType
};

enum GameType
{
	noUpdate, AI1, AI2, player, nonStaticEnviron
};

class GameObject
{
private:
	GameType type;
	std::string name;
	char* sound;
	bool isActive;
	LPCWSTR fileName;
	ObjectType assetType;

	D3DXVECTOR3		position;		//use [0] for font ht//use [1] for font width//use [2] for font bool italic
	D3DXVECTOR3		scale;			//use for direction for light, use for target for camera
	D3DXVECTOR3		rotation;
	D3DXQUATERNION	orientation;
	D3DXVECTOR3		velocity;
	float maxSpeed;
	float maxAngularAccel;
	float maxAcceleration;	//use for range for light
	
	float ambient[4];		//use for up for camera
	float diffuse[4];		//use for color for sprites
	float specular[4];
public:
	GameObject();
	~GameObject();
	GameType GetType ();
	void SetType (GameType gameType);
	std::string GetName ();
	void SetName (std::string value);
	LPCWSTR GetFileName();
	void SetFileName(LPCWSTR name);
	bool IsActive ();
	void IsActive (bool value);
	void SetPosition(float* pos);
	D3DXVECTOR3 GetPosition();
	void SetScale(float* scl);
	D3DXVECTOR3 GetScale();
	void SetRotation(float* rot);
	D3DXVECTOR3 GetRotation();
	void SetOrientation(float* ori);
	D3DXQUATERNION GetOrientation();
	void SetAmbient(float* amb);
	float* GetAmbient();
	void SetDiffuse(float* dif);
	float* GetDiffuse();
	void SetSpecular(float* spec);
	float* GetSpecular();
	void SetSound(char* name);
	char* GetSoundName();
	void SetMaxSpeed(float max);
	void SetMaxRotation(float max);
	void SetVelocity(float* vel);
	D3DXVECTOR3 GetVelocity();
	void SetMaxAcceleration(float max);
	float GetMaxAcceleration();
	float GetMaxSpeed();
	void SetMaxAngularAccel(float value);
	float GetMaxAngularAccel();
	void SetAssetType(ObjectType objectType);
	ObjectType ReturnAssetType();
};