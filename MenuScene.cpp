#include "MenuScene.h"

MenuScene::MenuScene()
{
	//null all the objects we will be useing
	myInput = NULL;
	background = NULL;
	newGame = NULL;
	newGameHighlighted = NULL;
	exit = NULL;
	exitHighlighted = NULL;
}
	
MenuScene::~MenuScene()
{
	//Delete everything we created for the menu;
	if (myInput != NULL){delete myInput;}
	if (background != NULL){delete background;}
	if (newGame != NULL){delete newGame;}
	if (newGameHighlighted != NULL){delete newGameHighlighted;}
	if (exit != NULL){delete exit;}
	if (exitHighlighted != NULL){delete exitHighlighted;}
}

void MenuScene::Begin(InputClass* input, LPDIRECT3DDEVICE9 device )
{
	myInput = input;
	//0 is new game, 1 is exit;
	menuItemSelected = 0;
	message = 0;
	/*//load menu Images
	//load background menubackground.jpg
	background = new Surface();
	background->loadSurface(device, "menubackground.jpg");
	
	//load new game image
	newGame = new Surface();
	newGame->loadSurface(device, "newgame.jpg");
	newGame->setPosition(0,0);
	newGameHighlighted = new Surface();
	newGameHighlighted->loadSurface(device, "newgameh.jpg");
	newGameHighlighted->setPosition(0,0);
	//load exit image
	exit = new Surface();
	exit->loadSurface(device, "exit.jpg");
	exit->setPosition(10,10);
	exitHighlighted = new Surface();
	exitHighlighted->loadSurface(device, "exith.jpg");
	exitHighlighted->setPosition(20,40);*/
	background = new SpriteClass;
	background->CreateSprite(device);
	background->LoadSprite(device, LPCWSTR("menubackground.jpg"));

	newGame = new SpriteClass;
	newGame->CreateSprite(device);
	newGame->LoadSprite(device, LPCWSTR("newgame.jpg"));

	newGameHighlighted = new SpriteClass;
	newGameHighlighted->CreateSprite(device);
	newGameHighlighted->LoadSprite(device, LPCWSTR("newgameh.jpg"));

	exit = new SpriteClass;
	exit->CreateSprite(device);
	exit->LoadSprite(device, LPCWSTR("exit.jpg"));

	exitHighlighted = new SpriteClass;
	exitHighlighted->CreateSprite(device);
	exitHighlighted->LoadSprite(device, LPCWSTR("exith.jpg"));
}
void MenuScene::update()
{
	myInput->Poll();

	//get menu movement input
	if (myInput->KeyPress(DIK_UP) || myInput->KeyPress(DIK_DOWN)){
		if (menuItemSelected == 0){
			menuItemSelected = 1;
		} else {
			menuItemSelected = 0;
		}
	}

	//get menu pressed input
	if (myInput->KeyPress(DIK_RETURN)){
		switch (menuItemSelected){
			case 0: {message = NEW_GAME; break;}
			case 1: {message = EXIT; break;}
		}	

	}
}
void MenuScene::CreateAssets()
{

}
void MenuScene::Render(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX pWorldMat;
	float m_xPos, m_yPos, m_zPos, color[3];
	m_xPos = 10;
	m_yPos = 10;
	m_zPos = 0;
	color[3]=(1.0f, 1.0f, 0.5f);
	/*//render menu
	//render background
	background->render(device);
	
	//render menu items based on which is highlighted
	if (menuItemSelected == 0)
	{
		newGameHighlighted->render(device);
		exit->render(device);
	} 
	else 
	{
		newGame->render(device);
		exitHighlighted->render(device);
	}	*/
	D3DXMatrixIdentity(&pWorldMat);
	D3DXMatrixTranslation(&pWorldMat, m_xPos, m_yPos, m_zPos);
	background->StartRender();
	newGame->StartRender();
	newGameHighlighted->StartRender();
	exit->StartRender();
	exitHighlighted->StartRender();

	background->Render(LPCWSTR("menubackground.jpg"), pWorldMat, color);
	background->EndRender();
	m_xPos = 100;
	m_yPos = 100;
	m_zPos = 0;

	D3DXMatrixIdentity(&pWorldMat);
	D3DXMatrixTranslation(&pWorldMat, m_xPos, m_yPos, m_zPos);

	newGame->Render(LPCWSTR("newgame.jpg"), pWorldMat, color);
	newGame->EndRender();

	newGame->Shutdown();
	background->Shutdown();
}
int MenuScene::getMessage()
{
	return message;
}