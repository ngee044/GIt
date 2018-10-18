//////////////////////////////////////////////////////////////////////
//ASE 포멧의 3D모델링 파일을 D3D9 환경으로 불러오기위한 코드입니다.///
//////////////////////////////////////////////////////////////////////

#include "ASE.h"
#include <crtdbg.h>
#include "CharacterClass.h"


void STriangle::Init()
{
	for(int i=0; i<3; i++)
	{
		VertexColor[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_vVtNomal[i] = D3DXVECTOR3(0,0,0);
		m_vFaceNomal = D3DXVECTOR3(0,0,0);
		m_sTverlist[i].tu=0;
		m_sTverlist[i].tv=0;
	}
	m_sFaceIndex.m_0 = 0;
	m_sFaceIndex.m_1 = 0;
	m_sFaceIndex.m_2 = 0;

	m_iMeterialID = 0;	
	m_bDraw = true;
}

void cMesh::MakeIndex(SMeterial* pMeterial)
{
	if(m_sTvertlist)delete[] m_sTvertlist;

	m_sTvertlist=NULL;

	if(m_ColorList)delete[] m_ColorList;

	m_ColorList=NULL;

	int* Num;

	sViewList* VTemp;
	sViewList* OpacityTemp=NULL;

	if(m_pViewList)delete[] m_pViewList;
	m_pViewList=NULL;

	if(pMeterial[m_iMeterial_Ref].m_iSubMeterialCount>0)	//if(1)
	{
		Num =new int[pMeterial[m_iMeterial_Ref].m_iSubMeterialCount];

		for(int i=0;i<m_iNumFace;i++)
		{
			if(m_sTriangle[i].m_iMeterialID==i && m_sTriangle[i].m_bDraw==true)
			{
				Num[i]++;
			}
		}
		int TriangleNum=0;
		for(int i=0;i<pMeterial[m_iMeterial_Ref].m_iSubMeterialCount;i++)
		{
			if(Num[i]<=0)
				continue;

			VTemp->m_iNumVertex=Num[i]*3;
			VTemp->m_iMaxVertex=Num[i]*3;		
			VTemp->m_pVertex=new SVertex[VTemp->m_iMaxVertex];
			if(m_sSkinningVt)
			{
				VTemp->m_pSknVt=new sSkinningVertex[VTemp->m_iMaxVertex * 3];
			}
			VTemp->m_pIndex=new int[Num[i]];
			VTemp->m_pMeterial=&pMeterial[m_iMeterial_Ref].m_SubMeterial[i];
		
			for(int j=0;j<m_iNumFace;j++)
			{
				if(m_sTriangle[j].m_iMeterialID==i && m_sTriangle[j].m_bDraw==true)
				{
					VTemp->m_pIndex[TriangleNum]=j;
					TriangleNum++;
				}
			}

			if(pMeterial[m_iMeterial_Ref].bUseOpacity==true)
			{
				if(OpacityTemp)
				{
					OpacityTemp->Add(VTemp);
				}
				else
				{
					m_pViewList=VTemp;
				}
			}

			if(OpacityTemp)
			{
				if(m_pViewList)
				{
					m_pViewList->Add(OpacityTemp);
				}
				else
				{
					m_pViewList=OpacityTemp;
				}
			}


		}

		delete[] Num;

	}	//if(1) 현재매쉬의메트리얼에 서브메트리얼이있다면 //끝
	else
	{
			m_pViewList=new sViewList;
			m_pViewList->m_iNumVertex=m_iNumFace;
			m_pViewList->m_iMaxVertex=m_iNumFace;	
			m_pViewList->m_pVertex=new SVertex[m_iNumFace*3];
			if(m_sSkinningVt)
			{
				m_pViewList->m_pSknVt=new sSkinningVertex[m_pViewList->m_iMaxVertex*3];
			}
			m_pViewList->m_pIndex=new int[m_iNumFace];
			m_pViewList->m_pMeterial=&pMeterial[m_iMeterial_Ref];

		for(int i=0;i<m_iNumFace;i++)
		{
			m_pViewList->m_pIndex[i]=i;
		}

	}

}

void cMesh::MakeVertex()
{
	sViewList* VTemp=m_pViewList;

	int k=0;
	int j=0;
	int iii=0;
	while(VTemp)
	{
		k=0;
		VTemp->m_iNumVertex=0;

		for(int i=0;i<VTemp->m_iMaxVertex;i++)
		{
			if(i==VTemp->m_iMaxVertex-1)
			{
				int a=0;
			}
			j=VTemp->m_pIndex[i];

			VTemp->m_pVertex[i*3+0].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_0].v;
			
			VTemp->m_pVertex[i*3+0].nv=m_sTriangle[j].m_vVtNomal[0];

			VTemp->m_pVertex[i*3+0].Diffuse=m_sTriangle[j].VertexColor[0];

			VTemp->m_pVertex[i*3+0].tu=m_sTriangle[j].m_sTverlist[0].tu;
			VTemp->m_pVertex[i*3+0].tv=m_sTriangle[j].m_sTverlist[0].tv;


			VTemp->m_pVertex[i*3+1].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_1].v;
			
			VTemp->m_pVertex[i*3+1].nv=m_sTriangle[j].m_vVtNomal[1];

			VTemp->m_pVertex[i*3+1].Diffuse=m_sTriangle[j].VertexColor[1];

			VTemp->m_pVertex[i*3+1].tu=m_sTriangle[j].m_sTverlist[1].tu;
			VTemp->m_pVertex[i*3+1].tv=m_sTriangle[j].m_sTverlist[1].tv;

			VTemp->m_pVertex[i*3+2].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_2].v;

			VTemp->m_pVertex[i*3+2].nv=m_sTriangle[j].m_vVtNomal[2];

			VTemp->m_pVertex[i*3+2].Diffuse=m_sTriangle[j].VertexColor[2];

			VTemp->m_pVertex[i*3+2].tu=m_sTriangle[j].m_sTverlist[2].tu;
			VTemp->m_pVertex[i*3+2].tv=m_sTriangle[j].m_sTverlist[2].tv;


			//스키닝 데이터
			//스키닝[?].p버택스 = 뷰리스트 버택스[?]의 주소
			//스키닝구조체로 접근하여 나중에 버택스를 수정할것임. 그것을 랜더

			if(m_sSkinningVt)
			{	
				VTemp->m_pSknVt[i*3+0].m_pVertex=&VTemp->m_pVertex[i*3+0].v;
				VTemp->m_pSknVt[i*3+0].m_VtIndex=m_sTriangle[j].m_sFaceIndex.m_0;
				VTemp->m_pSknVt[i*3+0].m_NumBlend=m_sSkinningVt[VTemp->m_pSknVt[i*3+0].m_VtIndex].m_NumBlend;
				VTemp->m_pSknVt[i*3+0].m_bBland=m_sSkinningVt[VTemp->m_pSknVt[i*3+0].m_VtIndex].m_bBland;
				VTemp->m_pSknVt[i*3+0].m_pBlandVt = m_sSkinningVt[VTemp->m_pSknVt[i*3+0].m_VtIndex].m_pBlandVt;
				
				//스키닝 데이터
				VTemp->m_pSknVt[i*3+1].m_pVertex=&VTemp->m_pVertex[i*3+1].v;
				VTemp->m_pSknVt[i*3+1].m_VtIndex=m_sTriangle[j].m_sFaceIndex.m_1;
				VTemp->m_pSknVt[i*3+1].m_NumBlend=m_sSkinningVt[VTemp->m_pSknVt[i*3+1].m_VtIndex].m_NumBlend;
				VTemp->m_pSknVt[i*3+1].m_bBland=m_sSkinningVt[VTemp->m_pSknVt[i*3+1].m_VtIndex].m_bBland;
				VTemp->m_pSknVt[i*3+1].m_pBlandVt = m_sSkinningVt[VTemp->m_pSknVt[i*3+1].m_VtIndex].m_pBlandVt;

				//스키닝 데이터
				VTemp->m_pSknVt[i*3+2].m_pVertex=&VTemp->m_pVertex[i*3+2].v;
				VTemp->m_pSknVt[i*3+2].m_VtIndex=m_sTriangle[j].m_sFaceIndex.m_2;
				VTemp->m_pSknVt[i*3+2].m_NumBlend=m_sSkinningVt[VTemp->m_pSknVt[i*3+2].m_VtIndex].m_NumBlend;
				VTemp->m_pSknVt[i*3+2].m_bBland=m_sSkinningVt[VTemp->m_pSknVt[i*3+2].m_VtIndex].m_bBland;
				VTemp->m_pSknVt[i*3+2].m_pBlandVt = m_sSkinningVt[VTemp->m_pSknVt[i*3+2].m_VtIndex].m_pBlandVt;
			}

			VTemp->m_iNumVertex++;
		}

		VTemp=VTemp->m_pNext;
	}

	int ji=0;
	ji++;

}

void cMesh::AddChild(cMesh* pMesh)
{
	sMeshContainer *pTmp;

	pTmp=new sMeshContainer;
	pTmp->m_pData=pMesh;

	if(m_pChild==NULL)
	{
		m_pChild=pTmp;
	}
	else
	{
		m_pChild->Add(pTmp);
	}
}



HRESULT CAse::LoadAse(char *FileName)
{
	FILE* pf=::fopen(FileName,"rt");

	//FILE* pf=::fopen("ddd.ASE","rt");

	if(pf==NULL)
	{
		return E_FAIL;
	}

	fgets(m_line, 256, pf); 

	sscanf( m_line , "%s", m_str);
	
	if(_stricmp("*3DSMAX_ASCIIEXPORT", m_str)!=0)
		{
			return E_FAIL;
		}
	

	while(!feof(pf))
	{
		fgets(m_line, 256, pf); 

		sscanf( m_line , "%s", m_str);
		
		if(_stricmp("*SCENE", m_str)==0)
		{
			ReadSCENE(pf);
			continue;
		}

		if(_stricmp("*MATERIAL_LIST", m_str)==0)
		{
			ReadMATERIAL_LIST(pf);
			continue;
		}

		if(_stricmp("*GEOMOBJECT", m_str)==0)
		{
			cMesh*	TmpMesh=new cMesh();

			m_pNowMesh=TmpMesh;

			ReadGEOMOBJECT(pf);

			if(strstr(m_pNowMesh->m_NodeName,"Bip0")!=NULL)
			{
				AddBone(m_pNowMesh);
			}
			else
			{
				AddMesh(m_pNowMesh);
			}
			continue;
		}
	}

	fclose(pf);
	
	
	if(m_NormalFlag==false)
	{
		MakeFaceNormalFromWorldVertex();
		MakeVertexNormalFromFaceNormal();
	}

	MakeSkinningLocal();

	MakeInherite();

	SetAllMesh();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	m_pNowMesh=m_pMeshList;

	while(m_pNowMesh)
	{
		m_pNowMesh->MakeIndex(m_Meterial);
		m_pNowMesh->MakeVertex();
		m_pNowMesh=m_pNowMesh->m_pNext;
	}

	m_pNowMesh=m_pBoneList;

	while(m_pNowMesh)
	{
		m_pNowMesh->MakeIndex(m_Meterial);
		m_pNowMesh->MakeVertex();
		m_pNowMesh=m_pNowMesh->m_pNext;
	}

	return S_OK;
}

void CAse::ReadSCENE(FILE *pf)
{
	fgets(m_line, 256, pf);//*SCENE_FILENAME	
	fgets(m_line, 256, pf);//*SCENE_FIRSTFRAME
		sscanf(m_line,"%s%f",m_str, &m_FirstFrame);
	fgets(m_line, 256, pf);//*SCENE_LASTFRAME	
		sscanf(m_line,"%s%f",m_str, &m_LastFrame);
	fgets(m_line, 256, pf);//*SCENE_FRAMESPEED
		sscanf(m_line,"%s%f",m_str, &m_FrameSpeed);
	fgets(m_line, 256, pf);//*SCENE_TICKSPERFRAME	
		sscanf(m_line,"%s%f",m_str, &m_TickPerFrame);
	fgets(m_line, 256, pf);//*SCENE_BACKGROUND_STATIC	
	fgets(m_line, 256, pf);//*SCENE_AMBIENT_STATIC	
	fgets(m_line, 256, pf);//}
}

