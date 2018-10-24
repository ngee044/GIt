#include "MainFrame.h"
#include "../DirectShow.h"

CMainFrame* CMainFrame::m_pkThis = NULL;
CMainFrame::CMainFrame()
{
	ZeroMemory(&msg,sizeof(msg));
	m_pDxshow = nullptr;
}
CMainFrame::~CMainFrame()
{
	if(m_pDxshow) delete m_pDxshow;
}
//생성
CMainFrame* CMainFrame::Create(HINSTANCE hInstance)
{
	if(!m_pkThis)
		m_pkThis = new CMainFrame;
	//윈도우 생성
	CWindowFrame::Create(hInstance);
	//d3d 생성
	CD3DFrame::Get()->Create();

	return	m_pkThis;
}
//생성의 역순으로 삭제
void CMainFrame::Destroy()
{
	//d3d 삭제
	CD3DFrame::Destroy();
	//윈도우 삭제
	CWindowFrame::Destroy();
	//포인트로 자기자신의 주소를 넘겨준 후 삭제
	CMainFrame* pFrame = CMainFrame::Get();

	delete pFrame;
}
//메인프레임주소리턴
CMainFrame* CMainFrame::Get()
{
	return m_pkThis;
}
//메세지전달함수
int CMainFrame::Run()
{
	while(1)
	{
		 // 메시지가 있다면 처리한다.
        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            // WM_QUIT 메시지 발생시, 루프를 벗어난다.
            if( msg.message == WM_QUIT)
                break;

            // 메시지 처리.
            TranslateMessage(&msg); // 메시지 번역.
            DispatchMessage(&msg);  // 번역된 메시지 전달.
        }
		else
		{
			CD3DFrame::Get()->Run();
		}
	}
	return (int)msg.wParam;
}

void CMainFrame::CreateDxShow()
{
	m_pDxshow = new DirectShow();

	m_pDxshow->initDxShow();
}

void CMainFrame::FModSoundInit()
{
#if 0
	FMOD_SYSTEM *pSystem;
	FMOD_CHANNEL *channel;
	FMOD_MODE fmodmode;
	FMOD_CHANNELINDEX channelIndex;
	FMOD_INITFLAGS fmodflasg;
	FMOD_BOOL is_fmodbool;
	FMOD_SOUND *sound;

	FMOD_System_Create(&pSystem);
	FMOD_System_Init(pSystem, 32, fmodflasg, NULL);
	FMOD_System_CreateSound(pSystem, "Data//Se//sword_hit.wav", fmodmode, 0, &sound);
	FMOD_System_Init(FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
	FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
	FMOD_Channel_GetVolume(FMOD_CHANNEL *channel, float *volume);
	FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
	FMOD_Channel_Stop(FMOD_CHANNEL *channel);
	FMOD_Channel_SetPaused(FMOD_CHANNEL *channel, FMOD_BOOL paused);
	FMOD_Channel_SetMute(FMOD_CHANNEL *channel, FMOD_BOOL mute);
#endif
}
