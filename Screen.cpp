#include"Screen.h"



ScreenClass::ScreenClass()
{
	gameWindowed = false;
}

ScreenClass::~ScreenClass()
{}


LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wparam, LPARAM lparam);

void ScreenClass::InitWindow(HINSTANCE hInstance)
{
	gameInstance = hInstance;

	WNDCLASSEX wndClass;  
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbSize			= sizeof(WNDCLASSEX);			// size of window structure
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;				// message callback
	wndClass.lpszClassName	= WINDOW_TITLE;					// class name -> a required field here, can't put NULL
	wndClass.hInstance		= gameInstance;					// handle to the application
	wndClass.hCursor		= LoadCursor(NULL, IDC_CROSS);	// changed t a CROSS pointer
	wndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOWFRAME);	// background brush

	RegisterClassEx(&wndClass);

	gameWnd = CreateWindow(
		WINDOW_TITLE, WINDOW_TITLE,
		gameWindowed ? WS_OVERLAPPEDWINDOW | WS_VISIBLE:(WS_POPUP | WS_VISIBLE),
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL, NULL,
		gameInstance,
		NULL);

	ShowWindow(gameWnd, SW_SHOW);
	UpdateWindow(gameWnd);
}

void ScreenClass::Shutdown()
{
	UnregisterClass(WINDOW_TITLE, gameInstance);
}

HWND ScreenClass::ReturnGameWnd()
{
	return gameWnd;
}
	
HINSTANCE ScreenClass::ReturnGameInstance()
{
	return gameInstance;
}
	
bool ScreenClass::ReturnGameWindowed()
{
	return gameWindowed;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
		case (WM_PAINT):
		{
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		}		
		case(WM_DESTROY):
		{
			PostQuitMessage(0); 
			break;
		}
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}