void CAse::ReadMATERIAL_LIST(FILE *pf)
{
	int Mtrcount=0;
	while(1)
	{
		fgets(m_line, 256, pf); 

		sscanf( m_line , "%s", m_str);
		
		if(_stricmp("*MATERIAL_COUNT", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&m_iNumMaterial);

			m_Meterial= new SMeterial[m_iNumMaterial];
			continue;
		}

		if(_stricmp("*MATERIAL", m_str)==0)
		{
			ReadMATERIAL(pf,&m_Meterial[Mtrcount]);
			Mtrcount++;
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

}

void CAse::ReadMATERIAL(FILE *pf,SMeterial* pNowMeterial)
{
	int num;
	
	ZeroMemory( &pNowMeterial->m_d3dMaterial, sizeof(D3DMATERIAL9) );
	pNowMeterial->m_d3dMaterial.Diffuse.r = pNowMeterial->m_d3dMaterial.Ambient.r = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.g = pNowMeterial->m_d3dMaterial.Ambient.g = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.b = pNowMeterial->m_d3dMaterial.Ambient.b = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.a = pNowMeterial->m_d3dMaterial.Ambient.a = 1;


	while(2)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*NUMSUBMTLS", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&pNowMeterial->m_iSubMeterialCount);

			pNowMeterial->m_SubMeterial=new SMeterial[pNowMeterial->m_iSubMeterialCount];
			continue;
		}

		if(_stricmp("*SUBMATERIAL", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&num);
			ReadMATERIAL(pf,&pNowMeterial->m_SubMeterial[num]);
			continue;
		}

		if(_stricmp("*MATERIAL_AMBIENT", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Ambient.r,
				&pNowMeterial->m_d3dMaterial.Ambient.g,
				&pNowMeterial->m_d3dMaterial.Ambient.b);
			continue;
		}

		if(_stricmp("*MATERIAL_DIFFUSE", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Diffuse.r,
				&pNowMeterial->m_d3dMaterial.Diffuse.g,
				&pNowMeterial->m_d3dMaterial.Diffuse.b);
			continue;
		}

		if(_stricmp("*MATERIAL_SPECULAR", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Specular.r,
				&pNowMeterial->m_d3dMaterial.Specular.g,
				&pNowMeterial->m_d3dMaterial.Specular.b);
			continue;
		}

		if(_stricmp("*MAP_DIFFUSE", m_str)==0)
		{
			pNowMeterial->bUseTexture=true;
			// 텍스쳐 불러오기 
			ReadMtrTextureName(pf,pNowMeterial);
			continue;
		}

		if(_stricmp("*MAP_OPACITY", m_str)==0)
		{
			pNowMeterial->bUseTexture=true;
			pNowMeterial->bUseOpacity=true;
			ReadMtrTextureName(pf,pNowMeterial);
			//텍스쳐 불러오기
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

}

void CAse::ReadMtrTextureName(FILE *pf,SMeterial *pNowMeterial)
{
	int Start=0,End=0;
	bool Check=false;
	int Count=0;


	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*BITMAP", m_str)==0)
		{
			while(2)
			{
				if(m_line[Count]=='"')
				{
					if(Check)
					{
						End=Count-1;
						break;
					}
					else
					{
						Check=true;
						Start=Count+1;
					}
				}
				Count++;
			}
			int i=Start;
			int j=0;
			for(;i<=End;i++,j++)
				{
					pNowMeterial->m_TextuerFileName[j]=m_line[i];
				}
				pNowMeterial->m_TextuerFileName[j]=NULL;
		}

		if(_stricmp("}", m_str)==0)
		{
			break;
		}

	}

}

void CAse::ReadGEOMOBJECT(FILE *pf)
{
	char tmpstr[256];

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*NODE_NAME", m_str)==0)		
		{
			ReadFileName(m_line,m_pNowMesh->m_NodeName);
			continue;
		}

		if(_stricmp("*NODE_PARENT", m_str)==0)
		{
			ReadFileName(m_line,m_pNowMesh->m_parentsName);
			m_pNowMesh->m_bParents=true;
			continue;
		}

		if(_stricmp("*NODE_TM", m_str)==0)
		{
			ReadTM(pf);
			continue;
		}	

		if(_stricmp("*MESH", m_str)==0)
		{
			ReadMESH(pf);
			continue;
		}

		if(_stricmp("*MATERIAL_REF", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&m_pNowMesh->m_iMeterial_Ref);
			continue;
		}
		if(_stricmp("*PHYSIQUE", m_str)==0)
		{
			ReadPHYSIQUE(pf);
			continue;
		}

		if(_stricmp("*TM_ANIMATION", m_str)==0)
		{
			ReadAnimation(&m_pNowMesh->m_sAnimation,pf);
			continue;
		}


		if(_stricmp("}", m_str)==0)
			break;
	}

	
}
void CAse::ReadPHYSIQUE(FILE *pf)
{
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*PHYSIQUE_NUMVERTEXASSIGNMENT", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&m_pNowMesh->m_iNumPhysiqueVt);
			m_pNowMesh->m_sSkinningVt= new sSkinningVertex[m_pNowMesh->m_iNumPhysiqueVt];
		}
		if(_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_LIST", m_str)==0)
		{
			ReadPHYSIQUE_VT_LIST(pf);
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

}

void CAse::ReadPHYSIQUE_VT_LIST(FILE *pf)
{
	int Count=0;
	int iTemp=0;
	float fTemp=0.0f;
	char NodeName[256];
	D3DXVECTOR3 *vtmp;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);


		if(_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_BLENDED_RIGIDTYPE", m_str)==0)
		{
			vtmp= new D3DXVECTOR3(0,0,0);
			sSkinningVertex *Temp=&m_pNowMesh->m_sSkinningVt[Count];
			*vtmp=m_pNowMesh->m_sVertex[Count].v;
			Temp->m_pVertex=vtmp;
			Temp->m_VtIndex=Count;

			fgets(m_line, 256, pf); // *PHYSIQUE_VERTEXASSIGNMENT_NUMNODE 2
			sscanf( m_line , "%s %d", m_str,&Temp->m_NumBlend);
		
			Temp->m_bBland=true;
			Temp->m_pBlandVt=new sBlandVertexInfo[Temp->m_NumBlend];

			fgets(m_line, 256, pf); // *PHYSIQUE_VERTEXASSIGNMENT_NODELIST 
			while(1)
			{
				fgets(m_line, 256, pf); 
				sscanf( m_line , "%s", m_str);
				
				if(_stricmp("}", m_str)==0)
					break;


				if(_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_NODE", m_str)==0)
				{

				sscanf( m_line , "%s %d %f %s", m_str, //*PHYSIQUE_VERTEXASSIGNMENT_NODE 0 0.999964 "Bip01 L Foot"
					&iTemp,&fTemp,
					NodeName);

				ReadFileName(m_line,Temp->m_pBlandVt[iTemp].m_NodeName);

				Temp->m_pBlandVt[iTemp].m_fWeight=fTemp;

				}

				
			}
			Count++;
			fgets(m_line, 256, pf);
			continue;
		}	
		
		if(_stricmp(m_str,"*PHYSIQUE_VERTEXASSIGNMENT_NONBLENDED_RIGIDTYPE")==0)
		{
			vtmp= new D3DXVECTOR3(0,0,0);
			sSkinningVertex *Temp=&m_pNowMesh->m_sSkinningVt[Count];
			*vtmp=m_pNowMesh->m_sVertex[Count].v;
			Temp->m_pVertex=vtmp;
			Temp->m_VtIndex=Count;
			
			sscanf( m_line , "%s %d %s", m_str,&Temp->m_VtIndex,NodeName);

			Temp->m_bBland=false;
			Temp->m_NumBlend=1;
			Temp->m_pBlandVt=new sBlandVertexInfo;
			ReadFileName(m_line,Temp->m_pBlandVt->m_NodeName);
			Temp->m_pBlandVt->m_fWeight=1.0f;

			Count++;
			continue;
		}

		

		if(_stricmp("}", m_str)==0)
			break;
	}

}
void CAse::ReadAniMationFromFile(char* AniFileName)
{
	FILE* pf2=::fopen(AniFileName,"rt");

	char	TempName[128];

	sAnimation* tempAni;

	while(!feof(pf2))
	{
		fgets(m_line, 256, pf2); 
		sscanf( m_line ,"%s", m_str);

		if(_stricmp("*ANINAME", m_str)==0)
		{
			sscanf( m_line , "%s %s",m_str,TempName);
			ReadFileName(TempName,TempName);

			while(1)
			{
				fgets(m_line, 256, pf2); 
				sscanf( m_line ,"%s", m_str);

				if(_stricmp("*TM_ANIMATION", m_str)==0)
				{
					tempAni=new sAnimation();
					::strcpy(tempAni->m_AniName,TempName);//,tempAni->m_AniName);
					ReadAnimation( tempAni,pf2);

					m_pNowMesh= SearchBone(tempAni->m_Name);

					if(m_pNowMesh)
					{
						if(!m_pNowMesh->m_pAniList)
						{
							m_pNowMesh->m_pAniList=tempAni;
						}
						else
						{
							m_pNowMesh->m_pAniList->Add(tempAni);
						}
					}
					continue;
				}

				if(_stricmp("}", m_str)==0)
					break;
			}
		}
	}
	fclose(pf2);
}

void CAse::ReadAnimation(sAnimation *p_Animation,FILE *pf)
{
	//m_pNowMesh->m_bAniData=true;

	//FILE* Anipf=::fopen("AniData.txt","rt");

	char TempStr[256];

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*NODE_NAME", m_str)==0)
		{
			sscanf( m_line , "%s %s",m_str,TempStr);
			ReadFileName(m_line,p_Animation->m_Name);
			continue;
		}
		
		if ( _stricmp(m_str, "*CONTROL_SCALE_TRACK") == 0 || _stricmp(m_str, "*CONTROL_SCALE_TCB") == 0
			|| _stricmp(m_str,"*CONTROL_SCALE_BEZIER")==0)
		{
			//Scale일경우
			ReadScale_Track(p_Animation,pf);
			continue;
		}

		if( _stricmp(m_str, "*CONTROL_ROT_TRACK") == 0 || _stricmp(m_str, "*CONTROL_ROT_TCB") == 0
			|| _stricmp(m_str,"*CONTROL_ROT_BEZIER")==0)
		{
			//회전일경우 
			ReadRot_Track(p_Animation,pf);
			continue;
		}
		
		if(   _stricmp(m_str, "*CONTROL_POS_TRACK")==0  || _stricmp(m_str, "*CONTROL_POS_TCB")==0
			|| _stricmp(m_str,"*CONTROL_POS_BEZIER")==0)
		{
			//이동일경우
			ReadPos_Track(p_Animation,pf);
			continue;
		}

		
		if(_stricmp("}", m_str)==0)
			break;
	}

}

