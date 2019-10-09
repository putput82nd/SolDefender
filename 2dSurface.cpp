#include "2dSurface.h"

//
//   FUNCTION: Surface(void)
//
//   PURPOSE: Constructor for the 2d Surface class
//
Surface::Surface(void)
{
	surface = NULL;
}
//
//   FUNCTION: ~Surface(void)
//
//   PURPOSE: deconstructor for the 2d Surface class
//
Surface::~Surface(void)
{
	if( surface != NULL) 
	{
        surface->Release();
		surface = NULL;
	}
}
//
//   FUNCTION: loadSurface(LPDIRECT3DDEVICE9 device, std::string filename, int w, int h)
//
//   PURPOSE: create a plainSurface, and load a bitmap onto it, then set initial source and dest rects.
//
bool Surface::loadSurface(LPDIRECT3DDEVICE9 device, std::string filename)
{
	imageScale = 100; //set our image scale to 100%
	//record the height and width

	HRESULT hResult;
	// Get the width and height of the image
	D3DXIMAGE_INFO imageInfo;
	hResult = D3DXGetImageInfoFromFile(LPCWSTR(filename.c_str()), &imageInfo);
	if FAILED (hResult){
		return false;
	}

	height = imageInfo.Height;
	width = imageInfo.Width;

	//create the Off Screen Surface
	hResult = device->CreateOffscreenPlainSurface(width, //surface width
		height, //surface height
		D3DFMT_A8R8G8B8, //surface format, D3DFMT_A8R8G8B8 is a 32 bit format with 8 alpha bits
		D3DPOOL_DEFAULT, //create it in the default memory pool
		&surface, //the pointer to our surface 
		NULL
		);

	if (FAILED(hResult))
		return false;

	//load the surface from the a file
	hResult = D3DXLoadSurfaceFromFile(surface, //the surface we just created
		NULL, //palette entry, NULL for non 256 color formats
		NULL, //dest rect, NULL for the whole surface
		LPCWSTR(filename.c_str()), // the file we wish to load
		NULL, // Source Rect, NULL for the whole file
		D3DX_DEFAULT, //Filter 
		0, // Color key, color that should be used as transparent.
		NULL // pointer to a D3DXIMAGE_INFO structure, for holding info about the image.
		);

	if (FAILED(hResult))
		return false;

	//set rects
	destRect.left = 0;
	destRect.top = 0;
	destRect.bottom = destRect.top + height;
	destRect.right = destRect.left + width;

	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.bottom = destRect.top + height;
	srcRect.right = destRect.left + width;

	return true;
}

//
//   FUNCTION: render(LPDIRECT3DDEVICE9 pDevice)
//
//   PURPOSE: gets the backbuffer and copys our surface onto it 
//
void Surface::render(LPDIRECT3DDEVICE9 pDevice)
{

	//Scale the destination based on current imageScale
	destRect.bottom = destRect.top + (int)(height * (imageScale / 100));
	destRect.right = destRect.left + (int)(width * (imageScale / 100));

	IDirect3DSurface9* backbuffer = NULL;
	pDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	
	pDevice->StretchRect(surface, &srcRect, backbuffer, &destRect, D3DTEXF_NONE);
}

//
//   FUNCTION: setPosition(int x, int y)
//
//   PURPOSE: sets the destination position on the screen, x and y are the top left corner.
//
void Surface::setPosition(int x, int y){
	destRect.left = x;
	destRect.top = y;
	destRect.bottom = destRect.top + height;
	destRect.right = destRect.left + width;
}

//
//   FUNCTION: setSize(int percent)
//
//   PURPOSE: sets size the image is to be drawn in percent.
//
void Surface::setSize(int percent){
	imageScale = percent;
}


//
//   FUNCTION: setSrcRect(int left, int top, int width, int height)
//
//   PURPOSE: used to manualy set the source rect.
//
void Surface::setSrcRect(int left, int top, int width, int height){
	srcRect.left = left;
	srcRect.top = top;
	srcRect.bottom = srcRect.top + height;
	srcRect.right = srcRect.left + width;
}

//
//   FUNCTION: setDestRect(int left, int top, int width, int height)
//
//   PURPOSE: used to manualy set the destination rect.
//
void Surface::setDestRect(int left, int top, int width, int height){
	destRect.left = left;
	destRect.top = top;
	destRect.bottom = destRect.top + height;
	destRect.right = destRect.left + width;
}