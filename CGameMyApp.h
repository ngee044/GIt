/*게임의 메인클래스이다~ㅇ ㅏ 허접하게 무지 길다~ㅠㅠ
  빨리 디자인 패턴을 배워 깔끔하게 다시 만들어야 겠다~
  전체적인 게임을 제어한다*/
class CAniTime;

class CGameMyApp :public CGameApp{
	Camera* m_Camera;
	Font* m_Fps;
	TCHAR m_FpsChar[128];
	CASE* m_Ase;
	CASE* m_AseMap;
	CAniTime *m_Ani;
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

public:
	CGameMyApp();
	~CGameMyApp(){}
	bool m_bStop;
	virtual HRESULT Init();
	virtual HRESULT Update();
	virtual HRESULT Render();
	virtual HRESULT Cleanup();
	virtual HRESULT InitMatrix();

	//사용자 지정함수
	
	void FPS();

};