#include "Scene.h"
#include <iostream>

Scene::Scene ()
{
	gameState = 0;
	videoPlay = false;
}

Scene::~Scene ()
{
}

void Scene::Begin ()
{
}

void Scene::End ()
{
}

void Scene::CreateAssets()
{

}

GameObject* Scene::Add (GameObject* object)
{
	if (object->GetName() != "") AddInstance(object);
	toAdd.push_back(object);
	return object;
}

GameObject* Scene::Remove (GameObject* object)
{
	if (object->GetName() != "") RemoveInstance(object);
	toRemove.push_back(object);
	return object;
}

void Scene::AddType (GameObject* object)
{
	types[object->GetName()].push_front(object);
}

void Scene::RemoveType (GameObject* object)
{
	types.erase(object->GetName());
}

void Scene::AddInstance (GameObject* object)
{
	instances[object->GetName()] = object;
}

void Scene::RemoveInstance (GameObject* object)
{
	instances.erase(object->GetName());
}

GameObject* Scene::GetInstance (std::string name)
{
	if (instances.find(name) != instances.end())
	{
		return instances[name];
	}
	else
	{
		return nullptr;
	}
}

void Scene::SetSceneAssets(GameObject* sceneAsset)
{
	assets[sceneAsset->GetName()] = sceneAsset;
}

void Scene::DeleteSceneAssets()
{
	assets.empty();
}

GameObject* Scene::ReturnAsset(std::string name)
{
	return assets[name];
}

map<string, GameObject*> Scene::LoadAssets()
{
	return assets;
}

void Scene::Update()
{
	render.clear();
	if (objects.size() > 0)
	{
		for (std::list<GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
		{
			// update children
			if ((*i)->IsActive())
			{
				render.push_back((*i));
			}
		}
	}
	// --------------------------------- ADD
	if (toAdd.size() > 0)
	{
		for (std::list<GameObject*>::iterator i = toAdd.begin(); i != toAdd.end(); ++i)
		{
			// update children
			if ((*i)->IsActive())
			{
				objects.push_back((*i));
			}
		}
		toAdd.clear();
	}
	// --------------------------------- REMOVE
	if (toRemove.size() > 0)
	{
		for (std::list<GameObject*>::iterator i = toRemove.begin(); i != toRemove.end(); ++i)
		{
			// update children
			if ((*i)->IsActive())
			{
				objects.remove((*i));
			}
		}
		toRemove.clear();
	}
}

list<GameObject*> Scene::ReturnGameObjects()
{
	return objects;
}

list<GameObject*> Scene::ReturnGameRenders()
{
	return render;
}

void Scene::SetUpdatedObjects(list<GameObject*> updatedObjects)
{
	objects = updatedObjects;
}

void Scene::ChangeGameState(int state)
{
	gameState = state;
}
	
int Scene::ReturnGameState()
{
	return gameState;
}

void Scene::SetVideoPlay(bool value)
{
	videoPlay = value;
}

bool Scene::ReturnVideoPlay()
{
	return videoPlay;
}