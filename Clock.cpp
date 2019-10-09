#include "Clock.h"

Clock::Clock()
{
	elapsedTime = 0;
	elapsedLast = 0;
	frameLast = 0;
	frameTime = 0;
	renderStart = 0;
	updateStart = 0;

	elapsed = 0;
	fps = 0;
	renderTime = 0;
	updateTime = 0;

	for (int i = 0; i < FPS_FRAME_BUFFER; i++)
	{
		frames[i] = 0;
	}
}

Clock::~Clock()
{
}

void Clock::UpdateElapsed(void)
{
	elapsedTime = clock();
	elapsed = (elapsedTime - elapsedLast) / float(CLOCKS_PER_SEC);
	elapsedLast = elapsedTime;
}

void Clock::UpdateFPS(void)
{
	// get current time
	frameTime = clock();

	// move all indexes back 1 index
	for (int i = FPS_FRAME_BUFFER-2; i > -1; i--)
	{
		frames[i+1] = frames[i];
	}
	// add current 
	frames[0] = frameTime - frameLast;
	
	// get average fps
	float sum = 0.0;
	for (int i = 0; i < FPS_FRAME_BUFFER; i++)
	{
		sum += frames[i];
	}
	fps = sum / FPS_FRAME_BUFFER;

	frameLast = frameTime;
}

void Clock::StartUpdate(void)
{
	updateStart = clock();
}

void Clock::EndUpdate(void)
{
	updateTime = float(clock() - updateStart) / CLOCKS_PER_SEC;
}

void Clock::StartRender(void)
{
	renderStart = clock();
}

void Clock::EndRender(void)
{
	renderTime = float(clock() - renderStart) / CLOCKS_PER_SEC;
}

float Clock::Elapsed() { return elapsed; }
float Clock::Fps() { return fps; }
float Clock::RenderTime() { return renderTime; }
float Clock::UpdateTime() { return updateTime; }