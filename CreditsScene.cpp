#include"CreditsScene.h"



CreditsScene::CreditsScene()
{

}
	
CreditsScene::~CreditsScene()
{

}

void CreditsScene::Begin()
{
	GameObject* sceneAsset;
	sceneAsset = new GameObject;
	sceneAsset->SetFileName(L"creditsVideo.avi");
	sceneAsset->SetName("creditsVideo");
	SetSceneAssets(sceneAsset);
}
	
void CreditsScene::CreateAssets()
{
	

}