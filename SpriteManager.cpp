#include"SpriteManager.h"



SpriteClass::SpriteClass()
{
	
}


SpriteClass::~SpriteClass()
{
	Shutdown();
}

void SpriteClass::CreateSprite(IDirect3DDevice9* DirectDevice)
{
	D3DXCreateSprite(DirectDevice, &Sprite);
}

void SpriteClass::LoadSprite(IDirect3DDevice9* DirectDevice, LPCWSTR fileName)
{
	D3DXIMAGE_INFO*	ImageInfo;
	ImageInfo = new D3DXIMAGE_INFO;
	SpriteInfo* sprite;
	sprite = new SpriteInfo;
	D3DXGetImageInfoFromFileW(fileName, ImageInfo);
	sprite->spriteCenter.x = (float)ImageInfo->Width / 2;
	sprite->spriteCenter.y = (float)ImageInfo->Height / 2;
	sprite->spriteCenter.z = 0.0f;
	D3DXCreateTextureFromFile(DirectDevice, fileName, &sprite->Texture);
	spriteList[fileName] = sprite;
}
	
void SpriteClass::StartRender()
{




	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void SpriteClass::Render(LPCWSTR fileName, D3DXMATRIX worldMat, float color[3])
{
	D3DXCOLOR temp;
	temp.r = color[0];
	temp.g = color[1];
	temp.b = color[2];
	Sprite->SetTransform(&worldMat);
	Sprite->Draw(spriteList[fileName]->Texture, 0, &spriteList[fileName]->spriteCenter, 
		0, temp);
}

void SpriteClass::EndRender()
{
	Sprite->End();
}
	
void SpriteClass::Shutdown()
{
	SAFE_RELEASE(Sprite);
	spriteList.empty();
}

IDirect3DTexture9* SpriteClass::ReturnSpriteTex(LPCWSTR name)
{
	return spriteList[name]->Texture;
}