void CAse::ReadPos_Track(sAnimation *p_Animation,FILE *pf)
{
	sPos_Track *Temp;
	sPos_Track *Tail=NULL;

	int Index;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*CONTROL_POS_SAMPLE", m_str)==0)
		{
			Temp=new sPos_Track;
			sscanf( m_line , "%s %d %f %f %f",m_str,&Index,&(Temp->m_Pos.x),&(Temp->m_Pos.z),&(Temp->m_Pos.y));

			Temp->m_iIndex=Index;
			if(Tail==NULL)
			{
				p_Animation->m_Pos=Temp;
				Tail=Temp;
			}
			else
			{
				Tail->m_pNext=Temp;
				Temp->m_pPrev=Tail;
				Tail=Temp;
			}
		}

		if(_stricmp("}", m_str)==0)
		{
			p_Animation->m_Pos->m_iMyLastIndex=Index;
			break;
		}
	}
}
void CAse::ReadScale_Track(sAnimation *p_Animation,FILE *pf)
{
	sScale_Track *Temp;
	sScale_Track *Tail=NULL;

	int Index;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);
		
		if(_stricmp("}", m_str)==0)
		{
			p_Animation->m_Scale->m_iMyLastIndex=Index;
			break;
		}

		Temp=new sScale_Track;

		sscanf(m_line, "%s %d%f%f%f%f%f%f%f",m_str, &Index, &(Temp->m_fX), &(Temp->m_fZ), &(Temp->m_fY), 
			&(Temp->m_aX), &(Temp->m_aY), &(Temp->m_aZ), &(Temp->m_Ang));

		Temp->m_iIndex=Index;

		if(p_Animation->m_Scale==NULL)
		{
			p_Animation->m_Scale = Temp;
			Tail = Temp;
		}
		else
		{
			Tail->m_pNext = Temp;
			Temp->m_pPrev = Tail;
			Tail = Temp;
		}

		
	}

}
void CAse::ReadRot_Track(sAnimation *p_Animation,FILE *pf)
{
	sRot_Track *Temp;
	sRot_Track *Tail=NULL;

	D3DXVECTOR3	vReadRot;

	D3DXQUATERNION	tmpR=m_pNowMesh->m_TmRot;

	int Index;

	float fW;

	D3DXQUATERNION qR;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*CONTROL_ROT_SAMPLE", m_str)==0)
		{
			Temp=new sRot_Track;

			sscanf( m_line , "%s %d %f %f %f %f",m_str,&Index,&vReadRot.x,&vReadRot.z,&vReadRot.y,&fW);

			Temp->m_iIndex=Index;
			Temp->m_x=vReadRot.x;
			Temp->m_y=vReadRot.y;
			Temp->m_z=vReadRot.z;
			Temp->m_w=fW;

			qR.x=(float)sinf(fW/2.0f) * vReadRot.x;
			qR.y=(float)sinf(fW/2.0f) * vReadRot.y;
			qR.z=(float)sinf(fW/2.0f) * vReadRot.z;
			qR.w=cosf(fW/2.0f);


			if(Tail==NULL)
			{
				Temp->m_qrot=qR;
				p_Animation->m_Rot=Temp;
				Tail=Temp;
			}
			else
			{
				D3DXQuaternionMultiply(&Temp->m_qrot,&Tail->m_qrot,&qR);
				Tail->m_pNext=Temp;
				Temp->m_pPrev=Tail;
				Tail=Temp;
			}
		}

		if(_stricmp("}", m_str)==0)
		{
			p_Animation->m_Rot->m_iMyLastIndex=Index;
			break;
		}
	}

}


void CAse::ReadTM(FILE *pf)
{
	D3DXMatrixIdentity(&m_pNowMesh->m_TmMat);

	float fX,fY,fZ,fW;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*TM_ROW0", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._11,
				&m_pNowMesh->m_TmMat._13,
				&m_pNowMesh->m_TmMat._12);
			continue;
		}

		if(_stricmp("*TM_ROW1", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._31,
				&m_pNowMesh->m_TmMat._33,
				&m_pNowMesh->m_TmMat._32);
			continue;
		}

		if(_stricmp("*TM_ROW2", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._21,
				&m_pNowMesh->m_TmMat._23,
				&m_pNowMesh->m_TmMat._22);
			continue;
		}

		if(_stricmp("*TM_ROW3", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._41,
				&m_pNowMesh->m_TmMat._43,
				&m_pNowMesh->m_TmMat._42);
			continue;
		}

		if(_stricmp("*TM_POS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmPos.x,
				&m_pNowMesh->m_TmPos.z,
				&m_pNowMesh->m_TmPos.y);
			continue;
		}

		if(_stricmp("*TM_ROTAXIS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}
		if(_stricmp("*TM_ROTANGLE", m_str)==0)
		{
			sscanf( m_line , "%s %f",m_str,&fW);

			m_pNowMesh->m_TmRot.x=(float)sinf(fW/2.0f) *fX;
			m_pNowMesh->m_TmRot.y=(float)sinf(fW/2.0f) *fY;
			m_pNowMesh->m_TmRot.z=(float)sinf(fW/2.0f) *fZ;
			m_pNowMesh->m_TmRot.w=(float)cosf(fW/2.0f);

			continue;
		}

		if(_stricmp("*TM_SCALE", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmScale.x,
				&m_pNowMesh->m_TmScale.z,
				&m_pNowMesh->m_TmScale.y);
			continue;
		}
		if(_stricmp("*TM_SCALEAXIS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}

		if(_stricmp("*TM_SCALEAXISANG", m_str)==0)
		{
			sscanf( m_line , "%s %f",m_str,&fW);
			m_pNowMesh->m_TmScaleRot.x=(float)sinf(fW/2.0f) *fX;
			m_pNowMesh->m_TmScaleRot.y=(float)sinf(fW/2.0f) *fY;
			m_pNowMesh->m_TmScaleRot.z=(float)sinf(fW/2.0f) *fZ;
			m_pNowMesh->m_TmScaleRot.w=(float)cosf(fW/2.0f);
			continue;
		}

		if(_stricmp("}", m_str)==0)
		{
			D3DXMatrixInverse(&m_pNowMesh->m_InvTm,NULL,&m_pNowMesh->m_TmMat);
			break;
		}
	}
}

void CAse::ReadMESH(FILE *pf)
{
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_NUMVERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumVertex);
			m_pNowMesh->m_sVertex=new SVertex[m_pNowMesh->m_iNumVertex];

			continue;
		}

		if(_stricmp("*MESH_NUMFACES", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumFace);
			m_pNowMesh->m_sTriangle=new STriangle[m_pNowMesh->m_iNumFace];

			for(int i=0;i<m_pNowMesh->m_iNumFace;i++)
			{
				m_pNowMesh->m_sTriangle[i].Init();
			}

			continue;
		}

		if(_stricmp("*MESH_VERTEX_LIST", m_str)==0)
		{
			ReadMESH_VERTEX_LIST(pf);

			continue;
		}

		if(_stricmp("*MESH_FACE_LIST", m_str)==0)
		{
			ReadMESH_FACE_LIST(pf);

			continue;
		}

		if(_stricmp("*MESH_NUMTVERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumTvVertex);

			m_pNowMesh->m_sTvertlist=new STvertlist[m_pNowMesh->m_iNumTvVertex];

			continue;
		}

		if(_stricmp("*MESH_TVERTLIST", m_str)==0)
		{
			ReadMESH_TVERTLIST(pf);

			continue;
		}

		if(_stricmp("*MESH_NUMTVFACES", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNUMTVFACES);

			continue;
		}

		if(_stricmp("*MESH_TFACELIST", m_str)==0)
		{
			ReadMESH_TFACELIST(pf);

			continue;
		}

		if ( _stricmp("*MESH_NUMCVERTEX",m_str ) == 0)
		{
			ReadMESH_CVERTEX(pf);///////////////////////////////////////
			continue;
		}
		if(_stricmp("*MESH_NUMCVFACES",m_str)==0)//*MESH_NUMCVERTEX
		{
			ReadMESH_CFACELIST(pf);////////////////////////////////////
			continue;
		}

		if(_stricmp("*MESH_NORMALS", m_str)==0)
		{
			ReadMESH_NORMALS(pf);
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}
}

void CAse::ReadMESH_VERTEX_LIST(FILE *pf)
{
	int iNum;
	D3DXVECTOR3 vtemp(0,0,0);
	float x,y,z;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_VERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d %f %f %f",m_str,&iNum,&vtemp.x,&vtemp.z,&vtemp.y);
			m_pNowMesh->m_sVertex[iNum].v=vtemp;
		}
		if(_stricmp("}", m_str)==0)
		{break;}
	}

}
void CAse::ReadMESH_FACE_LIST(FILE *pf)
{
	int iCount=0,tmp=0;
	DWORD Face_0,Face_1,Face_2;
	char Smooth[20];
	char MaterID[20];
	int ID;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		memset(MaterID, 0, 20);
		memset(Smooth, 0, 20);

		if(_stricmp("*MESH_FACE", m_str)==0)
		{
			sscanf(m_line, "%s%s %s%d %s%d %s%d %s%d %s%d %s%d %s%s %s%d",m_str,m_str,
				m_str,&Face_0,
				m_str,&Face_1,
				m_str,&Face_2,
				m_str,&tmp,
				m_str,&tmp,
				m_str,&tmp,
				m_str,Smooth,
				MaterID,&ID
				);
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_0=Face_0;
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_1=Face_2;
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_2=Face_1;

			if(_strcmpi(MaterID,"*MESH_MTLID")==0)
			{
				m_pNowMesh->m_sTriangle[iCount].m_iMeterialID = ID;
			}
			if(_strcmpi(Smooth,"*MESH_MTLID")==0)
			{
				m_pNowMesh->m_sTriangle[iCount].m_iMeterialID = atoi(MaterID);
			}
			iCount++;
		}
		
		if(_stricmp("}", m_str)==0)
		{break;}
	}
}

void CAse::ReadMESH_TVERTLIST(FILE *pf)
{
	if(m_pNowMesh->m_iNumTvVertex <=0)
	{
		return;
	}

	int iNum=0,tmp=0;
	float tu,tv,tw;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_TVERT", m_str)==0)
		{
			sscanf(m_line, "%s %d %f %f %f",m_str,&tmp, &tu,&tv,&tw );
			m_pNowMesh->m_sTvertlist[iNum].tu=tu;
			m_pNowMesh->m_sTvertlist[iNum].tv=1.0f-tv;
			iNum++;
		}
		if(_stricmp("}", m_str)==0)
		{break;}
	}

}

void CAse::ReadMESH_TFACELIST(FILE *pf)
{
	if(m_pNowMesh->m_iNUMTVFACES <=0)
	{
		return;
	}

	int iCount=0,tmp=0;
	int Tvindex[3];

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_TFACE", m_str)==0)
		{
			sscanf(m_line, "%s %d %d %d %d",m_str,&tmp, &Tvindex[0],&Tvindex[2],&Tvindex[1] );
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[0].tu=m_pNowMesh->m_sTvertlist[Tvindex[0]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[0].tv=m_pNowMesh->m_sTvertlist[Tvindex[0]].tv;

			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[1].tu=m_pNowMesh->m_sTvertlist[Tvindex[1]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[1].tv=m_pNowMesh->m_sTvertlist[Tvindex[1]].tv;

			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[2].tu=m_pNowMesh->m_sTvertlist[Tvindex[2]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[2].tv=m_pNowMesh->m_sTvertlist[Tvindex[2]].tv;

			iCount++;
		}

		if(_stricmp("}", m_str)==0)
		{break;}
	}

}

void CAse::ReadMESH_CVERTEX(FILE *pf)
{
	sscanf(m_line,"%s %d",m_str, &m_pNowMesh->m_iNumColorVt);

	if(m_pNowMesh->m_iNumColorVt <= 0)return;

	m_pNowMesh->m_ColorList= new D3DXCOLOR[m_pNowMesh->m_iNumColorVt];

	int iNum;

	float r,g,b;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		sscanf(m_line,"%s %d%f%f%f", m_str, &iNum, &r, &g, &b);

		m_pNowMesh->m_ColorList[iNum].r=r;
		m_pNowMesh->m_ColorList[iNum].g=g;
		m_pNowMesh->m_ColorList[iNum].b=b;
		m_pNowMesh->m_ColorList[iNum].a=1.0f;

		if(_stricmp("}", m_str)==0)
		{break;}
	}

}
void CAse::ReadMESH_CFACELIST(FILE *pf)
{
	sscanf(m_line,"%s %d",m_str, &m_pNowMesh->m_iNumColorFace);
	if(m_pNowMesh->m_iNumColorFace <= 0)return;

	BYTE R0, G0, B0, A0;
	int i,num;

	int facenum, v1, v2, v3;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		sscanf(m_line,"%s %d %d %d %d",m_str, &facenum, &v1, &v3, &v2);
		R0 = (BYTE)(m_pNowMesh->m_ColorList[v1].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v1].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v1].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v1].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[0] = D3DCOLOR_XRGB(R0,G0,B0);

		R0 = (BYTE)(m_pNowMesh->m_ColorList[v2].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v2].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v2].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v2].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[1] = D3DCOLOR_XRGB(R0,G0,B0);

		R0 = (BYTE)(m_pNowMesh->m_ColorList[v3].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v3].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v3].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v3].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[2] = D3DCOLOR_XRGB(R0,G0,B0);


		if(_stricmp("}", m_str)==0)
		{break;}
	}
}




void CAse::ReadMESH_NORMALS(FILE *pf)
{

	int iCount=0,iNum=0;

	float x=0.0f,y=0.0f,z=0.0f;

	m_NormalFlag=true;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line ,"%s", m_str);

		if(_stricmp("*MESH_FACENORMAL", m_str)==0)
		{
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum, &x, &z, &y );

			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].z=z;

			iCount++;
		}

		if(_stricmp("}", m_str)==0)
		{break;}

	}

}



