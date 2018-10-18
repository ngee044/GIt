
class Camera{
	float m_Rotx,m_Roty;
	D3DXVECTOR3 m_vMove;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_CameraPosit;
	D3DXMATRIX m_matBill;
	D3DXMATRIX m_matBulletBill;
public:
	D3DXVECTOR3 m_vFront,m_vRight;
	Camera(LPDIRECT3DDEVICE9 pdev);
	~Camera(){;}

	void Rotx(float fd){m_Rotx+=fd;Update();}
	void Roty(float fd){m_Roty+=fd;Update();}
	void Movez(float fd){ m_vMove+=fd*m_vFront;Update();}
	void Movex(float fd){ m_vMove+=fd*m_vRight;Update();}
	void Update();
	D3DXMATRIX GetBulletBill();
	D3DXMATRIX GetBill();
	D3DXVECTOR3 GetCameraPosit();
	void SetCameraPosit(D3DXVECTOR3 newPosit);
	D3DXMATRIX* Getview(){return &m_matView;}

};
