#ifndef WINAPP_H_
#define WINAPP_H_

#include <Windows.h>
#include <tchar.h>
//#include <memory>

//LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);

class CWindowFrame
{
protected:
	DWORD			m_uiWidth;
	DWORD			m_uiHeight;
	HINSTANCE		m_hInst;
	HWND				m_hWnd;

protected:
	static CWindowFrame*	m_pkThis;
	//static std::auto_ptr<CWindowFrame*>	m_pkThis;
	//'m_'���~
	//'_p'~������
	//'k'����üorŬ����
	CWindowFrame();

public:
	~CWindowFrame(){}
	static CWindowFrame* Create(HINSTANCE,UINT uiWidth = 800,UINT uiHeight = 600);
	static void Destroy();
	static CWindowFrame* Get();

	void Run(MSG* pMsg);
	HWND GethWnd()
	{
		if(m_pkThis != NULL)
			return m_hWnd;
		else
		{
			MessageBox(NULL,TEXT("�ڵ����"),NULL,MB_OK);
			return NULL;
		}
	}
	//static HWND GethWnd(){return m_pkThis->m_hWnd;}

protected:
	void Init(HINSTANCE,UINT,UINT);
	void RegisterWindow(HINSTANCE);

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);

};


#endif