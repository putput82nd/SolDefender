#include"Input.h"


InputClass::InputClass()
{
	DIKeyboard		= 0;
	DIMouse			= 0;
}

InputClass::~InputClass()
{
	Shutdown();
}

void InputClass::InitInput(HWND hWnd, HINSTANCE hInstance)
{
	ZeroMemory(KeyboardState, sizeof(KeyboardState));
	ZeroMemory(&MouseState, sizeof(MouseState));

	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&DIObject, 0);

	DIObject->CreateDevice(GUID_SysKeyboard, &DIKeyboard, 0);
	DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DIKeyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	DIKeyboard->Acquire();

	DIObject->CreateDevice(GUID_SysMouse, &DIMouse, 0);
	DIMouse->SetDataFormat(&c_dfDIMouse2);
	DIMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	DIMouse->Acquire();
}
	
void InputClass::Poll()
{
	// Poll keyboard.

	HRESULT hr = DIKeyboard->GetDeviceState(sizeof(KeyboardState), (void**)&KeyboardState); 
	if( FAILED(hr) )
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(KeyboardState, sizeof(KeyboardState));

		 // Try to acquire for next time we poll.
		hr = DIKeyboard->Acquire();
	}

	// Poll mouse.
	hr = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&MouseState); 
	if( FAILED(hr) )
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&MouseState, sizeof(MouseState));

		// Try to acquire for next time we poll.
		hr = DIMouse->Acquire(); 
	}
}

bool InputClass::KeyDown(char key)
{
	return (KeyboardState[key] & 0x80) != 0;
}
bool InputClass::KeyUp(char key)
{
	//check the state of the key
	if (KeyboardState[key] & 0x80)
	{
		return false;
	} 
	else 
	{
		return true;
	}
}

bool InputClass::KeyPress(char key)
{

	//check for keydown
	if (KeyDown(key)){
		KeyPressedState[key] = 1;
	}
	//check for key reaching the keydown state
	if (KeyPressedState[key] == 1){
		//check for key release
		if (KeyUp(key))
			KeyPressedState[key] = 2;
	}

	//check if key has been pressed and released
	if (KeyPressedState[key] == 2){
		//reset the key status
		KeyPressedState[key] = 0;
		return true;
	}
	
	return false;
}

bool InputClass::MouseButtonDown(int button)
{
	return (MouseState.rgbButtons[button] & 0x80) != 0;
}

float InputClass::MouseDX()
{
	return (float)MouseState.lX;
}

float InputClass::MouseDY()
{
	return (float)MouseState.lY;
}

float InputClass::MouseDZ()
{
	return (float)MouseState.lZ;
}
	
void InputClass::Shutdown()
{
	DIMouse->Unacquire();
	SAFE_RELEASE(DIMouse);
	DIKeyboard->Unacquire();
	SAFE_RELEASE(DIKeyboard);
}