void CAse::AddBone(cMesh *pNowMesh)
{
	cMesh *tmpMesh;

	if(!m_pBoneList)
	{
		m_pBoneList=pNowMesh;
	}
	else
	{
		tmpMesh=m_pBoneList;
		while(tmpMesh)
		{
			if(tmpMesh->m_pNext==NULL)
			{
				tmpMesh->m_pNext=pNowMesh;
				break;
			}
			else
			{
				tmpMesh=tmpMesh->m_pNext;
			}
		}

	}
}
void CAse::AddMesh(cMesh *pNowMesh)
{
	cMesh *tmpMesh;

	if(!m_pMeshList)
	{
		m_pMeshList=pNowMesh;
	}
	else
	{
		tmpMesh=m_pMeshList;
		while(tmpMesh)
		{
			if(tmpMesh->m_pNext==NULL)
			{
				tmpMesh->m_pNext=pNowMesh;
				break;
			}
			else
			{
				tmpMesh=tmpMesh->m_pNext;
			}
		}

	}

}

void CAse::MakeFaceNormalFromWorldVertex(){}
void CAse::MakeVertexNormalFromFaceNormal(){}


void CAse::MakeSkinningLocal()
{

	cMesh* temp=m_pMeshList;

	while(temp)
	{
		if(temp->m_sSkinningVt)
		{
			for(int i=0;i<temp->m_iNumPhysiqueVt;i++)
			{
				temp->m_sSkinningVt[i].MakeLoaclVt(m_pMeshList,m_pBoneList);
			}
		}

		temp=temp->m_pNext;
	}
}

void CAse::MakeInherite()
{
	cMesh *Child;
	cMesh *Parents;

	Child=m_pMeshList;

	while(Child)
	{
		if(Child->m_bParents)
		{
			Parents=Search(Child->m_parentsName);
			if(Parents)
			{
				Child->m_pParents=Parents;
				Parents->AddChild(Child);
			}
			else
			{
				Parents=SearchBone(Child->m_parentsName);
				Child->m_pParents=Parents;
			}
		}
		
		Child=Child->m_pNext;
	}

	Child=m_pBoneList;

	while(Child)
	{
		if(Child->m_bParents)
		{
			Parents=SearchBone(Child->m_parentsName);

			if(Parents)
			{
				Child->m_pParents=Parents;
				Parents->AddChild(Child);
			}
		}
			Child=Child->m_pNext;
	}

}

void CAse::SetAllMesh()
{
	cMesh *pNowMesh;

	pNowMesh=m_pMeshList;

	D3DXMATRIXA16 mat;

	D3DXVECTOR3 vTmp1,vTmp2;

	while(pNowMesh)
	{
		//D3DXMatrixInverse(&mat,0,&pNowMesh->m_TmMat);

		//pNowMesh->m_InvTm=mat;

		for(int i=0;i<pNowMesh->m_iNumVertex;i++)
		{
			vTmp1=pNowMesh->m_sVertex[i].v;

			D3DXVec3TransformCoord(&vTmp2,&vTmp1,&pNowMesh->m_InvTm);

			pNowMesh->m_sVertex[i].v=vTmp2;
		}

		pNowMesh=pNowMesh->m_pNext;
	}

	pNowMesh=m_pBoneList;

	while(pNowMesh)
	{
		//D3DXMatrixInverse(&mat,0,&pNowMesh->m_TmMat);

		///pNowMesh->m_InvTm=mat;

		for(int i=0;i<pNowMesh->m_iNumVertex;i++)
		{
			vTmp1=pNowMesh->m_sVertex[i].v;

			D3DXVec3TransformCoord(&vTmp2,&vTmp1,&pNowMesh->m_InvTm);

			pNowMesh->m_sVertex[i].v=vTmp2;
		}

		pNowMesh=pNowMesh->m_pNext;
	}
}

cMesh* CAse::Search(char* Name)
{
	cMesh* tmpMesh;
	tmpMesh=m_pMeshList;

	while(tmpMesh)
	{
		if(_stricmp(Name, tmpMesh->m_NodeName)==0)
		{
			return tmpMesh;
		}
		tmpMesh=tmpMesh->m_pNext;
	}
	return NULL;
}

cMesh* CAse::SearchBone(char* Name)
{
	cMesh* tmpMesh;
	tmpMesh=m_pBoneList;

	while(tmpMesh)
	{
		if(_stricmp(tmpMesh->m_NodeName, Name)==0)
		{
			return tmpMesh;
		}
		tmpMesh=tmpMesh->m_pNext;
	}
	return NULL;

}

//초기화 함수
HRESULT CAse::MakeVertexBuffer()
{

	return S_OK;

}
HRESULT CAse::MakeIndexBuffer()
{

	return S_OK;

}

void CAse::Alpha(bool flag)
{
	if(flag)
	{
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
		
		m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
		

		
		m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE); 
		m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
		m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ;     
		m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE);
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	}
	else
	{
		m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW); 
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , FALSE );
		m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);

	}
}
	
void CAse::RenderAse(D3DXMATRIX Scalemat,D3DXMATRIX Rotmat,D3DXMATRIX Posmat,cMesh* pNowMesh)
{
	D3DXMATRIX WorldMat;
	D3DXMatrixIdentity(&WorldMat);
	if(pNowMesh==NULL)return;

	DWORD dwfvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE  |D3DFVF_TEX1 ;
	DWORD fvfsize = D3DXGetFVFVertexSize(dwfvf);

	// 정점 타입 설정 
	m_pd3dDevice->SetFVF( dwfvf );
	
	
		// 정점의 월드 행렬 반영
	
	if(pNowMesh->m_sSkinningVt)
	{
		WorldMat=Scalemat*Rotmat*Posmat;
		m_pd3dDevice->SetTransform(D3DTS_WORLD,&WorldMat);
	}
	else
	{
		WorldMat=pNowMesh->m_AniMat;
		WorldMat._41+=Posmat._41;
		WorldMat._42+=Posmat._42;
		WorldMat._43+=Posmat._43;
		
		m_pd3dDevice->SetTransform(D3DTS_WORLD,&WorldMat);
	}
	
	
	sViewList* ViewList;
	ViewList = pNowMesh->m_pViewList;

	//-------------- 메시 리스트에서 출력 ------------------
	while(ViewList)
	{
		if(ViewList->m_iNumVertex>0)
		{
			// step2
            // 텍스쳐 설정 
			if(ViewList->m_pMeterial->bUseTexture)
				m_pd3dDevice->SetTexture(0, ViewList->m_pMeterial->m_pTexture );
			else
				m_pd3dDevice->SetMaterial(&(ViewList->m_pMeterial->m_d3dMaterial));	
			
			// 재질 설정
	      //m_pd3dDevice->SetMaterial(&(ViewList->pMaterial->d3dMaterial));	
			
			// 알파 설정 
			if(ViewList->m_pMeterial->bUseOpacity)			
				Alpha(true);

			//----------------- 비 정점 방식으로 ---------------------		
			// 랜더
			m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 
				ViewList->m_iNumVertex, ViewList->m_pVertex, sizeof(SVertex));
		
			if(ViewList->m_pMeterial->bUseOpacity)
				Alpha(false);
		}
		ViewList = ViewList->m_pNext;
	}



}

void CAse::SetUvVertexIndex()
{
	
}
void CAse::ReadFileName(char* Src,char *Dest)
{
	int Count=0;
	int Start=0;
	int End=0;

	bool Check=false;


	if(Src==NULL || Dest==NULL)
	{
		return;
	}

	while(2)
	{
		if(Src[Count]=='"')
		{
			if(Check)
			{
				End=Count-1;
				break;
			}
			else
			{
				Check=true;
				Start=Count+1;
			}
		}
		Count++;
	}

	int i=Start;
	int j=0;

	for(;i<=End;i++,j++)
	{
		Dest[j]=Src[i];
	}

	Dest[j]=NULL;

}


void CAse::LoadAseTexture()
{
	STextureList* Temp;

	for(int i=0; i<m_iNumMaterial; i++)
	{
		if(m_Meterial[i].bUseTexture)
		{
			m_Meterial[i].m_pTextureContainer = m_pTextureContainer;

			Temp = m_pTextureContainer->LoadTexture(m_pd3dDevice, 
				m_Meterial[i].m_TextuerFileName);
			if(Temp)
				m_Meterial[i].m_pTexture = Temp->m_pTexture;
			else
				m_Meterial[i].m_pTexture = NULL;

		}
		for(int j=0; j<m_Meterial[i].m_iSubMeterialCount; j++)
		{
			if(m_Meterial[i].m_SubMeterial[j].bUseTexture)
			{
				m_Meterial[i].m_SubMeterial[j].m_pTextureContainer = m_pTextureContainer;

				Temp = m_pTextureContainer->LoadTexture(m_pd3dDevice,
					m_Meterial[i].m_SubMeterial[j].m_TextuerFileName);
				if(Temp)
					m_Meterial[i].m_SubMeterial[j].m_pTexture = Temp->m_pTexture;
				else
					m_Meterial[i].m_SubMeterial[j].m_pTexture = NULL;

			}
		}
	}

}


void CAse::UpdateAnimation(float Frame)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	BoneAnimation(mat,Frame);

	MeshAnimation(mat,Frame);
}

void CAse::BoneAnimation(D3DXMATRIX mat,float frame)
{
	cMesh* TempMesh=m_pBoneList;

	while(TempMesh)
	{
		if(TempMesh->m_bParents==false)
		{
			TempMesh->UpdateAniTm(m_pAniName,mat,frame);
		}
		TempMesh=TempMesh->m_pNext;
	}
}

void CAse::MeshAnimation(D3DXMATRIX mat,float frame)
{
	cMesh* TempMesh=this->m_pMeshList;

	while(TempMesh)
	{
		if(TempMesh->m_pParents)
		{
			TempMesh->UpdateAniTm(m_pAniName,TempMesh->m_pParents->m_AniMat,frame);
		}
		else
		{
			if(TempMesh->m_sSkinningVt)
			{
				TempMesh->UpdateSkinning();
			}
			else
			{
				TempMesh->UpdateAniTm(m_pAniName,mat,frame);
			}
		}
		TempMesh=TempMesh->m_pNext;
	}
}

