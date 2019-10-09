#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include"Resource.h"



class DXClass
{
private:
	IDirect3D9*			DirectObject;
	IDirect3DDevice9*	DirectDevice;
	D3DCAPS9			DeviceCap;
	D3DDISPLAYMODE		mode;
	bool				vSync;
public:
	DXClass();
	~DXClass();
	void InitDX(HWND hWnd, bool windowed);
	void StartRender(HWND hWnd);
	void EndRender();
	void Shutdown();
	IDirect3DDevice9* ReturnDirectDevice();
};