#include"DX.h"



DXClass::DXClass()
{
	DirectObject	= 0;
	DirectDevice	= 0;
	vSync			= false;
}

DXClass::~DXClass()
{}

void DXClass::InitDX(HWND hWnd, bool windowed)
{
	DirectObject = Direct3DCreate9(D3D_SDK_VERSION);

	//ScreenMode
	for(int i = 0; i < DirectObject->GetAdapterCount(); i++)
	{
		UINT modeCnt = DirectObject->GetAdapterModeCount(i, D3DFMT_X8R8G8B8);
		for(int j = 0; j < modeCnt; j++)
		{
			DirectObject->EnumAdapterModes(i, D3DFMT_X8R8G8B8, j, &mode);
		}
	}

	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));												// NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= windowed;									// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= mode.Height;
	D3Dpp.BackBufferWidth				= mode.Width;
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= vSync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= mode.RefreshRate;
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

	//DeviceCap
	DWORD deviceBehaviorFlags = 0;
	DirectObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap);

	if(DeviceCap.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}
	
	if(DeviceCap.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}

	DirectObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&DirectDevice);			// returned device pointer
}

void DXClass::StartRender(HWND hWnd)
{
	if(!DirectDevice)
		return;
	if(SUCCEEDED(DirectDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)));
	{
		if(SUCCEEDED(DirectDevice->BeginScene()));
		{
			RECT rect;
			GetWindowRect(hWnd, &rect);
			//infor here
		}	
	}
}

void DXClass::EndRender()
{
	DirectDevice->EndScene();
	DirectDevice->Present(0, 0, 0, 0);
}

void DXClass::Shutdown()
{
	SAFE_RELEASE(DirectDevice);
	SAFE_RELEASE(DirectObject);
}

IDirect3DDevice9* DXClass::ReturnDirectDevice()
{
	return DirectDevice;
}