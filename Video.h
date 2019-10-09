#include<dshow.h>
#pragma comment(lib, "strmiids.lib")
#include<string>
#include"Resource.h"



class VideoClass
{
private:
	IGraphBuilder*		GraphBuilder;
	IMediaControl*		Control;
	IMediaEvent*		Media;
	IVideoWindow*		VideoWindow;
	bool				videoPlay;
public:
	VideoClass();
	~VideoClass();
	void InitVideo();
	void PlayVideo(HWND hWnd, LPCWSTR videoFile);
	void EndVideo();
	bool ReturnVideoPlay();
	void VideoCompleted(HWND handle2Wnd);
	void StopVideo(HWND handle2Wnd);
};