void cMesh::UpdateSkinning()
{
	sViewList* TempView=m_pViewList;
	sSkinningVertex *pSknVtSrc;
	sSkinningVertex *pSknVtDest;
	sSkinningVertex *pSknVt=NULL;
	D3DXVECTOR3 *vTemp;
	D3DXVECTOR3	vTempNoneBland;

	cMesh*		TempWeighMesh;
	D3DXMATRIX TempMat;

	int bland=0;
	int blandx=0;

	////////////////////////////////////////////////////////////
	// 매쉬의 스키닝정점정보전체의 업데이트					  //
	// pSknVtSrc = 스키닝정점 정보전체를 가지고 있다.		  //
	////////////////////////////////////////////////////////////

	pSknVtSrc=m_sSkinningVt;

	for(int i=0;i<m_iNumPhysiqueVt;i++)
	{
		if(pSknVtSrc[i].m_bBland==false)
			{
				TempWeighMesh=pSknVtSrc[i].m_pBlandVt[0].m_pMesh;

				vTempNoneBland=pSknVtSrc[i].m_pBlandVt[0].m_vBipLocal;

				D3DXVec3TransformCoord(&vTempNoneBland,&vTempNoneBland,&TempWeighMesh->m_AniMat);

				pSknVtSrc[i].m_pVertex->x=vTempNoneBland.x;
				pSknVtSrc[i].m_pVertex->y=vTempNoneBland.y;
				pSknVtSrc[i].m_pVertex->z=vTempNoneBland.z;
			}
			else
			{
				vTemp=new D3DXVECTOR3[pSknVtSrc[i].m_NumBlend];

				for(int j=0;j<pSknVtSrc[i].m_NumBlend;j++)
				{
					TempWeighMesh=pSknVtSrc[i].m_pBlandVt[j].m_pMesh;

					vTemp[j]=pSknVtSrc[i].m_pBlandVt[j].m_vBipLocal;

					D3DXVec3TransformCoord(&vTemp[j],&vTemp[j],&TempWeighMesh->m_AniMat);

					vTemp[j]*=pSknVtSrc[i].m_pBlandVt[j].m_fWeight;
				}
				for(int j=1;j<pSknVtSrc[i].m_NumBlend;j++)
				{
					vTemp[0]+=vTemp[j];
				}

				pSknVtSrc[i].m_pVertex->x=vTemp[0].x;
				pSknVtSrc[i].m_pVertex->y=vTemp[0].y;
				pSknVtSrc[i].m_pVertex->z=vTemp[0].z;

				delete[] vTemp; 
			}
	}

	////////////////////////////////////////////////////////////////////////
	//	pSknVtDest =삼각형 갯수 *3 으로 늘어난 스키닝정점정보			  //
	//	원본인 pSknVtSrc값이 중복되어 삼각형갯수 *3 이되었으니			  //
	//	pSknVtDest값은 pSknVtSrc(원본) 에서 찾아서 대입해주면			  //
	//	중복연산을 할필요가 없다.										  //
	//	맴버변수로 m_VtIndex를 가지고있어서 그걸 넣어주면됨				  //
	////////////////////////////////////////////////////////////////////////

	while(TempView)
	{
		pSknVtDest=TempView->m_pSknVt;

		for(int i=0;i<TempView->m_iMaxVertex *3;i++)
		{
			*pSknVtDest[i].m_pVertex=*pSknVtSrc[pSknVtDest[i].m_VtIndex].m_pVertex;
		}
		TempView=TempView->m_pNext;
	}
}
//애니와 애니의 보간
void cMesh::UpdateTransitionAniTm(char *pDestAniName,D3DXMATRIX matParents,float Nowframe)
{
	if(_stricmp(pDestAniName,"STAND")==0)
	{
		int a=0;
	}
	D3DXMATRIX MyAni,RotMat,PosMat,ScaleMat;

	D3DXMatrixIdentity(&MyAni);
	D3DXMatrixIdentity(&RotMat);
	D3DXMatrixIdentity(&PosMat);
	D3DXMatrixIdentity(&ScaleMat);

	D3DXVECTOR3	vPosStart,vPosEnd,vPos;
	
	D3DXQUATERNION	qRot,qRotStart,qRotEnd,qAniScale;

	float DestIndex,StartIndex;

	sAnimation* pAni=m_pAniList;//&m_sAnimation;
	sPos_Track* PosTrack=NULL;//m_sAnimation.GetNowPosTrack(frame);
	sRot_Track* RotTrack=NULL;//;m_sAnimation.GetNowRotTrack(frame);

	cTmInfomation *pTmInfoList=m_pTmInfoList;

	cTmInfomation *pTmInfo=NULL;

	cTmInfomation *pParentsTminfo=NULL;


	while(pTmInfoList)
	{
		if(_stricmp(pDestAniName, pTmInfoList->m_AniName)==0)
		{
			pTmInfo=pTmInfoList;
			break;
		}
		else
		{
			pTmInfoList=pTmInfoList->m_pNext;
		}
	}

	if(m_pParents)
	{
		pTmInfoList=m_pParents->m_pTmInfoList;

		while(2)
		{
			if(_stricmp(pDestAniName, pTmInfoList->m_AniName)==0)
			{
				pParentsTminfo=pTmInfoList;
				break;
			}
			else
			{
				pTmInfoList=pTmInfoList->m_pNext;
			}
		}
	}

	if(m_pParents)
	{
		int a=0;
	}

	while(pAni)
	{
		if(pAni && _stricmp(pDestAniName, pAni->m_AniName)==0)
		{
			PosTrack=pAni->m_Pos;
			RotTrack=pAni->m_Rot;
 			break;
		}
		else
		{
			if(pAni->m_pNext)
			{
				pAni=pAni->m_pNext;
			}
			else
			{
				break;
			}
		}
	}

	if(RotTrack)
	{
		D3DXQuaternionRotationMatrix(&qRotStart,&m_TransRotMat);
		qRotEnd= RotTrack->m_qrot;
		StartIndex=Nowframe;
		DestIndex=(float)MAXIMUM_INTERPOLATION_FRAME;
	 
		D3DXQuaternionSlerp(&qRot,&qRotStart,&qRotEnd,Nowframe / DestIndex);  
		D3DXMatrixRotationQuaternion(&RotMat,&qRot);
	}
	else
	{
		if(m_pParents)
		{
			RotMat=pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
		}
		else
		{
			RotMat=pTmInfo->m_TmMat;
		}
		RotMat._41=0.0f;RotMat._42=0.0f;RotMat._43=0.0f;RotMat._44=1.0f;

		D3DXQuaternionRotationMatrix(&qRotStart,&m_TransRotMat);
		D3DXQuaternionRotationMatrix(&qRotEnd,&RotMat);

		StartIndex=Nowframe;
		DestIndex=(float)MAXIMUM_INTERPOLATION_FRAME;
		D3DXQuaternionSlerp(&qRot,&qRotStart,&qRotEnd,Nowframe / DestIndex);  
		D3DXMatrixRotationQuaternion(&RotMat,&qRot);
	}

	vPos=m_vTransvec; //지우지마 --;; 삽질할거야 

	if(PosTrack)
	{
		vPosStart=m_vTransvec;
		vPosEnd= PosTrack->m_Pos;

		StartIndex=Nowframe;
		DestIndex=(float)MAXIMUM_INTERPOLATION_FRAME;

		vPos.x+=(vPosEnd.x - vPosStart.x) * (Nowframe / DestIndex);  
		vPos.y+=(vPosEnd.y - vPosStart.y) * (Nowframe / DestIndex);  
		vPos.z+=(vPosEnd.z - vPosStart.z) * (Nowframe / DestIndex);  
	}
	else
	{
		if(m_pParents)
		{
			PosMat=pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
			vPos.x=PosMat._41;
			vPos.y=PosMat._42;
			vPos.z=PosMat._43;
		}
		else
		{
			vPos=pTmInfo->m_TmPos;
		}

		vPosStart=m_vTransvec;
		vPosEnd=vPos;
		StartIndex=Nowframe;
		DestIndex=(float)MAXIMUM_INTERPOLATION_FRAME;
		vPos.x+=(vPosEnd.x - vPosStart.x) * (Nowframe / DestIndex);  
		vPos.y+=(vPosEnd.y - vPosStart.y) * (Nowframe / DestIndex);  
		vPos.z+=(vPosEnd.z - vPosStart.z) * (Nowframe / DestIndex);  

	}

	RotMat._41=vPos.x;
	RotMat._42=vPos.y;
	RotMat._43=vPos.z;
	RotMat._44=1.0f;

	MyAni= RotMat;

	if(m_pParents)
	{
		int a=0;
	}

	D3DXMatrixMultiply(&m_AniMat, &MyAni, &matParents);

	sMeshContainer* Tmp=m_pChild;

	while(Tmp)
	{
		Tmp->m_pData->UpdateTransitionAniTm(pDestAniName,m_AniMat,Nowframe);
		Tmp=Tmp->m_pNext;
	}
}

void cMesh::UpdateAniTm(char *pAniName,D3DXMATRIX matParents,float frame)
{
	static int count=0;
	count++;
	if(count==2)
	{
		int i=1;
	}

	D3DXMATRIX MyAni;
	D3DXMatrixIdentity(&MyAni);

	D3DXMATRIX RotMat;
	D3DXMatrixIdentity(&RotMat);

	D3DXMATRIX PosMat;
	D3DXMatrixIdentity(&PosMat);

	D3DXMATRIX ScaleMat;
	D3DXMatrixIdentity(&ScaleMat);

	D3DXVECTOR3	vPosStart;
	D3DXVECTOR3	vPosEnd;

	D3DXVECTOR3	vPos;
	
	D3DXQUATERNION	qRot;
	D3DXQUATERNION	qRotStart;
	D3DXQUATERNION	qRotEnd;

	D3DXQUATERNION	qAniScale;

	float DestIndex,StartIndex;

	
	//////////////////////////////////////////////////////////////////////
	//	부모가 있다면 계층형 tm= 자신tm*부모역tm						//
	//	계층형 tm으로 만드는 이유는 ani=  에니메이션된 계층tm * 부모	//
	//	이기 때문이다.													//
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////
	//	현재 프레임의 이동 에니 추출		//
	//////////////////////////////////////////
	sAnimation* pAni=m_pAniList;//&m_sAnimation;
	sPos_Track* PosTrack=NULL;//m_sAnimation.GetNowPosTrack(frame);
	sRot_Track* RotTrack=NULL;//;m_sAnimation.GetNowRotTrack(frame);

	cTmInfomation *pTmInfoList=m_pTmInfoList;

	cTmInfomation *pTmInfo=NULL;

	cTmInfomation *pParentsTminfo=NULL;


	while(pTmInfoList)
	{
		if(_stricmp(pAniName, pTmInfoList->m_AniName)==0)
		{
			pTmInfo=pTmInfoList;
			break;
		}
		else
		{
			pTmInfoList=pTmInfoList->m_pNext;
		}
	}

	if(m_pParents)
	{
		pTmInfoList=m_pParents->m_pTmInfoList;

		while(2)
		{
			if(_stricmp(pAniName, pTmInfoList->m_AniName)==0)
			{
				pParentsTminfo=pTmInfoList;
				break;
			}
			else
			{
				pTmInfoList=pTmInfoList->m_pNext;
			}
		}
	}

	while(pAni)
	{
		if(pAni && _stricmp(pAniName, pAni->m_AniName)==0)
		{
			PosTrack=pAni->GetNowPosTrack(frame);
			RotTrack=pAni->GetNowRotTrack(frame);
			break;
		}
		else
		{
			if(pAni->m_pNext)
			{
				pAni=pAni->m_pNext;
			}
			else
			{
				break;
			}
		}
	}


	if(frame > 5800)
	{
		int a=0;
		a++;
	}


	if(RotTrack)
	{
		qRot=RotTrack->m_qrot;

		if(RotTrack->m_pNext)
		{
			 qRotStart=RotTrack->m_qrot;
			 qRotEnd=RotTrack->m_pNext->m_qrot;

			 DestIndex=(float)RotTrack->m_pNext->m_iIndex;
			 StartIndex=(float)RotTrack->m_iIndex;
		}
		else
		{
			qRotStart=RotTrack->m_qrot;
			qRotEnd= pAni->m_Rot->m_qrot;
			StartIndex=(float)RotTrack->m_iIndex;
			DestIndex=(float)StartIndex+ 800.0f;
		} 

		D3DXQuaternionSlerp(&qRot,&qRotStart,&qRotEnd,(float)(frame-StartIndex) / (DestIndex -StartIndex));  
		D3DXMatrixRotationQuaternion(&RotMat,&qRot);

	}
	else
	{
		if(m_pParents)
		{
			if(pTmInfo==NULL)
			{
				RotMat=m_TmMat * m_pParents->m_InvTm;
			}
			else
			{
				RotMat=pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
			}
		}
		else
		{
			if(pTmInfo==NULL)
			{
				RotMat=m_TmMat;
			}
			else
			{
				RotMat=pTmInfo->m_TmMat;
			}
		}
	}

	RotMat._41=0.0f;
	RotMat._42=0.0f;
	RotMat._43=0.0f;
	RotMat._44=1.0f;

	m_TransRotMat=RotMat;	//결과 로트 

	if(PosTrack)
	{
		vPos=PosTrack->m_Pos;
		if(PosTrack->m_pNext)
		{
			vPosStart=PosTrack->m_Pos;
			vPosEnd=PosTrack->m_pNext->m_Pos;

			DestIndex=(float)PosTrack->m_pNext->m_iIndex;
			StartIndex=(float)PosTrack->m_iIndex;
			
			vPos.x+=(vPosEnd.x - vPosStart.x) * (float)(frame-StartIndex) / (DestIndex - StartIndex);  
			vPos.y+=(vPosEnd.y - vPosStart.y) * (float)(frame-StartIndex) / (DestIndex - StartIndex);   
			vPos.z+=(vPosEnd.z - vPosStart.z) * (float)(frame-StartIndex) / (DestIndex - StartIndex);
		}
		else
		{
			vPosStart=PosTrack->m_Pos;
			vPosEnd= pAni->m_Pos->m_Pos;

			StartIndex=(float)PosTrack->m_iIndex;
			DestIndex=(float)StartIndex+ 800.0f;

			vPos.x+=(vPosEnd.x - vPosStart.x) * (float)(frame-StartIndex) / (DestIndex - StartIndex);  
			vPos.y+=(vPosEnd.y - vPosStart.y) * (float)(frame-StartIndex) / (DestIndex - StartIndex);   
			vPos.z+=(vPosEnd.z - vPosStart.z) * (float)(frame-StartIndex) / (DestIndex - StartIndex);
		}
	}
	else
	{
		if(m_pParents)
		{
			if(pTmInfo==NULL)
			{
				PosMat=m_TmMat * m_pParents->m_InvTm;
			}
			else
			{
				PosMat=pTmInfo->m_TmMat * pParentsTminfo->m_InvTm;
			}
			vPos.x=PosMat._41;
			vPos.y=PosMat._42;
			vPos.z=PosMat._43;
		}
		else
		{
			if(pTmInfo==NULL)
			{
				vPos=m_TmPos;
			}
			else
			{
				vPos=pTmInfo->m_TmPos;
			}
		}
	}
	m_vTransvec=vPos;

	RotMat._41=vPos.x;
	RotMat._42=vPos.y;
	RotMat._43=vPos.z;
	RotMat._44=1.0f;


	MyAni= RotMat;

	if(m_pParents)
	{
		int a=0;
	}

	D3DXMatrixMultiply(&m_AniMat, &MyAni, &matParents);

	sMeshContainer* Tmp=m_pChild;

	while(Tmp)
	{
		Tmp->m_pData->UpdateAniTm(pAniName,m_AniMat,frame);
		Tmp=Tmp->m_pNext;
	}

}


