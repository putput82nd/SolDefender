#include<d3dx9.h>
#include<string>
#pragma comment(lib, "d3dx9.lib")
#include<map>
#include<string>
using namespace std;
#include <tchar.h>
#include"Resource.h"

struct FontInfo
{
	ID3DXFont* Font;
};

class FontClass
{
private:
	map<string, FontInfo*> fontList;
public:
	FontClass();
	~FontClass();
	void CreateFont(IDirect3DDevice9* DirectDevice, int height, 
		int width, bool italic, string fontName, LPCWSTR name);
	void Shutdown();
	void Render(string name, LPCWSTR text, RECT R, D3DCOLOR color);
};