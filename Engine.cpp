#include <Windows.h>
#include <iostream>
#include "Engine.h"

Engine::Engine ()
{
	currentScene = nullptr;
	toScene = nullptr;
	clock = new Clock();
	screen = new ScreenClass();
	dx = new DXClass();
	spriteManager = new SpriteClass();
	audio = new AudioClass();
	camera = new CameraClass();
	light = new LightClass();
	mesh = new MeshClass();
	video = new VideoClass();
	effects = new EffectsClass();
	logic = new GameLogicClass();
}

Engine::~Engine ()
{
}

void Engine::Startup (HINSTANCE hInstance)
{
	//create a new Menu
	menu = new MenuScene();
	menu->Begin(logic->getInput(), dx->ReturnDirectDevice());
	active =MENU;
	screen->InitWindow(hInstance);
	dx->InitDX(screen->ReturnGameWnd(), screen->ReturnGameWindowed());
	audio->InitAudio(screen->ReturnGameWnd());
	spriteManager->CreateSprite(dx->ReturnDirectDevice());
	mesh->InitMeshClass(dx->ReturnDirectDevice());
	logic->Startup(screen->ReturnGameWnd(), hInstance);
}

void Engine::Shutdown ()
{
	screen->Shutdown();
	dx->Shutdown();
	audio->Shutdown();
	spriteManager->Shutdown();
	logic->Shutdown();
}

void Engine::Run (HINSTANCE hInstance)
{
	Startup(hInstance);
	
	// msg structure to catch window messages
	MSG msg; 
	ZeroMemory(&msg, sizeof(msg));

	// game loop
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//update the menu
		if (active == MENU)
		{
			menu->update();
			if (menu->getMessage() == MenuScene::EXIT)
			{
				active = NOTHING;
				PostQuitMessage(0);
				delete menu;
			}
			if (menu->getMessage() == MenuScene::NEW_GAME)
			{
				if(logic != NULL)
				{
				}
				active = GAME;
			}
		}
		// calculate elapsed time
		clock->UpdateElapsed();

		// update components
		if (active == GAME)
		{
			clock->StartUpdate();
			Update();
			clock->EndUpdate();
		}
		// render renderable components
		if (active == MENU)
		{
			menu->Render(dx->ReturnDirectDevice());
		}

		if (active == GAME)
		{
			clock->StartRender();
			Render();
			clock->EndRender();
		}
	}

	Shutdown();
}

void Engine::SetCurrentScene (Scene* scene)
{
	toScene = scene;
}

Scene* Engine::GetCurrentScene ()
{
	return currentScene;
}

void Engine::Update ()
{

	// change scene at end of frame
	if (toScene)
	{
		if (currentScene) currentScene->End();
		currentScene = toScene;
		//currentScene->engine = this;
		currentScene->CreateAssets();
		LoadSceneAssets(currentScene->LoadAssets());
		currentScene->Begin();
		if(currentScene->GetInstance("light"))
			CreateLight(currentScene->GetInstance("light"));
		if(currentScene->GetInstance("camera"))
			CreateCamera(currentScene->GetInstance("camera"));
		toScene = nullptr;
	}
	if(!currentScene->ReturnVideoPlay())
	{
		if(currentScene != nullptr)
			logic->Update(currentScene);
		//insert class of functions for player control here
		currentScene->Update();
		camera->Update();
	}
	else
		video->VideoCompleted(screen->ReturnGameWnd());
}