//////////////////////////////////
// 텍스쳐						//
//////////////////////////////////

sPos_Track* sAnimation::GetNowPosTrack(float Frame)
{
	sPos_Track* Temp=m_Pos;
	sPos_Track* BeforeTemp=NULL;

	if(!Temp)return NULL;

	if(Temp->m_iIndex > Frame)
	{
		return NULL;
	}

	int iMy_LastIndex=m_Pos->m_iMyLastIndex;
	int iNowAni_LastIndex = m_pNowAniScene->m_LastFrame * m_pNowAniScene->m_TickPerFrame;

	if(iMy_LastIndex < iNowAni_LastIndex)
	{
		if(Frame > iMy_LastIndex)
		{
			while(Temp)
			{
				if(Temp->m_iIndex == iMy_LastIndex)
				{
					return Temp;
				}
				else
				{
					Temp=Temp->m_pNext;
				}
			}
		}
	}

	while(Temp)
	{
		if(Temp->m_iIndex < Frame)
		{
			BeforeTemp=Temp;
			Temp=Temp->m_pNext;	
			continue;
		}
		else
		{
			return BeforeTemp;
		}
	}

	return BeforeTemp;
}

sRot_Track*	sAnimation::GetNowRotTrack(float Frame)
{
	sRot_Track* Temp=m_Rot;
	sRot_Track* BeforeTemp=NULL;

	if(!Temp)return NULL;

	if(Temp->m_iIndex > Frame)
	{
		return NULL;
	}

	int iMy_LastIndex=m_Rot->m_iMyLastIndex;
	int iNowAni_LastIndex = m_pNowAniScene->m_LastFrame * m_pNowAniScene->m_TickPerFrame;

	if(iMy_LastIndex < iNowAni_LastIndex)
	{
		if(Frame > iMy_LastIndex)
		{
			while(Temp)
			{
				if(Temp->m_iIndex == iMy_LastIndex)
				{
					return Temp;
				}
				else
				{
					Temp=Temp->m_pNext;
				}
			}
		}
	}

	while(Temp)
	{
		if(Temp->m_iIndex < Frame)
		{
			BeforeTemp=Temp;
			Temp=Temp->m_pNext;
			continue;
		}
		else
		{
			return BeforeTemp;
		}
	}

	return BeforeTemp;
}

sScale_Track* sAnimation::GetNowScaleTrack(float Frame)
{
	sScale_Track* Temp=m_Scale;	
	
	sScale_Track* BeforeTemp=NULL;
	
	if(!Temp)return NULL;

	if(Temp->m_iIndex < Frame)
	{
		return NULL;
	}

	while(Temp)
	{
		if(Temp->m_iIndex > Frame)
		{
			BeforeTemp=Temp;
			Temp=Temp->m_pNext;
			continue;
		}
		else
		{
			return BeforeTemp;
		}
	}

	return NULL;
}


void sSkinningVertex::MakeLoaclVt(cMesh* pMeshList,cMesh* pBoneList)
{
	cMesh* TempMeshList=pMeshList;
	cMesh* TempBoneList=pBoneList;
	D3DXVECTOR3 vTemp;

	if(m_bBland==true)
	{
		for(int i=0;i<m_NumBlend;i++)
		{
			m_pBlandVt[i].m_pMesh=SearchMesh(pMeshList,m_pBlandVt[i].m_NodeName);

			if(!m_pBlandVt[i].m_pMesh)
			{
				m_pBlandVt[i].m_pMesh=SearchMesh(pBoneList,m_pBlandVt[i].m_NodeName);
			}
			vTemp=*m_pVertex;
			D3DXVec3TransformCoord(&vTemp                         ,&vTemp                      ,&m_pBlandVt[i].m_pMesh->m_InvTm);
			m_pBlandVt[i].m_vBipLocal=vTemp;
		}
	}
	else
	{
		m_pBlandVt->m_pMesh=SearchMesh(pMeshList,m_pBlandVt->m_NodeName);
		if(!m_pBlandVt->m_pMesh)
		{
			m_pBlandVt->m_pMesh=SearchMesh(pBoneList,m_pBlandVt->m_NodeName);
		}
		vTemp=*m_pVertex;
		D3DXVec3TransformCoord(&vTemp,&vTemp,&m_pBlandVt->m_pMesh->m_InvTm);
		m_pBlandVt->m_vBipLocal=vTemp;
	}

}

cMesh* sSkinningVertex::SearchMesh(cMesh* pList,char* Name)
{
	cMesh* tmpMesh;
	tmpMesh=pList;

	while(tmpMesh)
	{
		if(_stricmp(Name, tmpMesh->m_NodeName)==0)
		{
			return tmpMesh;
		}
		tmpMesh=tmpMesh->m_pNext;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////
/// BaseMesh
///////////////////////////////////////////////////////////////
void cBaseMesh::MakeIndex(SMeterial* pMeterial)
{
	if(m_sTvertlist)delete[] m_sTvertlist;

	m_sTvertlist=NULL;

	if(m_ColorList)delete[] m_ColorList;

	m_ColorList=NULL;

	int* Num;

	sViewList* VTemp;
	sViewList* OpacityTemp=NULL;

	if(m_pViewList)delete[] m_pViewList;
	m_pViewList=NULL;

	if(pMeterial[m_iMeterial_Ref].m_iSubMeterialCount>0)	//if(1)
	{
		Num =new int[pMeterial[m_iMeterial_Ref].m_iSubMeterialCount];

		for(int i=0;i<m_iNumFace;i++)
		{
			if(m_sTriangle[i].m_iMeterialID==i && m_sTriangle[i].m_bDraw==true)
			{
				Num[i]++;
			}
		}
		int TriangleNum=0;
		for(int i=0;i<pMeterial[m_iMeterial_Ref].m_iSubMeterialCount;i++)
		{
			if(Num[i]<=0)
				continue;

			VTemp->m_iNumVertex=Num[i]*3;
			VTemp->m_iMaxVertex=Num[i]*3;		
			VTemp->m_pVertex=new SVertex[VTemp->m_iMaxVertex];

			VTemp->m_pIndex=new int[Num[i]];
			VTemp->m_pMeterial=&pMeterial[m_iMeterial_Ref].m_SubMeterial[i];
		
			for(int j=0;j<m_iNumFace;j++)
			{
				if(m_sTriangle[j].m_iMeterialID==i && m_sTriangle[j].m_bDraw==true)
				{
					VTemp->m_pIndex[TriangleNum]=j;
					TriangleNum++;
				}
			}

			if(pMeterial[m_iMeterial_Ref].bUseOpacity==true)
			{
				if(OpacityTemp)
				{
					OpacityTemp->Add(VTemp);
				}
				else
				{
					m_pViewList=VTemp;
				}
			}

			if(OpacityTemp)
			{
				if(m_pViewList)
				{
					m_pViewList->Add(OpacityTemp);
				}
				else
				{
					m_pViewList=OpacityTemp;
				}
			}


		}

		delete[] Num;

	}	//if(1) 현재매쉬의메트리얼에 서브메트리얼이있다면 //끝
	else
	{
			m_pViewList=new sViewList;
			m_pViewList->m_iNumVertex=m_iNumFace;
			m_pViewList->m_iMaxVertex=m_iNumFace;	
			m_pViewList->m_pVertex=new SVertex[m_iNumFace*3];

			m_pViewList->m_pIndex=new int[m_iNumFace];
			m_pViewList->m_pMeterial=&pMeterial[m_iMeterial_Ref];

		for(int i=0;i<m_iNumFace;i++)
		{
			m_pViewList->m_pIndex[i]=i;
		}

	}

}

void cBaseMesh::MakeVertex()
{
	sViewList* VTemp=m_pViewList;

	int k=0;
	int j=0;
	int iii=0;
	while(VTemp)
	{
		k=0;
		VTemp->m_iNumVertex=0;

		for(int i=0;i<VTemp->m_iMaxVertex;i++)
		{
			j=VTemp->m_pIndex[i];

			VTemp->m_pVertex[i*3+0].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_0].v;
			
			VTemp->m_pVertex[i*3+0].nv=m_sTriangle[j].m_vVtNomal[0];

			VTemp->m_pVertex[i*3+0].Diffuse=m_sTriangle[j].VertexColor[0];

			VTemp->m_pVertex[i*3+0].tu=m_sTriangle[j].m_sTverlist[0].tu;
			VTemp->m_pVertex[i*3+0].tv=m_sTriangle[j].m_sTverlist[0].tv;

			VTemp->m_pVertex[i*3+1].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_1].v;
			
			VTemp->m_pVertex[i*3+1].nv=m_sTriangle[j].m_vVtNomal[1];

			VTemp->m_pVertex[i*3+1].Diffuse=m_sTriangle[j].VertexColor[1];

			VTemp->m_pVertex[i*3+1].tu=m_sTriangle[j].m_sTverlist[1].tu;
			VTemp->m_pVertex[i*3+1].tv=m_sTriangle[j].m_sTverlist[1].tv;

			VTemp->m_pVertex[i*3+2].v=m_sVertex[m_sTriangle[j].m_sFaceIndex.m_2].v;

			VTemp->m_pVertex[i*3+2].nv=m_sTriangle[j].m_vVtNomal[2];

			VTemp->m_pVertex[i*3+2].Diffuse=m_sTriangle[j].VertexColor[2];

			VTemp->m_pVertex[i*3+2].tu=m_sTriangle[j].m_sTverlist[2].tu;
			VTemp->m_pVertex[i*3+2].tv=m_sTriangle[j].m_sTverlist[2].tv;

			VTemp->m_iNumVertex++;
		}

		VTemp=VTemp->m_pNext;
	}
}

void cBaseMesh::AddChild(cBaseMesh* pMesh)
{
	sBaseMeshContainer *pTmp;

	pTmp=new sBaseMeshContainer;
	pTmp->m_pData=pMesh;

	if(m_pChild==NULL)
	{
		m_pChild=pTmp;
	}
	else
	{
		m_pChild->Add(pTmp);
	}
}

