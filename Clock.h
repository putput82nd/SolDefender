#pragma once
#include <stdio.h>
#include <time.h>
#include <stack>

const int FPS_FRAME_BUFFER = 10;

class Clock 
{
private:
	int elapsedTime;
	int elapsedLast;
	int frameLast;
	int frameTime;
	int renderStart;
	int updateStart;
	int frames[FPS_FRAME_BUFFER];

	// stats
	float elapsed;
	float fps;
	float renderTime;
	float updateTime;

public:
	Clock(void);
	~Clock(void);

	void UpdateElapsed(void);
	void UpdateFPS(void);
	void StartUpdate(void);
	void EndUpdate(void);
	void StartRender(void);
	void EndRender(void);

	// GETTERS
	float Elapsed();
	float Fps();
	float RenderTime();
	float UpdateTime();
};
