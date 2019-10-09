#pragma once
#include "fmod.h"
#include "assert.h"
#include "fmod_errors.h"
#pragma comment(lib, "fmodex_vc.lib")
#include<Windows.h>
#include <map>
using namespace std;





class AudioClass
{
private:
	FMOD_SYSTEM*		AudSystem;
	FMOD_RESULT			AudResult;
	unsigned int		version;
	int					numDrivers;
	FMOD_SPEAKERMODE	SpeakerMode;
	FMOD_CAPS			AudCap;
	char				name[256];
	FMOD_CHANNEL*		Channel;
	map<char*, FMOD_SOUND*>  soundList;	
	HWND hWnd;
	#define ERRCHECK(x) if(x != FMOD_OK) {MessageBox(hWnd, (LPCWSTR)x, L"Fmod Error", MB_OK);}
public:
	AudioClass();
	~AudioClass();
	void InitAudio(HWND hWnd);
	void LoadSound(char* filename);
	void DeleteSound(char* fileName);
	void PlaySound(char* fileName);
	void Shutdown();
};