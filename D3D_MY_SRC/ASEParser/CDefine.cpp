#include "header.h"
CMaterial::CMaterial(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	ZeroMemory(&m_Material,sizeof(D3DMATERIAL9));
	ZeroMemory(&m_Texture,sizeof(LPDIRECT3DTEXTURE9));
	ZeroMemory(&m_Ambient,sizeof(D3DXVECTOR3));
	ZeroMemory(&m_Diffuse,sizeof(D3DXVECTOR3));
	ZeroMemory(&m_Specular,sizeof(D3DXVECTOR3));

}
CMaterial::~CMaterial()
{
	SAFE_RELEASE(m_Texture);
}

HRESULT CMaterial::CreateTexture()
{
	LPCSTR temp = m_TextureName.c_str(); 

	if(FAILED(D3DXCreateTextureFromFile(m_pd3dDevice,temp,&m_Texture)))
		return E_FAIL;	
	return S_OK;
}
void CMaterial::SetTexture()
{
	m_pd3dDevice->SetTexture(0,m_Texture);
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
}

void CMaterial::SetMaterial()
{
	m_Material.Diffuse.r =m_Diffuse.x;
	m_Material.Diffuse.g =m_Diffuse.y;
	m_Material.Diffuse.b =m_Diffuse.z;
	m_Material.Diffuse.a =1.0f;
	m_Material.Ambient.r =m_Ambient.x; 
	m_Material.Ambient.g =m_Ambient.y; 
	m_Material.Ambient.b =m_Ambient.z; 
	m_Material.Ambient.a =1.0f;
	m_Material.Specular.r=m_Specular.x;
	m_Material.Specular.g=m_Specular.y;
	m_Material.Specular.b=m_Specular.z;
	m_Material.Specular.a=1.0f;
	m_pd3dDevice->SetMaterial( &m_Material );
}

CAniTime::CAniTime()
{
	m_StartTime=0.0f;
	m_EndTime=0.0f;
	m_CurrentTime=0.0f;
}

void CAniTime::Init(float firstframe,float endframe,float tickperframe)
{

	m_StartTime=firstframe*tickperframe;
	m_EndTime=endframe*tickperframe;
	m_CurrentTime=m_StartTime;


}

void CAniTime::Update(float dt)
{
	m_CurrentTime+=dt;
	if(m_CurrentTime>=m_EndTime)
		m_CurrentTime=m_StartTime;
}

void CharacterClass::Render() //메쉬 데이타 랜더링
{
	::D3DXMATRIX Rot;
	D3DXMatrixRotationX(&Rot, 3.14f / 8.0f);
	Mesh *TempMesh = m_pAse->m_pMeshList;

	while (TempMesh)
	{
		Rot = m_Rot * Rot;
		m_pAse->RenderAse(m_Scale, m_Rot, m_Pos, TempMesh); //ase 파일 랜더링
		TempMesh = TempMesh->m_pNext;
	}
}

void CharacterClass::UpdateTransitionAni()
{
	m_TransitionFrame += 0.001f * (float)(INTERPOLATION_SPEED * 2); //수정가능한 프레임 값

	if (m_TransitionFrame >= (float)MAXIMUM_INTERPOLATION_FRAME)
	{
		m_TransitionFrame = 0.0f;
		m_bTransitionAni = false;
		return;
	}

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat); //정규화

	Mesh* TempMesh = m_pAse->m_pBoneList; //ase 본 리스트

	while (TempMesh)
	{
		if (TempMesh->m_bParents == false)
		{
			TempMesh->UpdateTransitionAniTm(m_NowAnimationName, mat, m_TransitionFrame); //애니 행렬
		}
		TempMesh = TempMesh->m_pNext;
	}

	TempMesh = m_pAse->m_pMeshList;//ase  매쉬 리스트

	while (TempMesh)
	{
		if (TempMesh->m_pParents)
		{
			TempMesh->UpdateTransitionAniTm(m_NowAnimationName, mat, m_TransitionFrame);
		}
		else
		{
			if (TempMesh->m_sSkinningVt)
			{
				TempMesh->UpdateSkinning();
			}
			else
			{
				TempMesh->UpdateTransitionAniTm(m_NowAnimationName, mat, m_TransitionFrame);
			}
		}
		TempMesh = TempMesh->m_pNext;
	}
}

void CharacterClass::Update()
{
	UpdateState(); //애니메이션 상태

	if (m_bTransitionAni)
	{
		UpdateTransitionAni(); //보간이 필요한 애니메이션
	}
	else
	{
		UpdateAnimation(); //일반 애니메이션
	}

	if (m_bTransRot)
	{
		TransRot(); //최종 행렬
	}
}