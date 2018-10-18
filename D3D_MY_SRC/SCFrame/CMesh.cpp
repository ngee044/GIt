#include "header.h"

Mesh::Mesh(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	m_Mesh=NULL;
	m_MeshMaterial=NULL;
	m_MeshTexture=NULL;
	m_numMaterial=0;
}

Mesh::~Mesh()
{
	Cleanup();
}



HRESULT Mesh::InitMesh(LPCSTR filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	if(FAILED(D3DXLoadMeshFromX( filename, D3DXMESH_SYSTEMMEM, 
		m_pd3dDevice, NULL, 
		&pD3DXMtrlBuffer, NULL, &m_numMaterial, 
		&m_Mesh )))
		return E_FAIL;

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_MeshMaterial = new D3DMATERIAL9[m_numMaterial];
	if( m_numMaterial == NULL )
		return E_FAIL;
	m_MeshTexture  = new LPDIRECT3DTEXTURE9[m_numMaterial];
	if( m_MeshTexture == NULL )
		return E_FAIL;

	for( DWORD i=0; i<m_numMaterial; i++ )
	{

		m_MeshMaterial[i] = d3dxMaterials[i].MatD3D;
		m_MeshMaterial[i].Ambient = m_MeshMaterial[i].Diffuse;
		m_MeshTexture[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename != NULL && 
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			D3DXCreateTextureFromFile( m_pd3dDevice,d3dxMaterials[i].pTextureFilename,&m_MeshTexture[i] );
		}
	}
	pD3DXMtrlBuffer->Release();
	return S_OK;
}

void Mesh::UpdateSkinning() //��Ű�� ����Ÿ ������Ʈ
{
	sViewList* TempView = m_pViewList;
	sSkinningVertex *pSknVtSrc;
	sSkinningVertex *pSknVtDest;
	sSkinningVertex *pSknVt = NULL;
	D3DXVECTOR3 *vTemp;
	D3DXVECTOR3 vTempNoneBland;

	Mesh*  TempWeighMesh;
	D3DXMATRIX TempMat;

	int bland = 0;
	int blandx = 0;

	////////////////////////////////////////////////////////////
	// �Ž��� ��Ű������������ü�� ������Ʈ       //
	// pSknVtSrc = ��Ű������ ������ü�� ������ �ִ�.    //
	////////////////////////////////////////////////////////////

	pSknVtSrc = m_sSkinningVt; //��Ű�� ����Ÿ

	for (int i = 0; i<m_iNumPhysiqueVt; i++)
	{
		if (pSknVtSrc[i].m_bBland == false) //�޽����ؽ� �״�� ���
		{
			TempWeighMesh = pSknVtSrc[i].m_pBlandVt[0].m_pMesh;
			vTempNoneBland = pSknVtSrc[i].m_pBlandVt[0].m_vBipLocal;
			D3DXVec3TransformCoord(&vTempNoneBland, &vTempNoneBland, &TempWeighMesh->m_AniMat);
			pSknVtSrc[i].m_pVertex->x = vTempNoneBland.x;
			pSknVtSrc[i].m_pVertex->y = vTempNoneBland.y;
			pSknVtSrc[i].m_pVertex->z = vTempNoneBland.z;
		}
		else
		{
			vTemp = new D3DXVECTOR3[pSknVtSrc[i].m_NumBlend];

			for (int j = 0; j < pSknVtSrc[i].m_NumBlend; j++) //��Ű�� ������ ����ġ�� ������ ���ؽ� ����
			{
				TempWeighMesh = pSknVtSrc[i].m_pBlandVt[j].m_pMesh;
				vTemp[j] = pSknVtSrc[i].m_pBlandVt[j].m_vBipLocal;
				D3DXVec3TransformCoord(&vTemp[j], &vTemp[j], &TempWeighMesh->m_AniMat);
				vTemp[j] *= pSknVtSrc[i].m_pBlandVt[j].m_fWeight;
			}

			for (int j = 1; j < pSknVtSrc[i].m_NumBlend; j++)
			{
				vTemp[0] += vTemp[j];
			}

			pSknVtSrc[i].m_pVertex->x = vTemp[0].x;
			pSknVtSrc[i].m_pVertex->y = vTemp[0].y;
			pSknVtSrc[i].m_pVertex->z = vTemp[0].z;

			delete[] vTemp;
		}
	}

	////////////////////////////////////////////////////////////////////////
	// pSknVtDest =�ﰢ�� ���� *3 ���� �þ ��Ű����������     //
	// ������ pSknVtSrc���� �ߺ��Ǿ� �ﰢ������ *3 �̵Ǿ�����     //
	// pSknVtDest���� pSknVtSrc(����) ���� ã�Ƽ� �������ָ�     //
	// �ߺ������� ���ʿ䰡 ����.            //
	// �ɹ������� m_VtIndex�� �������־ �װ� �־��ָ��      //
	////////////////////////////////////////////////////////////////////////

	while (TempView)
	{
		pSknVtDest = TempView->m_pSknVt;

		for (int i = 0; i<TempView->m_iMaxVertex * 3; i++)//���ؽ� ����� ���� �ﰢ��
		{
			*pSknVtDest[i].m_pVertex = *pSknVtSrc[pSknVtDest[i].m_VtIndex].m_pVertex;
		}
		TempView = TempView->m_pNext;
	}
}

