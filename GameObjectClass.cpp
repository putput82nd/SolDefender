#include"GameObjectClass.h"


GameObject::GameObject()
{
	name = "";
	type = noUpdate;
	fileName = L"";
	sound = "";
	isActive = true;
	assetType = audioType;
	
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;

	scale[0] = 0.0;
	scale[1] = 0.0;
	scale[2] = 0.0;

	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;

	orientation[0] = 0.0f;
	orientation[0] = 0.0f;
	orientation[0] = 0.0f;
	orientation[0] = 0.0f;

	ambient[0] = 0.0;
	ambient[1] = 0.0;
	ambient[2] = 0.0;
	ambient[3] = 0.0;

	diffuse[0] = 0.0;
	diffuse[1] = 0.0;
	diffuse[2] = 0.0;
	diffuse[3] = 0.0;

	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
	specular[3] = 0.0;

	maxSpeed = 0.0f;
	maxAngularAccel = 0.0f;
	maxAcceleration = 0.0;

	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;
}

GameObject::~GameObject()
{

}

void GameObject::SetPosition(float* pos)
{
	position[0] = pos[0];
	position[1] = pos[1];
	position[2] = pos[2];
}
	
void GameObject::SetScale(float scl[3])
{
	scale[0] = scl[0];
	scale[1] = scl[1];
	scale[2] = scl[2];
}
	
void GameObject::SetRotation(float* rot)
{
	rotation[0] = rot[0];
	rotation[1] = rot[1];
	rotation[2] = rot[2];
}
	
void GameObject::SetOrientation(float* ori)
{
	orientation[0] = ori[0];
	orientation[1] = ori[1];
	orientation[2] = ori[2];
	orientation[3] = ori[3];
}

void GameObject::SetAmbient(float amb[4])
{
	ambient[0] = amb[0];
	ambient[1] = amb[1];
	ambient[2] = amb[2];
	ambient[3] = amb[3];
}
	
void GameObject::SetDiffuse(float dif[4])
{
	diffuse[0] = dif[0];
	diffuse[1] = dif[1];
	diffuse[2] = dif[2];
	diffuse[3] = dif[3];
}
	
void GameObject::SetSpecular(float spec[4])
{
	specular[0] = spec[0];
	specular[1] = spec[1];
	specular[2] = spec[2];
	specular[3] = spec[3];
}

GameType GameObject::GetType () { return type; }
void GameObject::SetType (GameType value) { type = value; }

std::string GameObject::GetName () { return name; }
void GameObject::SetName (std::string value) { name = value; }

LPCWSTR GameObject::GetFileName(){return fileName;}
void GameObject::SetFileName(LPCWSTR name){fileName = name;}

bool GameObject::IsActive () { return isActive; }
void GameObject::IsActive (bool value) { isActive = value; }

D3DXVECTOR3 GameObject::GetPosition () { return position; }

D3DXVECTOR3 GameObject::GetScale () { return scale; }

D3DXVECTOR3 GameObject::GetRotation () { return rotation; }

D3DXQUATERNION GameObject::GetOrientation()
{
	return orientation;
}

void GameObject::SetAssetType(ObjectType type)
{
	assetType = type;
}
	
ObjectType GameObject::ReturnAssetType()
{
	return assetType;
}

float* GameObject::GetAmbient()
{
	return ambient;
}

float* GameObject::GetDiffuse()
{
	return diffuse;
}

float* GameObject::GetSpecular()
{
	return specular;
}

void GameObject::SetSound(char* name)
{
	sound = name;
}

char* GameObject::GetSoundName()
{
	return sound;
}

void GameObject::SetMaxSpeed(float max)
{
	maxSpeed = max;
}

float GameObject::GetMaxSpeed()
{
	return maxSpeed;
}

void GameObject::SetMaxAngularAccel(float value)
{
	maxAngularAccel = value;
}

float GameObject::GetMaxAngularAccel()
{
	return maxAngularAccel;
}

void GameObject::SetVelocity(float vel[3])
{
	velocity[0] = vel[0];
	velocity[1] = vel[1];
	velocity[2] = vel[2];
}

D3DXVECTOR3 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetMaxAcceleration(float max)
{
	maxAcceleration = max;
}

float GameObject::GetMaxAcceleration()
{
	return maxAcceleration;
}