void Engine::Render ()
{
	if(!currentScene->ReturnVideoPlay())
	{
		D3DXMATRIX worldMat;
		D3DXMatrixIdentity(&worldMat);
		dx->StartRender(screen->ReturnGameWnd());
		effects->SetLight(currentScene->GetInstance("effects")->GetFileName(), light->ReturnLight("light"));
		effects->SetTech(currentScene->GetInstance("effects")->GetFileName());
		effects->SetCamPos(currentScene->GetInstance("effects")->GetFileName(), camera->ReturnPosition());
		UINT numPasses = 0;
		effects->Begin(currentScene->GetInstance("effects")->GetFileName(), numPasses);
		spriteManager->StartRender();
		std::list<GameObject*> renderList;
		renderList = currentScene->ReturnGameRenders();
		for (std::list<GameObject*>::iterator i = renderList.begin(); i != renderList.end(); ++i)
		{
			if((*i)->ReturnAssetType() == meshType)
			{
				D3DXMatrixTranslation(&worldMat, (*i)->GetPosition()[0], (*i)->GetPosition()[1], (*i)->GetPosition()[2]);
				effects->SetFX(currentScene->GetInstance("effects")->GetFileName(), camera->ReturnViewProj(), worldMat);
				for(UINT j = 0; j < mesh->ReturnNumMtrls((*i)->GetFileName()); j++)
				{
					effects->BeginPass(currentScene->GetInstance("effects")->GetFileName(), j);
					effects->SetFXMaterial(currentScene->GetInstance("effects")->GetFileName(),
						mesh->ReturnMaterial((*i)->GetFileName(), j));
					if(mesh->ReturnTexture((*i)->GetFileName(), j) != 0)
					{
						effects->SetFXTexture(currentScene->GetInstance("effects")->GetFileName(),
							mesh->ReturnTexture((*i)->GetFileName(), j));
					}
					else
					{
						effects->SetFXTexture(currentScene->GetInstance("effects")->GetFileName(),
							spriteManager->ReturnSpriteTex(currentScene->GetInstance("defaultTex")->GetFileName()));
					}
					mesh->Render((*i)->GetFileName(), dx->ReturnDirectDevice(), j);
					effects->EndPass(currentScene->GetInstance("effects")->GetFileName());
				}
			}
			else if((*i)->ReturnAssetType() == spriteType)
			{
				D3DXMatrixTranslation(&worldMat, (*i)->GetPosition()[0], (*i)->GetPosition()[1], (*i)->GetPosition()[2]);
				spriteManager->Render((*i)->GetFileName(), worldMat, (*i)->GetDiffuse());
			}
			spriteManager->EndRender();
		}
		renderList.clear();
		effects->End(currentScene->GetInstance("effects")->GetFileName());
		dx->EndRender();
	}
	else
	{
		video->InitVideo();
		video->PlayVideo(screen->ReturnGameWnd(), currentScene->GetInstance("creditsVideo")->GetFileName());
	}
}

DXClass* Engine::GetDx () { return dx; }
ScreenClass* Engine::GetScreen () { return screen; }
SpriteClass* Engine::GetSpriteManager () { return spriteManager; }
AudioClass* Engine::GetAudio () { return audio; }

CameraClass* Engine::GetCamera()
{
	return camera;
}

EffectsClass* Engine::GetEffects()
{
	return effects;
}
	
LightClass* Engine::GetLight()
{
	return light;
}
	
MeshClass* Engine::GetMesh()
{
	return mesh;
}
	
VideoClass* Engine::GetVideo()
{
	return video;
}

FontClass* Engine::GetFont()
{
	return write;
}

GameLogicClass* Engine::GetLogic()
{
	return logic;
}

void Engine::LoadSceneAssets(map<string, GameObject*> sceneAssets)
{
	 for(map<string, GameObject*>::iterator i = sceneAssets.begin(); i != sceneAssets.end(); i++)
	 {
		 switch(i->second->ReturnAssetType())
		 {
		 case(0):
			 audio->LoadSound(i->second->GetSoundName());
			 break;
		 case(1):
			 effects->LoadEffects(i->second->GetFileName(), dx->ReturnDirectDevice());
			 effects->Reset(i->second->GetFileName());
			 break;
		 case(2):
			 write->CreateFontW(dx->ReturnDirectDevice(),i->second->GetPosition()[0], i->second->GetPosition()[1], 
				 i->second->GetPosition()[2], i->second->GetName(), i->second->GetFileName());
			 break;
		 case(3):
			 mesh->LoadXFile(i->second->GetFileName(), dx->ReturnDirectDevice());
			 break;
		 case(4):
			 spriteManager->LoadSprite(dx->ReturnDirectDevice(), i->second->GetFileName());
			 break;
		 }
	 }
}

void Engine::CreateCamera(GameObject* camObject)
{
	camera->LookAt(camObject->GetPosition(), camObject->GetScale(), camObject->GetAmbient());
	RECT rect;
	GetWindowRect(screen->ReturnGameWnd(), &rect);
	camera->SetLens(D3DX_PI * 0.25f, (float)rect.right / (float)rect.bottom, 1.0f, 100000.0f);		
}
	
void Engine::CreateLight(GameObject* lightObject)
{
	light->CreateLight(dx->ReturnDirectDevice(), lightObject->GetAmbient(), lightObject->GetDiffuse(), lightObject->GetSpecular(),
		lightObject->GetMaxAcceleration(), lightObject->GetPosition(), lightObject->GetScale(), lightObject->GetName());
}