void cBaseMesh::Render(D3DXMATRIX WorldTm)
{
	D3DXMATRIX LocalTm=m_TmMat;
	//D3DXMatrixIdentity(&LocalTm);

	WorldTm=LocalTm * WorldTm;

	m_pd3dDevice->SetTransform(D3DTS_WORLD,&WorldTm);

	sViewList* ViewList;
	ViewList = m_pViewList;

	//-------------- 메시 리스트에서 출력 ------------------
	while(ViewList)
	{
		if(ViewList->m_iNumVertex>0)
		{
			// step2
            // 텍스쳐 설정 
			if(ViewList->m_pMeterial->bUseTexture)
				m_pd3dDevice->SetTexture(0, ViewList->m_pMeterial->m_pTexture );
			else
				m_pd3dDevice->SetMaterial(&(ViewList->m_pMeterial->m_d3dMaterial));	
			
			// 재질 설정
	        m_pd3dDevice->SetMaterial(&(ViewList->m_pMeterial->m_d3dMaterial));	
			
			// 알파 설정 
			if(ViewList->m_pMeterial->bUseOpacity)			
				Alpha(true);

			//----------------- 비 정점 방식으로 ---------------------		
			// 랜더
			m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 
				ViewList->m_iNumVertex, ViewList->m_pVertex, sizeof(SVertex));
		
			if(ViewList->m_pMeterial->bUseOpacity)
				Alpha(false);
		}
		ViewList = ViewList->m_pNext;
	}
}

void cBaseMesh::Alpha(bool flag)
{
	if(flag)
	{
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
		
		m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
		

		
		m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE); 
		m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
		m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ;     
		m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE);
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	}
	else
	{
		m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW); 
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , FALSE );
		m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
		m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);

	}
}


///////////////////////////////////////////////////////////////
/// BaseAse
///////////////////////////////////////////////////////////////
void cBaseAse::JumpFIlePointer(int Num,FILE *pf)
{
	for(int i=0;i<Num;i++)
	{
		while(1)
		{
			fgets(m_line, 256, pf); 
			sscanf( m_line , "%s", m_str);

			if(_stricmp("}", m_str)==0)
			break;
			
		}
	}
}

void cBaseAse::MakeFaceNormalFromWorldVertex(){}
void cBaseAse::MakeVertexNormalFromFaceNormal(){}


HRESULT cBaseAse::LoadAse(char *FileName)
{
	FILE* pf=::fopen(FileName,"rt");

	if(pf==NULL)
	{
		return E_FAIL;
	}

	fgets(m_line, 256, pf); 

	sscanf( m_line , "%s", m_str);
	
	if(_stricmp("*3DSMAX_ASCIIEXPORT", m_str)!=0)
		{
			return E_FAIL;
		}
	

	while(!feof(pf))
	{
		fgets(m_line, 256, pf); 

		sscanf( m_line , "%s", m_str);
		
		if(_stricmp("*SCENE", m_str)==0)
		{
			JumpFIlePointer(1,pf);
			continue;
		}

		if(_stricmp("*MATERIAL_LIST", m_str)==0)
		{
			ReadMATERIAL_LIST(pf);
			continue;
		}

		if(_stricmp("*GEOMOBJECT", m_str)==0)
		{
			cBaseMesh*	TmpMesh=new cBaseMesh();

			TmpMesh->SetDevice(m_pd3dDevice);

			m_pNowMesh=TmpMesh;

			ReadGEOMOBJECT(pf);

			AddMesh(m_pNowMesh);
			continue;
		}
	}

	fclose(pf);
	

	if(m_NormalFlag==false)
	{
		MakeFaceNormalFromWorldVertex();
		MakeVertexNormalFromFaceNormal();
	}

	MakeInherite();

	SetAllMesh();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	m_pNowMesh=m_pMeshList;

	while(m_pNowMesh)
	{
		m_pNowMesh->MakeIndex(m_Meterial);
		m_pNowMesh->MakeVertex();
		m_pNowMesh=m_pNowMesh->m_pNext;
	}

	m_pTextureContainer=new CTextureContainer;
	LoadAseTexture();

	return S_OK;
}


void cBaseAse::ReadMATERIAL_LIST(FILE *pf)
{
	int Mtrcount=0;
	while(1)
	{
		fgets(m_line, 256, pf); 

		sscanf( m_line , "%s", m_str);
		
		if(_stricmp("*MATERIAL_COUNT", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&m_iNumMaterial);

			m_Meterial= new SMeterial[m_iNumMaterial];
			continue;
		}

		if(_stricmp("*MATERIAL", m_str)==0)
		{
			ReadMATERIAL(pf,&m_Meterial[Mtrcount]);
			Mtrcount++;
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

}

void cBaseAse::ReadMATERIAL(FILE *pf,SMeterial* pNowMeterial)
{
	int num;
	
	ZeroMemory( &pNowMeterial->m_d3dMaterial, sizeof(D3DMATERIAL9) );
	pNowMeterial->m_d3dMaterial.Diffuse.r = pNowMeterial->m_d3dMaterial.Ambient.r = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.g = pNowMeterial->m_d3dMaterial.Ambient.g = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.b = pNowMeterial->m_d3dMaterial.Ambient.b = 0;
	pNowMeterial->m_d3dMaterial.Diffuse.a = pNowMeterial->m_d3dMaterial.Ambient.a = 1;


	while(2)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*NUMSUBMTLS", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&pNowMeterial->m_iSubMeterialCount);

			pNowMeterial->m_SubMeterial=new SMeterial[pNowMeterial->m_iSubMeterialCount];
			continue;
		}

		if(_stricmp("*SUBMATERIAL", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&num);
			ReadMATERIAL(pf,&pNowMeterial->m_SubMeterial[num]);
			continue;
		}

		if(_stricmp("*MATERIAL_AMBIENT", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Ambient.r,
				&pNowMeterial->m_d3dMaterial.Ambient.g,
				&pNowMeterial->m_d3dMaterial.Ambient.b);
			continue;
		}

		if(_stricmp("*MATERIAL_DIFFUSE", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Diffuse.r,
				&pNowMeterial->m_d3dMaterial.Diffuse.g,
				&pNowMeterial->m_d3dMaterial.Diffuse.b);
			continue;
		}

		if(_stricmp("*MATERIAL_SPECULAR", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f", m_str,
				&pNowMeterial->m_d3dMaterial.Specular.r,
				&pNowMeterial->m_d3dMaterial.Specular.g,
				&pNowMeterial->m_d3dMaterial.Specular.b);
			continue;
		}

		if(_stricmp("*MAP_DIFFUSE", m_str)==0)
		{
			pNowMeterial->bUseTexture=true;
			// 텍스쳐 불러오기 
			ReadMtrTextureName(pf,pNowMeterial);
			continue;
		}

		if(_stricmp("*MAP_OPACITY", m_str)==0)
		{
			pNowMeterial->bUseTexture=true;
			pNowMeterial->bUseOpacity=true;
			ReadMtrTextureName(pf,pNowMeterial);
			//텍스쳐 불러오기
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

}

void cBaseAse::ReadMtrTextureName(FILE *pf,SMeterial *pNowMeterial)
{
	int Start=0,End=0;
	bool Check=false;
	int Count=0;


	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*BITMAP", m_str)==0)
		{
			while(2)
			{
				if(m_line[Count]=='"')
				{
					if(Check)
					{
						End=Count-1;
						break;
					}
					else
					{
						Check=true;
						Start=Count+1;
					}
				}
				Count++;
			}
			int i=Start;
			int j=0;
			for(;i<=End;i++,j++)
				{
					pNowMeterial->m_TextuerFileName[j]=m_line[i];
				}
				pNowMeterial->m_TextuerFileName[j]=NULL;
		}

		if(_stricmp("}", m_str)==0)
		{
			break;
		}

	}

}

void cBaseAse::ReadGEOMOBJECT(FILE *pf)
{
	char tmpstr[256];

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*NODE_NAME", m_str)==0)		
		{
			ReadFileName(m_line,m_pNowMesh->m_NodeName);
			continue;
		}

		if(_stricmp("*NODE_PARENT", m_str)==0)
		{
			ReadFileName(m_line,m_pNowMesh->m_parentsName);
			m_pNowMesh->m_bParents=true;
			continue;
		}

		if(_stricmp("*NODE_TM", m_str)==0)
		{
			ReadTM(pf);
			continue;
		}	

		if(_stricmp("*MESH", m_str)==0)
		{
			ReadMESH(pf);
			continue;
		}

		if(_stricmp("*MATERIAL_REF", m_str)==0)
		{
			sscanf( m_line , "%s %d", m_str,&m_pNowMesh->m_iMeterial_Ref);
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}

	
}

void cBaseAse::ReadTM(FILE *pf)
{
	D3DXMatrixIdentity(&m_pNowMesh->m_TmMat);

	float fX,fY,fZ,fW;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*TM_ROW0", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._11,
				&m_pNowMesh->m_TmMat._13,
				&m_pNowMesh->m_TmMat._12);
			continue;
		}

		if(_stricmp("*TM_ROW1", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._31,
				&m_pNowMesh->m_TmMat._33,
				&m_pNowMesh->m_TmMat._32);
			continue;
		}

		if(_stricmp("*TM_ROW2", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._21,
				&m_pNowMesh->m_TmMat._23,
				&m_pNowMesh->m_TmMat._22);
			continue;
		}

		if(_stricmp("*TM_ROW3", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmMat._41,
				&m_pNowMesh->m_TmMat._43,
				&m_pNowMesh->m_TmMat._42);
			continue;
		}

		if(_stricmp("*TM_POS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmPos.x,
				&m_pNowMesh->m_TmPos.z,
				&m_pNowMesh->m_TmPos.y);
			continue;
		}

		if(_stricmp("*TM_ROTAXIS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}
		if(_stricmp("*TM_ROTANGLE", m_str)==0)
		{
			sscanf( m_line , "%s %f",m_str,&fW);

			m_pNowMesh->m_TmRot.x=(float)sinf(fW/2.0f) *fX;
			m_pNowMesh->m_TmRot.y=(float)sinf(fW/2.0f) *fY;
			m_pNowMesh->m_TmRot.z=(float)sinf(fW/2.0f) *fZ;
			m_pNowMesh->m_TmRot.w=(float)cosf(fW/2.0f);

			continue;
		}

		if(_stricmp("*TM_SCALE", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&m_pNowMesh->m_TmScale.x,
				&m_pNowMesh->m_TmScale.z,
				&m_pNowMesh->m_TmScale.y);
			continue;
		}
		if(_stricmp("*TM_SCALEAXIS", m_str)==0)
		{
			sscanf( m_line , "%s %f %f %f",m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}

		if(_stricmp("*TM_SCALEAXISANG", m_str)==0)
		{
			sscanf( m_line , "%s %f",m_str,&fW);
			m_pNowMesh->m_TmScaleRot.x=(float)sinf(fW/2.0f) *fX;
			m_pNowMesh->m_TmScaleRot.y=(float)sinf(fW/2.0f) *fY;
			m_pNowMesh->m_TmScaleRot.z=(float)sinf(fW/2.0f) *fZ;
			m_pNowMesh->m_TmScaleRot.w=(float)cosf(fW/2.0f);
			continue;
		}

		if(_stricmp("}", m_str)==0)
		{
			D3DXMatrixInverse(&m_pNowMesh->m_InvTm,NULL,&m_pNowMesh->m_TmMat);
			break;
		}
	}
}

void cBaseAse::ReadMESH(FILE *pf)
{
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_NUMVERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumVertex);
			m_pNowMesh->m_sVertex=new SVertex[m_pNowMesh->m_iNumVertex];

			continue;
		}

		if(_stricmp("*MESH_NUMFACES", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumFace);
			m_pNowMesh->m_sTriangle=new STriangle[m_pNowMesh->m_iNumFace];

			for(int i=0;i<m_pNowMesh->m_iNumFace;i++)
			{
				m_pNowMesh->m_sTriangle[i].Init();
			}
			continue;
		}

		if(_stricmp("*MESH_VERTEX_LIST", m_str)==0)
		{
			ReadMESH_VERTEX_LIST(pf);

			continue;
		}

		if(_stricmp("*MESH_FACE_LIST", m_str)==0)
		{
			ReadMESH_FACE_LIST(pf);

			continue;
		}

		if(_stricmp("*MESH_NUMTVERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNumTvVertex);

			m_pNowMesh->m_sTvertlist=new STvertlist[m_pNowMesh->m_iNumTvVertex];

			continue;
		}

		if(_stricmp("*MESH_TVERTLIST", m_str)==0)
		{
			ReadMESH_TVERTLIST(pf);

			continue;
		}

		if(_stricmp("*MESH_NUMTVFACES", m_str)==0)
		{
			sscanf( m_line , "%s %d",m_str,&m_pNowMesh->m_iNUMTVFACES);

			continue;
		}

		if(_stricmp("*MESH_TFACELIST", m_str)==0)
		{
			ReadMESH_TFACELIST(pf);

			continue;
		}

		if ( _stricmp("*MESH_NUMCVERTEX",m_str ) == 0)
		{
			ReadMESH_CVERTEX(pf);///////////////////////////////////////
			continue;
		}
		if(_stricmp("*MESH_NUMCVFACES",m_str)==0)//*MESH_NUMCVERTEX
		{
			ReadMESH_CFACELIST(pf);////////////////////////////////////
			continue;
		}

		if(_stricmp("*MESH_NORMALS", m_str)==0)
		{
			ReadMESH_NORMALS(pf);
			continue;
		}

		if(_stricmp("}", m_str)==0)
			break;
	}
}

