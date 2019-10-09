#include "Engine.h"
#include"GameScene.h"
#include "MenuScene.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	Engine engine = Engine();

	engine.SetCurrentScene(new GameScene());
	engine.Run(hInstance);

	return 0;
}