void Mesh::Render()
{
	for( DWORD i=0; i<m_numMaterial; i++ )
	{
		m_pd3dDevice->SetMaterial( &m_MeshMaterial[i] );
		m_pd3dDevice->SetTexture( 0, m_MeshTexture[i] );
		m_Mesh->DrawSubset( i );
	}
}

void Mesh::Cleanup()
{
	if( m_MeshMaterial != NULL ) 
		delete[] m_MeshMaterial;

	if( m_MeshTexture )
	{
		for( DWORD i = 0; i < m_numMaterial; i++ )
		{
			if( m_MeshTexture[i] )
				m_MeshTexture[i]->Release();
		}
		delete[] m_MeshTexture;
	}
	if( m_Mesh != NULL )
		m_Mesh->Release();
}

void Mesh::UpdateAniTm(char *pAniName, D3DXMATRIX matParents, float frame)
{
	D3DXMATRIX MyAni;
	D3DXMatrixIdentity(&MyAni);
	D3DXMATRIX RotMat;
	D3DXMatrixIdentity(&RotMat);
	D3DXMATRIX PosMat;
	D3DXMatrixIdentity(&PosMat);
	D3DXMATRIX ScaleMat;
	D3DXMatrixIdentity(&ScaleMat);
	D3DXVECTOR3 vPosStart;
	D3DXVECTOR3 vPosEnd;
	D3DXVECTOR3 vPos;
	D3DXQUATERNION qRot;
	D3DXQUATERNION qRotStart;
	D3DXQUATERNION qRotEnd;
	D3DXQUATERNION qAniScale;
	float DestIndex, StartIndex;
	sAnimation* pAni = m_pAniList;//&m_sAnimation;
	sPos_Track* PosTrack = NULL;//m_sAnimation.GetNowPosTrack(frame);
	sRot_Track* RotTrack = NULL;//;m_sAnimation.GetNowRotTrack(frame);
	cTmInfomation *pTmInfoList = m_pTmInfoList;
	cTmInfomation *pTmInfo = NULL;
	cTmInfomation *pParentsTminfo = NULL;
	while (pTmInfoList)
	{
		if (_stricmp(pAniName, pTmInfoList->m_AniName) == 0)
		{
			pTmInfo = pTmInfoList;
			break;
		}
		else
		{
			pTmInfoList = pTmInfoList->m_pNext;
		}
	}

	if (m_pParents)
	{
		pTmInfoList = m_pParents->m_pTmInfoList;

		while (2)
		{
			if (_stricmp(pAniName, pTmInfoList->m_AniName) == 0)
			{
				pParentsTminfo = pTmInfoList;
				break;
			}
			else
			{
				pTmInfoList = pTmInfoList->m_pNext;
			}
		}
	}

	while (pAni)
	{
		if (pAni && _stricmp(pAniName, pAni->m_AniName) == 0)
		{
			PosTrack = pAni->GetNowPosTrack(frame);
			RotTrack = pAni->GetNowRotTrack(frame);
			break;
		}
		else
		{
			if (pAni->m_pNext)
			{
				pAni = pAni->m_pNext;
			}
			else
			{
				break;
			}
		}
	}

	if (RotTrack)
	{
		qRot = RotTrack->m_qrot;
		if (RotTrack->m_pNext)
		{
			qRotStart = RotTrack->m_qrot;
			qRotEnd = RotTrack->m_pNext->m_qrot;
			DestIndex = (float)RotTrack->m_pNext->m_iIndex;
			StartIndex = (float)RotTrack->m_iIndex;
		}
		else
		{
			qRotStart = RotTrack->m_qrot;
			qRotEnd = pAni->m_Rot->m_qrot;
			StartIndex = (float)RotTrack->m_iIndex;
			DestIndex = (float)StartIndex + 800.0f;
		}

		D3DXQuaternionSlerp(&qRot, &qRotStart, &qRotEnd, (float)(frame - StartIndex) / (DestIndex - StartIndex));
		D3DXMatrixRotationQuaternion(&RotMat, &qRot);
	}
	else
	{
		if (m_pParents)
		{
			if (pTmInfo == NULL)
			{
				RotMat = m_TmMat * m_pParents->m_InvTm;
			}
			else
			{
				RotMat = pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
			}
		}
		else
		{
			if (pTmInfo == NULL)
			{
				RotMat = m_TmMat;
			}
			else
			{
				RotMat = pTmInfo->m_TmMat;
			}
		}
	}

	RotMat._41 = 0.0f;
	RotMat._42 = 0.0f;
	RotMat._43 = 0.0f;
	RotMat._44 = 1.0f;
	m_TransRotMat = RotMat; //��� ��Ʈ 

	if (PosTrack)
	{
		vPos = PosTrack->m_Pos;

		if (PosTrack->m_pNext)
		{
			vPosStart = PosTrack->m_Pos;
			vPosEnd = PosTrack->m_pNext->m_Pos;
			DestIndex = (float)PosTrack->m_pNext->m_iIndex;
			StartIndex = (float)PosTrack->m_iIndex;

			vPos.x += (vPosEnd.x - vPosStart.x) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
			vPos.y += (vPosEnd.y - vPosStart.y) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
			vPos.z += (vPosEnd.z - vPosStart.z) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
		}
		else
		{
			vPosStart = PosTrack->m_Pos;
			vPosEnd = pAni->m_Pos->m_Pos;
			StartIndex = (float)PosTrack->m_iIndex;
			DestIndex = (float)StartIndex + 800.0f;
			vPos.x += (vPosEnd.x - vPosStart.x) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
			vPos.y += (vPosEnd.y - vPosStart.y) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
			vPos.z += (vPosEnd.z - vPosStart.z) * (float)(frame - StartIndex) / (DestIndex - StartIndex);
		}
	}
	else
	{
		if (m_pParents)
		{
			if (pTmInfo == NULL)
			{
				PosMat = m_TmMat * m_pParents->m_InvTm;
			}
			else
			{
				PosMat = pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
			}
			vPos.x = PosMat._41;
			vPos.y = PosMat._42;
			vPos.z = PosMat._43;
		}
		else
		{
			if (pTmInfo == NULL)
			{
				vPos = m_TmPos;
			}
			else
			{
				vPos = pTmInfo->m_TmPos;
			}
		}
	}

	m_vTransvec = vPos;

	RotMat._41 = vPos.x;
	RotMat._42 = vPos.y;
	RotMat._43 = vPos.z;
	RotMat._44 = 1.0f;

	MyAni = RotMat;

	if (m_pParents)
	{
		int a = 0;
	}

	D3DXMatrixMultiply(&m_AniMat, &MyAni, &matParents);
	sMeshContainer* Tmp = m_pChild;

	while (Tmp)
	{
		Tmp->m_pData->UpdateAniTm(pAniName, m_AniMat, frame);
		Tmp = Tmp->m_pNext;
	}
}