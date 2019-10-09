#pragma once
#include "Clock.h"
#include "DX.h"
#include "Screen.h"
#include "SpriteManager.h"
#include "Audio.h"
#include"Mesh.h"
#include"Camera.h"
#include"Effects.h"
#include"Font.h"
#include"Light.h"
#include"Video.h"
#include"GameLogic.h"
#include "MenuScene.h"
#include<map>
using namespace std;


//class Scene;

class Engine
{
private:
	// the current scene
	Scene* currentScene;
	// scene to switch to at end of frame
	Scene* toScene;
	//engine cores
	Clock* clock;
	AudioClass* audio;
	CameraClass* camera;
	DXClass* dx;
	EffectsClass* effects;
	LightClass* light;
	MeshClass* mesh;
	ScreenClass* screen;
	SpriteClass* spriteManager;
	VideoClass* video;
	FontClass* write;
	GameLogicClass* logic;
	MenuScene* menu;

	// called when engine first starts
	void Startup (HINSTANCE hInstance);
	// updates scene every frame
	void Update ();
	// renders frame ever frame
	void Render ();
	// called when engine ends
	void Shutdown ();
	
	void LoadSceneAssets(map<string, GameObject*> sceneAssets);
	void CreateCamera(GameObject* camObject);
	void CreateLight(GameObject* lightObject);
	int active;
public:
	Engine ();
	~Engine ();

	// game loop
	void Run (HINSTANCE hInstance);

	// getters/setters
	void SetCurrentScene (Scene* scene);
	Scene* GetCurrentScene ();
	AudioClass* Engine::GetAudio ();
	DXClass* GetDx ();
	ScreenClass* GetScreen ();
	SpriteClass* GetSpriteManager ();
	
	CameraClass* GetCamera();
	EffectsClass* GetEffects();
	LightClass* GetLight();
	MeshClass* GetMesh();
	VideoClass* GetVideo();
	FontClass* GetFont();
	GameLogicClass* GetLogic();
	enum { NOTHING = 0, MENU = 1, GAME = 2 };
};