#include"Font.h"



FontClass::FontClass()
{

}
	
FontClass::~FontClass()
{
	Shutdown();
}
	
void FontClass::CreateFont(IDirect3DDevice9* DirectDevice, int height, int width, 
	bool italic, string fontName, LPCWSTR name)
{
	FontInfo* font;
	font = new FontInfo;
	D3DXCreateFontW(DirectDevice, height, width, 0, 0, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name, &font->Font);
	fontList[fontName] = font;
}

void FontClass::Shutdown()
{
	fontList.empty();
}

void FontClass::Render(string name, LPCWSTR text, RECT R, D3DCOLOR color)
{
	fontList[name]->Font->DrawText(0, text, -1, &R, DT_NOCLIP, color);
}