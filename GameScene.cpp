#include"GameScene.h"


GameScene::GameScene()
{
	CreateAssets();
}
	
GameScene::~GameScene()
{

}

void GameScene::Begin()
{
	GameObject* temp;
	float position[3];
	float scale[3];
	float rotation[3];
	float orientation[4];
	float amb[4];
	float dif[4];
	float spec[4];

	orientation[0] = 0, orientation[1] = 0, orientation[2] = 0, orientation[3] = 0;
	rotation[0] = 0, rotation[1] = 0, rotation[2] = 0;

	temp = new GameObject;
	position[0] = -0.577f, position[1] = 0.577f, position[2] = -0.577f;
	amb[0] = 0.6f, amb[1] = 0.6f, amb[2] = 0.6f, amb[3] = 1.0f;
	dif[0] = 1.0f, dif[1] = 1.0f, dif[2] = 1.0f, dif[3] = 1.0f;
	spec[0] = 1.0f, spec[1] = 1.0f, spec[2] = 1.0f, spec[3] = 1.0f;
	temp->SetName("light");
	temp->SetType(noUpdate);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->SetAmbient(amb);
	temp->SetDiffuse(dif);
	temp->SetSpecular(spec);
	temp->IsActive(false);
	Add(temp);

	temp = new GameObject;
	scale[0] = 0, scale [1] = 0, scale[2] = 0;
	position[0] = 0.0, position[1] = 0.0, position[2] = 2100.0;
	amb[0] = 0.0f, amb[1] = 1.0f, amb[2] = 0.0f, amb[3] = 0.0f;
	temp->SetName("camera");
	temp->SetType(noUpdate);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->SetAmbient(amb);
	temp->IsActive(false);
	Add(temp);

	temp = new GameObject;
	temp = ReturnAsset("effects");
	temp->IsActive(false);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 0, position[1] = 0, position[2] = 0;
	temp = ReturnAsset("spaceDome");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);
	
	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 0, position[1] = 0, position[2] = 0;
	temp = ReturnAsset("planet");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 1000, position[1] = 0, position[2] = 0;
	temp = ReturnAsset("moon");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 0, position[1] = 0, position[2] = 2000;
	temp = ReturnAsset("humanMotherShip");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 0, position[1] = 0, position[2] = 1850;
	temp = ReturnAsset("player");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = 0, position[1] = 20, position[2] = 1850;
	temp = ReturnAsset("humanMinion");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = -1000, position[1] = 0, position[2] = 0;
	temp = ReturnAsset("asteroidRing");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = -1000, position[1] = 30, position[2] = 0;
	temp = ReturnAsset("asteroid1");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = -1000, position[1] = -30, position[2] = 0;
	temp = ReturnAsset("asteroid2");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = -1000, position[1] = 0, position[2] = 30;
	temp = ReturnAsset("asteroid3");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);

	temp = new GameObject;
	scale[0] = 1, scale [1] = 1, scale[2] = 1;
	position[0] = -1000, position[1] = 0, position[2] = -30;
	temp = ReturnAsset("asteroid4");
	temp->SetOrientation(orientation);
	temp->SetRotation(rotation);
	temp->SetScale(scale);
	temp->SetPosition(position);
	temp->IsActive(true);
	Add(temp);
}

void GameScene::CreateAssets()
{
	GameObject* sceneAsset;
	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"spaceDome.x");
	sceneAsset->SetName("spaceDome");
	sceneAsset->SetType(noUpdate);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"planet.x");
	sceneAsset->SetName("planet");
	sceneAsset->SetType(noUpdate);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"moon.x");
	sceneAsset->SetName("moon");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"humanMotherShip.x");
	sceneAsset->SetName("humanMotherShip");
	sceneAsset->SetType(AI1);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"humanMinion.x");
	sceneAsset->SetName("humanMinion");
	sceneAsset->SetType(AI2);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"humanFighter.x");
	sceneAsset->SetName("player");
	sceneAsset->SetType(player);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"asteroidRing.x");
	sceneAsset->SetName("asteroidRing");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"asteroid1.x");
	sceneAsset->SetName("asteroid1");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"asteroid2.x");
	sceneAsset->SetName("asteroid2");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"asteroid3.x");
	sceneAsset->SetName("asteroid3");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"asteroid4.x");
	sceneAsset->SetName("asteroid4");
	sceneAsset->SetType(nonStaticEnviron);
	sceneAsset->SetAssetType(meshType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"DirLightTex.fx");
	sceneAsset->SetName("effects");
	sceneAsset->SetType(noUpdate);
	sceneAsset->SetAssetType(effectsType);
	SetSceneAssets(sceneAsset);

	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"whitetex.dds");
	sceneAsset->SetName("defaultTex");
	sceneAsset->SetType(noUpdate);
	sceneAsset->SetAssetType(spriteType);
	SetSceneAssets(sceneAsset);
}