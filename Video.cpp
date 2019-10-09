#include"Video.h"

VideoClass::VideoClass()
{
	videoPlay = false;
}
	
VideoClass::~VideoClass()
{
	SAFE_RELEASE(Control);
	SAFE_RELEASE(VideoWindow);
	SAFE_RELEASE(GraphBuilder);
}
	
void VideoClass::InitVideo()
{
	CoInitialize(NULL);
	CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&GraphBuilder);
}

void VideoClass::PlayVideo(HWND hWnd, LPCWSTR videoFile)
{
	videoPlay = true;
	GraphBuilder->QueryInterface(IID_IMediaControl, (void**)&Control);
	GraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&Media);
	GraphBuilder->RenderFile(videoFile, NULL);
	Control->QueryInterface( IID_IVideoWindow, (void**)&VideoWindow);
	VideoWindow->put_Owner((OAHWND)hWnd);
	VideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);

	RECT WinRect;
	GetClientRect(hWnd, &WinRect);

	VideoWindow->SetWindowPosition(WinRect.left, WinRect.top, WinRect.right, WinRect.bottom);
	Control->Run();
}

void VideoClass::EndVideo()
{
	SAFE_RELEASE(Control);
	SAFE_RELEASE(VideoWindow);
	SAFE_RELEASE(GraphBuilder);
	videoPlay = false;
}

bool VideoClass::ReturnVideoPlay()
{
	return videoPlay;
}

void VideoClass::VideoCompleted(HWND handle2Wnd)
{
	long evCode, param1, param2;

	if(SUCCEEDED(Media->GetEvent(&evCode, &param1, &param2, 0)))
	{
		Media->FreeEventParams(evCode, param1, param2);

		// If video is complete (EC_COMPLETE)
		if(evCode == EC_COMPLETE)
		{
			StopVideo(handle2Wnd);
		}
	}
}

void VideoClass::StopVideo(HWND handle2Wnd)
{
	// Act on complete call here. (Continue with next game state, etc)
	Control->Stop();
	videoPlay = false;

	VideoWindow->put_Visible(OAFALSE);
	VideoWindow->put_Owner((OAHWND)handle2Wnd);

	// Clean up DirectShow variables now that it is completed.
	SAFE_RELEASE(Control);
	SAFE_RELEASE(VideoWindow);
	SAFE_RELEASE(GraphBuilder);
}