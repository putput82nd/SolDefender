#pragma once
#include"Scene.h"
#include"Steering.h" //incomplete, Joshua Murrill is working on for AI movement
#include "Input.h"


class GameLogicClass
{
private:
	Steering steeringControl; //see above
	
public:
	InputClass* input;
	GameLogicClass();
	~GameLogicClass();
	void Startup(HWND hWnd, HINSTANCE hInstance);
	void Update(Scene* currScene);
	void Shutdown();
	InputClass* getInput();
};