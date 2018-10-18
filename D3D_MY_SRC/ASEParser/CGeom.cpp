#include "header.h"
CGeom::CGeom(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	m_VertexBuffer=NULL;
	//m_IndexBuffer=NULL;
	D3DXMatrixIdentity(&m_GeomTM);
	D3DXMatrixIdentity(&m_Current);
	m_Materialref=0;
	m_NodeName="";
	m_ParentsName="";
	m_ParentsGeom=NULL;
}
CGeom::~CGeom()
{
	
	vector<CPosTrack*>::iterator iter2;
	vector<CRotTrack*>::iterator iter3;
	
	for(iter2=m_PosTrackList.begin();iter2!=m_PosTrackList.end();iter2++)
	{
		delete *iter2;

	}
	m_PosTrackList.clear();

	for(iter3=m_RotTrackList.begin();iter3!=m_RotTrackList.end();iter3++)
	{
		delete *iter3;

	}
	m_RotTrackList.clear();

	
	SAFE_DELETE(m_Mesh);
}

void
CGeom::UpdateAni(D3DXMATRIX matParents,float anidt)
{
	D3DXMATRIX matRot,matPos,matInverseGeom,matInverseParents,matCurrentChild;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matCurrentChild);
	D3DXMatrixIdentity(&matInverseParents);
	D3DXQUATERNION qr;
	D3DXVECTOR3 Pos;
	if(GetRotTrack(anidt,&qr))
	{
		D3DXMatrixRotationQuaternion(&matRot,&qr);
	}
	else if(m_ParentsGeom)
	{
		D3DXMatrixInverse(&matInverseParents,NULL,&m_ParentsGeom->m_GeomTM);
		matRot=m_GeomTM*matInverseParents;
	}
	else
	{
		matRot=m_GeomTM;
	}
	matRot._41=0.0f;
	matRot._42=0.0f;
	matRot._43=0.0f;
	matRot._44=1.0f;

	if(GetPosTrack(anidt,&Pos))
	{


	}
	else if(m_ParentsGeom)
	{
		D3DXMatrixInverse(&matInverseParents,NULL,&m_ParentsGeom->m_GeomTM);
		matPos=m_GeomTM*matInverseParents;
		Pos.x=matPos._41;
		Pos.y=matPos._42;
		Pos.z=matPos._43;

	}
	else
	{
		matPos=m_GeomTM;
		Pos.x=matPos._41;
		Pos.y=matPos._42;
		Pos.z=matPos._43;
	}
	matRot._41=Pos.x;
	matRot._42=Pos.y;
	matRot._43=Pos.z;

	D3DXMatrixInverse(&matInverseGeom,NULL,&m_GeomTM);
	m_Current=matInverseGeom*matRot*matParents;
	matCurrentChild=matRot*matParents;

	vector<CGeom*>::iterator iter;
	for(iter=m_ChildList.begin();iter!=m_ChildList.end();iter++)
	{
		(*iter)->UpdateAni(matCurrentChild,anidt);
	}


}
HRESULT 
CGeom::MakeVertexBuffer()
{
	CUSTOMVERTEX* temp;

	void* pVertice;
	if(FAILED(m_pd3dDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX)*(m_Mesh->m_NumIndex*3),0
		,D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT ,&m_VertexBuffer,NULL)))
		return E_FAIL;

	temp=new CUSTOMVERTEX[m_Mesh->m_NumIndex*3];

	for(int i=0;i<m_Mesh->m_NumIndex*3;i=i+3)
	{
		temp[i].point=m_Mesh->m_VertexList[m_Mesh->m_IndexList[i/3]._0];
		temp[i].normal=m_Mesh->m_NormalList[i/3]->m_VertexNormal[0];
		temp[i].color=0x00ffffff;

		if(Type==MESH)
		{
			temp[i].tu=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._0].x;
			temp[i].tv=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._0].y;
		}
		else
		{
			temp[i].tu=0.0f;
			temp[i].tv=0.0f;
		}

		temp[i+1].point=m_Mesh->m_VertexList[m_Mesh->m_IndexList[i/3]._1];
		temp[i].normal=m_Mesh->m_NormalList[i/3]->m_VertexNormal[1];
		temp[i+1].color=0x00ffffff;

		if(Type==MESH)
		{
			temp[i+1].tu=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._1].x;
			temp[i+1].tv=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._1].y;
		}
		else
		{
			temp[i+1].tu=0.0f;
			temp[i+1].tv=0.0f;
		}

		temp[i+2].point=m_Mesh->m_VertexList[m_Mesh->m_IndexList[i/3]._2];
		temp[i].normal=m_Mesh->m_NormalList[i/3]->m_VertexNormal[2];
		temp[i+2].color=0x00ffffff;

		if(Type==MESH)
		{
			temp[i+2].tu=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._2].x;
			temp[i+2].tv=m_Mesh->m_TextureVertexList[m_Mesh->m_TextureFaceList[i/3]._2].y;
		}
		else
		{
			temp[i+2].tu=0.0f;
			temp[i+2].tv=0.0f;
		}

	}

	m_VertexBuffer->Lock(0,sizeof(CUSTOMVERTEX)*(m_Mesh->m_NumIndex*3),(void**)&pVertice,0);
	memcpy(pVertice,temp,sizeof(CUSTOMVERTEX)*(m_Mesh->m_NumIndex*3));
	m_VertexBuffer->Unlock();
	delete [] temp;

	return S_OK;
}

void CGeom::Render()
{
		m_pd3dDevice->SetTransform(D3DTS_WORLD,&m_Current);
		m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		m_pd3dDevice->SetStreamSource(0,m_VertexBuffer,0,sizeof(CUSTOMVERTEX));
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,m_Mesh->m_NumIndex);
}