void cBaseAse::ReadMESH_VERTEX_LIST(FILE *pf)
{
	int iNum;
	D3DXVECTOR3 vtemp(0,0,0);
	float x,y,z;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_VERTEX", m_str)==0)
		{
			sscanf( m_line , "%s %d %f %f %f",m_str,&iNum,&vtemp.x,&vtemp.z,&vtemp.y);
			m_pNowMesh->m_sVertex[iNum].v=vtemp;
		}
		if(_stricmp("}", m_str)==0)
		{break;}
	}

}
void cBaseAse::ReadMESH_FACE_LIST(FILE *pf)
{
	int iCount=0,tmp=0;
	DWORD Face_0,Face_1,Face_2;
	char Smooth[20];
	char MaterID[20];
	int ID;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		memset(MaterID, 0, 20);
		memset(Smooth, 0, 20);

		if(_stricmp("*MESH_FACE", m_str)==0)
		{
			sscanf(m_line, "%s%s %s%d %s%d %s%d %s%d %s%d %s%d %s%s %s%d",m_str,m_str,
				m_str,&Face_0,
				m_str,&Face_1,
				m_str,&Face_2,
				m_str,&tmp,
				m_str,&tmp,
				m_str,&tmp,
				m_str,Smooth,
				MaterID,&ID
				);
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_0=Face_0;
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_1=Face_2;
			m_pNowMesh->m_sTriangle[iCount].m_sFaceIndex.m_2=Face_1;

			if(_strcmpi(MaterID,"*MESH_MTLID")==0)
			{
				m_pNowMesh->m_sTriangle[iCount].m_iMeterialID = ID;
			}
			if(_strcmpi(Smooth,"*MESH_MTLID")==0)
			{
				m_pNowMesh->m_sTriangle[iCount].m_iMeterialID = atoi(MaterID);
			}
			iCount++;
		}
		
		if(_stricmp("}", m_str)==0)
		{break;}
	}
}

void cBaseAse::ReadMESH_TVERTLIST(FILE *pf)
{
	if(m_pNowMesh->m_iNumTvVertex <=0)
	{
		return;
	}

	int iNum=0,tmp=0;
	float tu,tv,tw;
	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_TVERT", m_str)==0)
		{
			sscanf(m_line, "%s %d %f %f %f",m_str,&tmp, &tu,&tv,&tw );
			m_pNowMesh->m_sTvertlist[iNum].tu=tu;
			m_pNowMesh->m_sTvertlist[iNum].tv=1.0f-tv;
			iNum++;
		}
		if(_stricmp("}", m_str)==0)
		{break;}
	}

}

void cBaseAse::ReadMESH_TFACELIST(FILE *pf)
{
	if(m_pNowMesh->m_iNUMTVFACES <=0)
	{
		return;
	}

	int iCount=0,tmp=0;
	int Tvindex[3];

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		if(_stricmp("*MESH_TFACE", m_str)==0)
		{
			sscanf(m_line, "%s %d %d %d %d",m_str,&tmp, &Tvindex[0],&Tvindex[2],&Tvindex[1] );
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[0].tu=m_pNowMesh->m_sTvertlist[Tvindex[0]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[0].tv=m_pNowMesh->m_sTvertlist[Tvindex[0]].tv;

			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[1].tu=m_pNowMesh->m_sTvertlist[Tvindex[1]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[1].tv=m_pNowMesh->m_sTvertlist[Tvindex[1]].tv;

			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[2].tu=m_pNowMesh->m_sTvertlist[Tvindex[2]].tu;
			m_pNowMesh->m_sTriangle[iCount].m_sTverlist[2].tv=m_pNowMesh->m_sTvertlist[Tvindex[2]].tv;

			iCount++;
		}

		if(_stricmp("}", m_str)==0)
		{break;}
	}

}

void cBaseAse::ReadMESH_CVERTEX(FILE *pf)
{
	sscanf(m_line,"%s %d",m_str, &m_pNowMesh->m_iNumColorVt);

	if(m_pNowMesh->m_iNumColorVt <= 0)return;

	m_pNowMesh->m_ColorList= new D3DXCOLOR[m_pNowMesh->m_iNumColorVt];

	int iNum;

	float r,g,b;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		sscanf(m_line,"%s %d%f%f%f", m_str, &iNum, &r, &g, &b);

		m_pNowMesh->m_ColorList[iNum].r=r;
		m_pNowMesh->m_ColorList[iNum].g=g;
		m_pNowMesh->m_ColorList[iNum].b=b;
		m_pNowMesh->m_ColorList[iNum].a=1.0f;

		if(_stricmp("}", m_str)==0)
		{break;}
	}

}
void cBaseAse::ReadMESH_CFACELIST(FILE *pf)
{
	sscanf(m_line,"%s %d",m_str, &m_pNowMesh->m_iNumColorFace);
	if(m_pNowMesh->m_iNumColorFace <= 0)return;

	BYTE R0, G0, B0, A0;
	int i,num;

	int facenum, v1, v2, v3;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line , "%s", m_str);

		sscanf(m_line,"%s %d %d %d %d",m_str, &facenum, &v1, &v3, &v2);
		R0 = (BYTE)(m_pNowMesh->m_ColorList[v1].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v1].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v1].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v1].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[0] = D3DCOLOR_XRGB(R0,G0,B0);

		R0 = (BYTE)(m_pNowMesh->m_ColorList[v2].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v2].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v2].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v2].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[1] = D3DCOLOR_XRGB(R0,G0,B0);

		R0 = (BYTE)(m_pNowMesh->m_ColorList[v3].r*255.0f);
		G0 = (BYTE)(m_pNowMesh->m_ColorList[v3].g*255.0f);
		B0 = (BYTE)(m_pNowMesh->m_ColorList[v3].b*255.0f);
		A0 = (BYTE)(m_pNowMesh->m_ColorList[v3].a*255.0f);
		m_pNowMesh->m_sTriangle[facenum].VertexColor[2] = D3DCOLOR_XRGB(R0,G0,B0);


		if(_stricmp("}", m_str)==0)
		{break;}
	}
}




void cBaseAse::ReadMESH_NORMALS(FILE *pf)
{

	int iCount=0,iNum=0;

	float x=0.0f,y=0.0f,z=0.0f;

	m_NormalFlag=true;

	while(1)
	{
		fgets(m_line, 256, pf); 
		sscanf( m_line ,"%s", m_str);

		if(_stricmp("*MESH_FACENORMAL", m_str)==0)
		{
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum, &x, &z, &y );

			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vFaceNomal.z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[0].z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[2].z=z;

			fgets(m_line, 256, pf); //*MESH_VERTEXNORMAL
			sscanf(m_line, "%s%d%f%f%f",m_str,&iNum,&x,&z,&y );

			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].x=x;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].y=y;
			m_pNowMesh->m_sTriangle[iCount].m_vVtNomal[1].z=z;

			iCount++;
		}

		if(_stricmp("}", m_str)==0)
		{break;}

	}

}

void cBaseAse::AddMesh(cBaseMesh *pNowMesh)
{
	cBaseMesh *tmpMesh;

	if(!m_pMeshList)
	{
		m_pMeshList=pNowMesh;
	}
	else
	{
		tmpMesh=m_pMeshList;
		while(tmpMesh)
		{
			if(tmpMesh->m_pNext==NULL)
			{
				tmpMesh->m_pNext=pNowMesh;
				break;
			}
			else
			{
				tmpMesh=tmpMesh->m_pNext;
			}
		}

	}

}

void cBaseAse::MakeInherite()
{
	cBaseMesh *Child;
	cBaseMesh *Parents;

	Child=m_pMeshList;

	while(Child)
	{
		if(Child->m_bParents)
		{
			Parents=Search(Child->m_parentsName);
			if(Parents)
			{
				Child->m_pParents=Parents;
				Parents->AddChild(Child);
			}
		}
		
		Child=Child->m_pNext;
	}
}

void cBaseAse::SetAllMesh()
{
	cBaseMesh *pNowMesh;

	pNowMesh=m_pMeshList;

	D3DXMATRIXA16 mat;

	D3DXVECTOR3 vTmp1,vTmp2;

	while(pNowMesh)
	{
		for(int i=0;i<pNowMesh->m_iNumVertex;i++)
		{
			vTmp1=pNowMesh->m_sVertex[i].v;

			D3DXVec3TransformCoord(&vTmp2,&vTmp1,&pNowMesh->m_InvTm);

			pNowMesh->m_sVertex[i].v=vTmp2;
		}

		pNowMesh=pNowMesh->m_pNext;
	}
}

cBaseMesh* cBaseAse::Search(char* Name)
{
	cBaseMesh* tmpMesh;
	tmpMesh=m_pMeshList;

	while(tmpMesh)
	{
		if(_stricmp(Name, tmpMesh->m_NodeName)==0)
		{
			return tmpMesh;
		}
		tmpMesh=tmpMesh->m_pNext;
	}
	return NULL;
}

void cBaseAse::RenderAse(D3DXMATRIX Scalemat,D3DXMATRIX Rotmat,D3DXMATRIX Posmat)
{
	D3DXMATRIX WorldMat;
	D3DXMatrixIdentity(&WorldMat);

	DWORD dwfvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE  |D3DFVF_TEX1 ;
	DWORD fvfsize = D3DXGetFVFVertexSize(dwfvf);

	// 정점 타입 설정 
	m_pd3dDevice->SetFVF( dwfvf );
	
	
		// 정점의 월드 행렬 반영
	
	WorldMat=Scalemat*Rotmat*Posmat;

	cBaseMesh* pMeshList=m_pMeshList;

	while(pMeshList)
	{
		pMeshList->Render(WorldMat);
		pMeshList=pMeshList->m_pNext;
	}
}

void cBaseAse::ReadFileName(char* Src,char *Dest)
{
	int Count=0;
	int Start=0;
	int End=0;

	bool Check=false;


	if(Src==NULL || Dest==NULL)
	{
		return;
	}

	while(2)
	{
		if(Src[Count]=='"')
		{
			if(Check)
			{
				End=Count-1;
				break;
			}
			else
			{
				Check=true;
				Start=Count+1;
			}
		}
		Count++;
	}

	int i=Start;
	int j=0;

	for(;i<=End;i++,j++)
	{
		Dest[j]=Src[i];
	}

	Dest[j]=NULL;

}


void cBaseAse::LoadAseTexture()
{
	STextureList* Temp;

	for(int i=0; i<m_iNumMaterial; i++)
	{
		if(m_Meterial[i].bUseTexture)
		{
			m_Meterial[i].m_pTextureContainer = m_pTextureContainer;

			Temp = m_pTextureContainer->LoadTexture(m_pd3dDevice, 
				m_Meterial[i].m_TextuerFileName);
			if(Temp)
				m_Meterial[i].m_pTexture = Temp->m_pTexture;
			else
				m_Meterial[i].m_pTexture = NULL;

		}
		for(int j=0; j<m_Meterial[i].m_iSubMeterialCount; j++)
		{
			if(m_Meterial[i].m_SubMeterial[j].bUseTexture)
			{
				m_Meterial[i].m_SubMeterial[j].m_pTextureContainer = m_pTextureContainer;

				Temp = m_pTextureContainer->LoadTexture(m_pd3dDevice,
					m_Meterial[i].m_SubMeterial[j].m_TextuerFileName);
				if(Temp)
					m_Meterial[i].m_SubMeterial[j].m_pTexture = Temp->m_pTexture;
				else
					m_Meterial[i].m_SubMeterial[j].m_pTexture = NULL;

			}
		}
	}

}
//_CrtDumpMemoryLeaks();
