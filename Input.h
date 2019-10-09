#ifndef Input_h
#define Input_h

#include<dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include"Resource.h"

class InputClass
{
private:
	IDirectInput8*			DIObject;
	IDirectInputDevice8*	DIKeyboard;
	IDirectInputDevice8*	DIMouse;
	byte					KeyboardState[256];
	byte					KeyPressedState[256];
	DIMOUSESTATE2			MouseState;
public:
	InputClass();
	~InputClass();
	void InitInput(HWND hWnd, HINSTANCE hInstance);
	void Poll();
	bool KeyDown(char key);
	bool KeyUp(char key);
	bool KeyPress(char key);
	bool MouseButtonDown(int button);
	float MouseDX();
	float MouseDY();
	float MouseDZ();
	void Shutdown();
};
#endif