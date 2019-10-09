#include<Windows.h>



class ScreenClass
{
private:
	HWND		gameWnd;
	HINSTANCE	gameInstance;
	#define		WINDOW_TITLE L"Star Fighter"
	bool		gameWindowed;
public:
	ScreenClass();
	~ScreenClass();
	void InitWindow(HINSTANCE hInsance);
	void Shutdown();
	HWND ReturnGameWnd();
	HINSTANCE ReturnGameInstance();
	bool ReturnGameWindowed();
};