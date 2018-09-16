#include "header.h"

Camera ::Camera(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	m_Rotx=0.0f;
	m_Roty=0.0f;
	m_vMove=D3DXVECTOR3(0.0f,0.0f,-10.0f);
	m_vFront=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_vRight=D3DXVECTOR3(1.0f,0.0f,0.0f);
	
	

}
void
Camera::SetCameraPosit(D3DXVECTOR3 newPosit)
{	
	m_vMove=newPosit;

}
D3DXMATRIX
Camera::GetBulletBill()
{
	D3DXMatrixIdentity(&m_matBulletBill);
	D3DXMatrixInverse(&m_matBulletBill,NULL,&m_matView);
	m_matBulletBill._41=0.0f;
	m_matBulletBill._42=0.0f;
	m_matBulletBill._43=0.0f;
	return m_matBulletBill;


}
D3DXMATRIX
Camera::GetBill()
{
	D3DXMatrixIdentity(&m_matBill);
	m_matBill._11=m_matView._11;
	m_matBill._13=m_matView._13;
	m_matBill._31=m_matView._31;
	m_matBill._33=m_matView._33;
	D3DXMatrixInverse(&m_matBill,NULL,&m_matBill);
	return m_matBill;

}
D3DXVECTOR3 
Camera::GetCameraPosit()
{
	return m_vMove;
}
void Camera::Update()
{
	D3DXMATRIX matRoyx,matRoty;
	D3DXMATRIX matWorld;
	
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matRoyx,m_Rotx);
	D3DXMatrixRotationY(&matRoty,m_Roty);
	matWorld=matRoyx*matRoty;
	
	matWorld._41 =m_vMove.x;
	matWorld._42 =m_vMove.y;
	matWorld._43 =m_vMove.z;
	
	D3DXMatrixInverse(&m_matView,NULL,&matWorld);
	//m_matView._42-=30.0f;
	//m_matView._43+=30.0f;
	m_vFront.x=matWorld._31;
	m_vFront.y=matWorld._32;
	m_vFront.z=matWorld._33;
	m_vRight.x=matWorld._11;
	m_vRight.y=matWorld._12;
	m_vRight.z=matWorld._13;
	m_pd3dDevice->SetTransform(D3DTS_VIEW,&m_matView);
	
}
