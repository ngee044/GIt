/*������ ����Ŭ�����̴�~�� �� �����ϰ� ���� ���~�Ф�
  ���� ������ ������ ��� ����ϰ� �ٽ� ������ �ڴ�~
  ��ü���� ������ �����Ѵ�*/
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

	//����� �����Լ�
	
	void FPS();

};