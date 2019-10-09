#include"GameLogic.h"



GameLogicClass::GameLogicClass()
{
	input = new InputClass();
}

GameLogicClass::~GameLogicClass()
{

}

void GameLogicClass::Startup(HWND hWnd, HINSTANCE hInstance)
{
	input->InitInput(hWnd, hInstance);
}

void GameLogicClass::Shutdown()
{
	input->Shutdown();
}
InputClass* GameLogicClass::getInput()
{
	return input;
}
void GameLogicClass::Update(Scene* currScene)
{
	std::string temp;
	if(!currScene->ReturnVideoPlay())
	{
		input->Poll();

		std::list<GameObject*> updateList;
		updateList = currScene->ReturnGameObjects();
		switch(currScene->ReturnGameState())
		{
		case(0):
			currScene->ChangeGameState(1);
			break;
		case(1):
			for (std::list<GameObject*>::iterator i = updateList.begin(); i != updateList.end(); ++i)
			{
				if((*i)->GetType() == 0)
				{
				}
				else if((*i)->GetType() == 1)
				{
				}
				else if((*i)->GetType() == 2)
				{
				}
				else if((*i)->GetType() == 3)
				{
					float* p = (*i)->GetPosition();
					p[0] += 0.01;
					p[1] += 0.0;
					p[2] += 0.0;
					(*i)->SetPosition(p);
					break;
				}
			}
			currScene->SetUpdatedObjects(updateList);
			break;
		case(2):
			
			break;
		}
	}
	
}