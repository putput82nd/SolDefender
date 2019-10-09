#pragma once
#include<string>
#include "GameObjectClass.h"
#include <list>
using namespace std;


class Scene
{
private:
	list<GameObject*> objects;
	list<GameObject*> toAdd;
	list<GameObject*> toRemove;
	list<GameObject*> render;
	
	map<string, std::list<GameObject*>> types;
	map<string, GameObject*> instances;
	map<string, GameObject*> assets;

	void AddType (GameObject* object);
	void RemoveType (GameObject* object);

	void AddInstance (GameObject* object);
	void RemoveInstance (GameObject* object);

	int gameState;
	bool videoPlay;
public:
	Scene ();
	~Scene ();

	//Load scene assets
	virtual void CreateAssets();
	// called when the scene first starts
	virtual void Begin ();
	// called when the scene engs
	virtual void End ();
	void Update();
	void DeleteSceneAssets();
	void SetSceneAssets(GameObject* sceneAsset);
	void SetUpdatedObjects(list<GameObject*> updatedObjects);
	map<string, GameObject*> LoadAssets();
	GameObject* ReturnAsset(string name);
	GameObject* Add (GameObject* object);
	GameObject* Remove (GameObject* object);
	GameObject* GetInstance(std::string name);

	list<GameObject*> ReturnGameObjects();
	list<GameObject*> ReturnGameRenders();

	void ChangeGameState(int state);
	int ReturnGameState();
	void SetVideoPlay(bool value);
	bool ReturnVideoPlay();
};