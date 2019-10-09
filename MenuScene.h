#pragma once
#include "Scene.h"
#include "Input.h"
#include "SpriteManager.h"

class MenuScene
{
public:
	MenuScene();
	~MenuScene();

	void Begin(InputClass* input, LPDIRECT3DDEVICE9 device);
	void CreateAssets();
	void update();
	void Render(LPDIRECT3DDEVICE9);
	int getMessage();
	enum { NEW_GAME = 1, EXIT = 2 };

private:
	InputClass* myInput;
	SpriteClass* background;
	SpriteClass* newGame;
	SpriteClass* newGameHighlighted;
	SpriteClass* exit;
	SpriteClass* exitHighlighted;
	int menuItemSelected;
	int message;
};