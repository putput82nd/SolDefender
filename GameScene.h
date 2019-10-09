#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene ();
	~GameScene ();

	void Begin ();
	void CreateAssets();
};