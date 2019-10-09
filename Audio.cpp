#include"Audio.h"



AudioClass::AudioClass()
{
	AudSystem = 0;
}

AudioClass::~AudioClass()
{

}

void AudioClass::InitAudio(HWND hWnd)
{
	
	AudResult = FMOD_System_Create(&AudSystem);
	ERRCHECK(AudResult);
	
	AudResult = FMOD_System_GetVersion(AudSystem, &version);
	ERRCHECK(AudResult);

	if(version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
	}

	AudResult = FMOD_System_GetNumDrivers(AudSystem, &numDrivers);
	ERRCHECK(AudResult);

	if(numDrivers == 0)
	{
		AudResult = FMOD_System_SetOutput(AudSystem, FMOD_OUTPUTTYPE_NOSOUND);
		ERRCHECK(AudResult);
	}
	else
	{
		AudResult = FMOD_System_GetDriverCaps(AudSystem, 0, &AudCap, 0, &SpeakerMode);
		ERRCHECK(AudResult);

		AudResult = FMOD_System_SetSpeakerMode(AudSystem, SpeakerMode);
		ERRCHECK(AudResult);

		if (AudCap & FMOD_CAPS_HARDWARE_EMULATED)             // The user has the 'Acceleration' slider set to off!  This is really bad for latency!. //
		{                                                   // You might want to warn the user about this. //
			AudResult = FMOD_System_SetDSPBufferSize(AudSystem, 1024, 10);
			ERRCHECK(AudResult);
		}
		
		AudResult = FMOD_System_GetDriverInfo(AudSystem, 0, name, 256, 0);
		ERRCHECK(AudResult);

		if (strstr(name, "SigmaTel"))   // Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. //
		{
			AudResult = FMOD_System_SetSoftwareFormat(AudSystem, 48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 2, FMOD_DSP_RESAMPLER_LINEAR);
			ERRCHECK(AudResult);
		}
	}

	//uses 100 virtual voices for initialization
	AudResult = FMOD_System_Init(AudSystem, 100, FMOD_INIT_NORMAL, 0);
	if (AudResult == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		AudResult = FMOD_System_SetSpeakerMode(AudSystem, FMOD_SPEAKERMODE_STEREO); 
		ERRCHECK(AudResult);

		AudResult = FMOD_System_Init(AudSystem, 100, FMOD_INIT_NORMAL, 0);
		ERRCHECK(AudResult);
	}
}

void AudioClass::LoadSound(char* fileName)
{
	FMOD_SOUND* Sound;
	AudResult = FMOD_System_CreateSound(AudSystem, fileName, FMOD_SOFTWARE, 0, &Sound);
	ERRCHECK(AudResult);
	soundList[fileName] = Sound;
}

void AudioClass::DeleteSound(char* fileName)
{
	soundList.erase(fileName);
}

void AudioClass::PlaySound(char* fileName)
{
	FMOD_SOUND* Sound;
	Sound = soundList[fileName];
	AudResult = FMOD_System_PlaySound(AudSystem, FMOD_CHANNEL_FREE, Sound, false, 0);
	ERRCHECK(AudResult);
}

void AudioClass::Shutdown()
{
	FMOD_System_Release(AudSystem);
}