#include "header.h"
CASE::CASE(LPDIRECT3DDEVICE9 pdev)
{
	m_AniTime=new CAniTime;
	m_pd3dDevice=pdev;
	m_Scene=new CScene;
}
CASE::~CASE()
{
	Cleanup();
}

void CASE::Cleanup()
{
	vector<CMaterial*>::iterator iter;
	for(iter=m_MaterialList.begin();iter !=m_MaterialList.end();iter++)
	{
		delete (*iter);
	}
	m_MaterialList.clear();

	vector<CGeom*>::iterator iter1;
	for(iter1=m_GeomList.begin();iter1 !=m_GeomList.end();iter1++)
	{
		delete (*iter1);
	}
	m_GeomList.clear();

	SAFE_DELETE(m_AniTime);
	SAFE_DELETE(m_Scene);
}
void
CASE::StartUpdate(D3DXMATRIX matWorld,float dt)
{
	m_AniTime->Update(dt);
	vector<CGeom*>::iterator iter;
	vector<CGeom*>::iterator iter2;
	for(iter=m_GeomList.begin();iter!=m_GeomList.end();iter++)
	{
		if((*iter)->m_ParentsGeom==NULL)
		{
			for(iter2=(*iter)->m_ChildList.begin();iter2!=(*iter)->m_ChildList.end();iter2++)
			{
				(*iter2)->UpdateAni(matWorld,m_AniTime->GetDT());
			}
		}
	}
}
bool CGeom::GetPosTrack(float frame,D3DXVECTOR3* Pos)
{
	if(m_PosTrackList.size()==0)
		return false;
	vector<CPosTrack*>::iterator iter;
	for(iter=m_PosTrackList.begin();iter!=m_PosTrackList.end()-1;iter++)
	{
		if((*iter)->m_Time<=frame&&(*(iter+1))->m_Time>=frame)
		{
			float ap=(frame-(*iter)->m_Time)/((*(iter+1))->m_Time-(*iter)->m_Time);
			D3DXVec3Lerp(Pos,&(*iter)->m_Pos,&(*(iter+1))->m_Pos,ap);
			/*Pos->x=(1.0f-ap)*(*iter)->m_Pos.x+ap*(*(iter+1))->m_Pos.x;
			Pos->y=(1.0f-ap)*(*iter)->m_Pos.y+ap*(*(iter+1))->m_Pos.y;
			Pos->z=(1.0f-ap)*(*iter)->m_Pos.z+ap*(*(iter+1))->m_Pos.z;*/
			return true;
		}
	}
	return false;

}
bool CGeom::GetRotTrack(float frame,D3DXQUATERNION* qr)
{
	int temp=m_RotTrackList.size();
	if(temp==0)
		return false;
	vector<CRotTrack*>::iterator iter;
	for(iter=m_RotTrackList.begin();iter!=m_RotTrackList.end()-1;iter++)
	{
		if((*iter)->m_Time<=frame&&(*(iter+1))->m_Time>=frame)
		{
			float ap=(frame-(*iter)->m_Time)/((*(iter+1))->m_Time-(*iter)->m_Time);
			D3DXQuaternionSlerp(qr,&(*iter)->m_Rot,&(*(iter+1))->m_Rot,ap);
			/*qr->x=(1.0f-ap)*(*iter)->m_Rot.x+ap*(*(iter+1))->m_Rot.x;
			qr->y=(1.0f-ap)*(*iter)->m_Rot.y+ap*(*(iter+1))->m_Rot.y;
			qr->z=(1.0f-ap)*(*iter)->m_Rot.z+ap*(*(iter+1))->m_Rot.z;
			qr->w=(1.0f-ap)*(*iter)->m_Rot.w+ap*(*(iter+1))->m_Rot.w;*/
			return true;
		}
	}
	return false;


}
void CASE::Init()
{
	vector<CGeom*>::iterator iter;
	for(iter=m_GeomList.begin();iter!=m_GeomList.end();iter++)
	{
		(*iter)->MakeVertexBuffer();
		//(*iter)->MakeIndexBuffer();
	}
	vector<CMaterial*>::iterator iter2;
	for(iter2=m_MaterialList.begin();iter2!=m_MaterialList.end();iter2++)
	{
		(*iter2)->CreateTexture();
		//(*iter2)->SetMaterial();
	}
	m_AniTime->Init(m_Scene->m_FirstFrame,m_Scene->m_LastFrame,m_Scene->m_TickPerFrame);
}
void
CASE::Render()
{
	vector<CGeom*>::iterator iter;
	for(iter=m_GeomList.begin();iter!=m_GeomList.end();iter++)
	{
		if((*iter)->Type==MESH)
		{
			m_MaterialList[(*iter)->m_Materialref]->SetTexture();
			m_MaterialList[(*iter)->m_Materialref]->SetMaterial();
			(*iter)->Render();
		}
	}

}
HRESULT CASE::ReadASE(char* filename)
{
	FILE* fp;
	fp=fopen(filename,"rt");
	if(fp==NULL)
		return E_FAIL;
	m_LineCount=0;

	if(FAILED(DecodeASE(fp)))
		return E_FAIL;
	fclose(fp);
	return S_OK;

}
HRESULT CASE::DecodeSCENE(FILE *fp)
{
	float temp;	
	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s%f",m_TempString,&temp);

		if(_stricmp(m_TempString,"*SCENE_FIRSTFRAME")==0)
			m_Scene->m_FirstFrame=temp;
		
		if(_stricmp(m_TempString,"*SCENE_LASTFRAME")==0)
			m_Scene->m_LastFrame=temp;

		if(_stricmp(m_TempString,"*SCENE_FRAMESPEED")==0)
			m_Scene->m_FrameSpeed=temp;

		if(_stricmp(m_TempString,"*SCENE_TICKSPERFRAME")==0)
			m_Scene->m_TickPerFrame=temp;

		if(_stricmp(m_TempString, "}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}
	}
	return S_OK;
}

HRESULT CASE::DecodeMATERIAL(FILE* fp,CMaterial* Material)
{
	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);

		if(_stricmp(m_TempString,"*MATERIAL_AMBIENT")==0)
		{
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Material->m_Ambient.x,&Material->m_Ambient.y,&Material->m_Ambient.z);
			//Material->m_Ambient=D3DXCOLOR(temp1,temp2,temp3,1.0f);	
		}
		if(_stricmp(m_TempString,"*MATERIAL_DIFFUSE")==0)
		{
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Material->m_Diffuse.x,&Material->m_Diffuse.y,&Material->m_Diffuse.z);
			//Material->m_Diffuse=D3DXCOLOR(temp1,temp2,temp3,1.0f);
		}
		if(_stricmp(m_TempString,"*MATERIAL_SPECULAR")==0)
		{
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Material->m_Specular.x,&Material->m_Specular.y,&Material->m_Specular.z);
			//Material->m_Specular=D3DXCOLOR(temp1,temp2,temp3,1.0f);
		}
		if(_stricmp(m_TempString,"*BITMAP")==0)
		{
			bool check=false;
			
			for(int i=0;i<255;i++)
			{
				if(check)
				{
					if(m_TempLine[i]=='\"')
						break;
					else 
					{
						Material->m_TextureName.push_back(m_TempLine[i]);
					}
				}
				if(m_TempLine[i]=='\"')check = true;
			}
			
		}
		if(_stricmp(m_TempString,"}")==0)
		{
			m_LineCount++;
			fgets(m_TempLine,256,fp);
			sscanf(m_TempLine,"%s",m_TempString);
			if(_stricmp(m_TempString,"}")==0)
			{
				strcpy(m_TempString,"sungchul");
				break;
			}
		}
	}
	return S_OK;
}
HRESULT CASE::DecodeMATERIALLIST(FILE* fp)
{
	int MaterialCount,num=0;
	m_LineCount++;
	fgets(m_TempLine,256,fp);
	sscanf(m_TempLine,"%s",m_TempString,&MaterialCount);

	if(_stricmp(m_TempString,"*MATERIAL_COUNT")==0)
	{
		sscanf(m_TempLine,"%s",m_TempString,&MaterialCount);
	}

	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*MATERIAL")==0)
		{
			CMaterial* Material=new CMaterial(m_pd3dDevice);

			DecodeMATERIAL(fp,Material);
			m_MaterialList.push_back(Material);
			num++;
		}

		if(_stricmp(m_TempString,"}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}
	}
	return S_OK;
}

HRESULT 
CASE::DecodeMESH(FILE* fp,ASEMesh* mesh)
{
	int temp;
	D3DXVECTOR3 tempVec;
	D3DXVECTOR2 tempVec2;
	MYINDEX		tempIndex;
	ZeroMemory(&tempIndex,sizeof(MYINDEX));

	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*MESH_NUMVERTEX")==0)
			sscanf(m_TempLine,"%s%d",m_TempString,&mesh->m_NumVertex);
		if(_stricmp(m_TempString,"*MESH_NUMFACES")==0)
			sscanf(m_TempLine,"%s%d",m_TempString,&mesh->m_NumIndex);
		if(_stricmp(m_TempString,"*MESH_VERTEX_LIST")==0)
		{
			while(1)
			{
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*MESH_VERTEX")==0)
				{
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&temp,&tempVec.x,&tempVec.z,&tempVec.y);
					mesh->m_VertexList.push_back(tempVec);
				}
				
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}
			}
		}
		if(_stricmp(m_TempString,"*MESH_FACE_LIST")==0)
		{
			while(1)
			{
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*MESH_FACE")==0)
				{
					sscanf(m_TempLine,"%s%s%s%d%s%d%s%d",m_TempString,m_TempString,m_TempString
						,&tempIndex._0,m_TempString,&tempIndex._2,m_TempString,&tempIndex._1);
					mesh->m_IndexList.push_back(tempIndex);
				}
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}

			}
		}
		if(_stricmp(m_TempString,"*MESH_TVERTLIST")==0)
		{
			
			while(1)
			{
				float addf;
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*MESH_TVERT")==0)
				{
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&temp,&tempVec2.x,&tempVec2.y,&addf);
					tempVec2.y=1-tempVec2.y;
					mesh->m_TextureVertexList.push_back(tempVec2);
				}
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}

			}
		}
		if(_stricmp(m_TempString,"*MESH_TFACELIST")==0)
		{
			while(1)
			{
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*MESH_TFACE")==0)
				{
					sscanf(m_TempLine,"%s%d%d%d%d",m_TempString,&temp,&tempIndex._0,&tempIndex._2,&tempIndex._1);
					mesh->m_TextureFaceList.push_back(tempIndex);
				}
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}

			}
		}
		if(_stricmp(m_TempString,"*MESH_NORMALS")==0)
		{
			
			while(1)
			{
				
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*MESH_FACENORMAL")==0)
				{
					CNormal* Normal=new CNormal;
					int temp;
					
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&temp,&Normal->m_FaceNormal.x,&Normal->m_FaceNormal.z,&Normal->m_FaceNormal.y);
				
					m_LineCount++;
					fgets(m_TempLine,256,fp);
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&Normal->m_NormalIndex[0],&Normal->m_VertexNormal[0].x,&Normal->m_VertexNormal[0].z,&Normal->m_VertexNormal[0].y);
                    
					m_LineCount++;
					fgets(m_TempLine,256,fp);
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&Normal->m_NormalIndex[1],&Normal->m_VertexNormal[1].x,&Normal->m_VertexNormal[1].z,&Normal->m_VertexNormal[1].y);
					
					m_LineCount++;
					fgets(m_TempLine,256,fp);
					sscanf(m_TempLine,"%s%d%f%f%f",m_TempString,&Normal->m_NormalIndex[2],&Normal->m_VertexNormal[2].x,&Normal->m_VertexNormal[2].z,&Normal->m_VertexNormal[2].y);
				
					mesh->m_NormalList.push_back(Normal);
				}	
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}
			}
			
		}
		if(_stricmp(m_TempString,"}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}


	}

	return S_OK;

}
HRESULT 
CASE::DecodeTM(FILE* fp,CGeom* Geomatri)
{
	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*TM_ROW0")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_GeomTM._11,&Geomatri->m_GeomTM._13,&Geomatri->m_GeomTM._12);
		if(_stricmp(m_TempString,"*TM_ROW1")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_GeomTM._31,&Geomatri->m_GeomTM._33,&Geomatri->m_GeomTM._32);
		if(_stricmp(m_TempString,"*TM_ROW2")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_GeomTM._21,&Geomatri->m_GeomTM._23,&Geomatri->m_GeomTM._22);
		if(_stricmp(m_TempString,"*TM_ROW3")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_GeomTM._41,&Geomatri->m_GeomTM._43,&Geomatri->m_GeomTM._42);
		if(_stricmp(m_TempString,"*TM_POS")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_Pos.x,&Geomatri->m_Pos.z,&Geomatri->m_Pos.y);
		if(_stricmp(m_TempString,"*TM_ROTAXIS")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_Rot.x,&Geomatri->m_Rot.z,&Geomatri->m_Rot.y);
		if(_stricmp(m_TempString,"*TM_SCALEAXIS")==0)
			sscanf(m_TempLine,"%s%f%f%f",m_TempString,&Geomatri->m_Scale.x,&Geomatri->m_Scale.z,&Geomatri->m_Scale.y);
		if(_stricmp(m_TempString,"}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}
	
	}

	return S_OK;

}
HRESULT CASE::DecodePOSTRACK(FILE* fp,CGeom* Geom)
{
	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*CONTROL_POS_SAMPLE")==0)
		{
			CPosTrack* PosTrack=new CPosTrack;
			sscanf(m_TempLine,"%s%f%f%f%f",m_TempString,&PosTrack->m_Time,&PosTrack->m_Pos.x
						,&PosTrack->m_Pos.z,&PosTrack->m_Pos.y);
			Geom->m_PosTrackList.push_back(PosTrack);
			
		}
		if(_stricmp(m_TempString,"}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}
	}
	return S_OK;
}

HRESULT CASE::DecodeROTTRACK(FILE* fp,CGeom* Geom)
{
	float a, b, c, d;
	D3DXQUATERNION temp;
	D3DXQuaternionIdentity(&temp);
	D3DXQuaternionNormalize(&temp, &temp);

	while (1)
	{
		m_LineCount++;
		fgets(m_TempLine, 256, fp);
		sscanf(m_TempLine, "%s", m_TempString);

		if (_stricmp(m_TempString, "}") == 0)
		{
			strcpy(m_TempString, "sungchul");
			break;
		}
	}
	return S_OK;
}

CGeom *CASE::Search(string filename)
{
	vector<CGeom*>::iterator iter;
	for(iter=m_GeomList.begin();iter!=m_GeomList.end();iter++)
	{
		if(filename==(*iter)->m_NodeName)
			return *iter;
	}
	return NULL;
	
}

HRESULT CASE::MakeParents()
{
	vector<CGeom*>::iterator iter;
	for(iter=m_GeomList.begin();iter!=m_GeomList.end();iter++)
	{
		if((*iter)->m_ParentsName!="")
		{
			(*iter)->m_ParentsGeom=Search((*iter)->m_ParentsName);//부모느드를 찾아 담는다
			(*iter)->m_ParentsGeom->m_ChildList.push_back((*iter));//자식 노드들을 담는다
		}
	}
	return S_OK;
}

HRESULT CASE::DecodeGEOM(FILE* fp)
{
	CGeom* Geomatri=new CGeom(m_pd3dDevice);
	while(1)
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*NODE_NAME")==0)
		{
			bool check=false;
			
			for(int i=0;i<256;i++)
			{
				if(check)
				{
					if(m_TempLine[i]=='"'){ check=false; break;}
					Geomatri->m_NodeName +=m_TempLine[i];
				
				}
				if(m_TempLine[i]=='"')check = true;
			}
		}
		if(_stricmp(m_TempString,"*NODE_PARENT")==0)
		{
			bool check=false;
			for(int i=0;i<256;i++)
			{
				if(check)
				{
					if(m_TempLine[i]=='"'){ check=false; break;}
					Geomatri->m_ParentsName +=m_TempLine[i];
					
				}
				if(m_TempLine[i]=='"')check = true;
			}
		}
		if(_stricmp(m_TempString,"*NODE_TM")==0)
			DecodeTM(fp,Geomatri);

		if(_stricmp(m_TempString,"*MESH")==0)
		{
			Geomatri->m_Mesh=new ASEMesh;
			DecodeMESH(fp,Geomatri->m_Mesh);
		}
		if(_stricmp(m_TempString,"*TM_ANIMATION")==0)
		{
			while(1)
			{
				m_LineCount++;
				fgets(m_TempLine,256,fp);
				sscanf(m_TempLine,"%s",m_TempString);
				if(_stricmp(m_TempString,"*CONTROL_POS_TRACK")==0)
				{
					DecodePOSTRACK(fp,Geomatri);
				}
				if(_stricmp(m_TempString,"*CONTROL_ROT_TRACK")==0)
				{
					DecodeROTTRACK(fp,Geomatri);
				}
				if(_stricmp(m_TempString,"}")==0)
				{
					strcpy(m_TempString,"sungchul");
					break;
				}
			}
		}
		if(_stricmp(m_TempString,"*MATERIAL_REF")==0)
		{
			sscanf(m_TempLine,"%s%d",m_TempString,&Geomatri->m_Materialref);
		}
		if(_stricmp(m_TempString,"}")==0)
		{
			strcpy(m_TempString,"sungchul");
			break;
		}

	}

	
	if(Geomatri->m_NodeName[0]=='B' 
		&& Geomatri->m_NodeName[1]=='i'
		&& Geomatri->m_NodeName[2]=='p'
		&& Geomatri->m_NodeName[3]=='0'
		&& Geomatri->m_NodeName[4]=='1'
		)
		Geomatri->Type=BONE;
	else
		Geomatri->Type=MESH;
	//본메쉬
	m_GeomList.push_back(Geomatri);
	return S_OK;
}

HRESULT CASE::DecodeASE(FILE *fp)
{
	m_LineCount++;
	fgets(m_TempLine,256,fp);
	sscanf(m_TempLine,"%s",m_TempString);

	if(_stricmp(m_TempString,"*3DSMAX_ASCIIEXPORT")!=0)//_stricmp문자가 같으면 0을 반환
		return E_FAIL;

	while(!feof(fp))
	{
		m_LineCount++;
		fgets(m_TempLine,256,fp);
		sscanf(m_TempLine,"%s",m_TempString);
		if(_stricmp(m_TempString,"*SCENE")==0)
			if(FAILED(DecodeSCENE(fp)))
				return E_FAIL;

		if(_stricmp(m_TempString,"*MATERIAL_LIST")==0)
			if(FAILED(DecodeMATERIALLIST(fp)))
				return E_FAIL;

		if(_stricmp(m_TempString,"*GEOMOBJECT")==0)
		{
			if (FAILED(DecodeGEOM(fp)))
				return E_FAIL;
		}
	}
	if(FAILED(MakeParents()))
		return E_FAIL;

	return S_OK;
}

void CASE::Alpha(bool flag) //알파 설정
{

	if (flag)
	{
		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}
	else
	{
		m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}

}

void CASE::MeshAnimation(D3DXMATRIX mat, float frame) //메쉬 애니메이션에서 스키닝 업데이트
{
	Mesh* TempMesh = this->m_pMeshList;

	while (TempMesh)
	{
		if (TempMesh->m_pParents)
		{
			TempMesh->UpdateAniTm(m_pAniName, TempMesh->m_pParents->m_AniMat, frame);
		}
		else
		{
			if (TempMesh->m_sSkinningVt)
			{
				TempMesh->UpdateSkinning(); //스키닝 데이타 업데이트
			}
			else
			{
				TempMesh->UpdateAniTm(m_pAniName, mat, frame);
			}
		}
		TempMesh = TempMesh->m_pNext;
	}
}

void CASE::RenderAse(D3DXMATRIX Scalemat, D3DXMATRIX Rotmat, D3DXMATRIX Posmat, Mesh* pNowMesh) //출력
{
	D3DXMATRIX WorldMat;
	D3DXMatrixIdentity(&WorldMat);

	if (pNowMesh == NULL)
		return;

	DWORD dwfvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	DWORD fvfsize = D3DXGetFVFVertexS

	sViewList* ViewList;
	ViewList = pNowMesh->m_pViewList;

	//-------------- 메시 리스트에서 출력 ------------------

	while (ViewList)
	{
		if (ViewList->m_iNumVertex>0)
		{
			// step2
			// 텍스쳐 설정 
			if (ViewList->m_pMeterial->bUseTexture)
				m_pd3dDevice->SetTexture(0, ViewList->m_pMeterial->m_pTexture);
			else
				m_pd3dDevice->SetMaterial(&(ViewList->m_pMeterial->m_d3dMaterial));

			// 재질 설정
			//m_pd3dDevice->SetMaterial(&(ViewList->pMaterial->d3dMaterial)); 
			// 알파 설정 
			if (ViewList->m_pMeterial->bUseOpacity)
				Alpha(true);

			//----------------- 비 정점 방식으로 ---------------------  
			// 랜더
			m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				ViewList->m_iNumVertex, ViewList->m_pVertex, sizeof(SVertex)); //삼각형 출력

			if (ViewList->m_pMeterial->bUseOpacity)
				Alpha(false);
		}

		ViewList = ViewList->m_pNext;

	}

}

void CASE::Alpha(bool flag) //알파 설정
{
	if (flag)
	{
		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

		m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}
	else
	{
		m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

#if 1
void CASE::ReadGEOMOBJECT(FILE *pf)
{
	char tmpstr[256];

	while (1)
	{
		fgets(m_line, 256, pf);
		sscanf(m_line, "%s", m_str);

		if (_stricmp("*NODE_NAME", m_str) == 0)
		{
			ReadFileName(m_line, m_pNowMesh->m_NodeName);
			continue;
		}

		if (_stricmp("*NODE_PARENT", m_str) == 0)
		{
			ReadFileName(m_line, m_pNowMesh->m_parentsName);
			m_pNowMesh->m_bParents = true;
			continue;
		}

		if (_stricmp("*NODE_TM", m_str) == 0)
		{
			ReadTM(pf);
			continue;
		}

		if (_stricmp("*MESH", m_str) == 0)
		{
			ReadMESH(pf);
			continue;
		}

		if (_stricmp("*MATERIAL_REF", m_str) == 0)
		{
			sscanf(m_line, "%s %d", m_str, &m_pNowMesh->m_iMeterial_Ref);
			continue;
		}

		if (_stricmp("*PHYSIQUE", m_str) == 0)
		{
			ReadPHYSIQUE(pf);
			continue;
		}

		if (_stricmp("*TM_ANIMATION", m_str) == 0)
		{
			ReadAnimation(&m_pNowMesh->m_sAnimation, pf);
			continue;
		}

		if (_stricmp("}", m_str) == 0)
			break;
	}
}

void CASE::ReadPHYSIQUE(FILE *pf)
{
	while (1)
	{
		fgets(m_line, 256, pf);
		sscanf(m_line, "%s", m_str);

		if (_stricmp("*PHYSIQUE_NUMVERTEXASSIGNMENT", m_str) == 0)
		{
			sscanf(m_line, "%s %d", m_str, &m_pNowMesh->m_iNumPhysiqueVt);
			m_pNowMesh->m_sSkinningVt = new sSkinningVertex[m_pNowMesh->m_iNumPhysiqueVt];
		}

		if (_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_LIST", m_str) == 0)
		{
			ReadPHYSIQUE_VT_LIST(pf);
		}

		if (_stricmp("}", m_str) == 0)
			break;
	}
}

void CASE::ReadPHYSIQUE_VT_LIST(FILE *pf)
{
	int Count = 0;
	int iTemp = 0;
	float fTemp = 0.0f;
	char NodeName[256];
	D3DXVECTOR3 *vtmp;

	while (1)
	{
		fgets(m_line, 256, pf);
		sscanf(m_line, "%s", m_str);

		if (_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_BLENDED_RIGIDTYPE", m_str) == 0)
		{
			vtmp = new D3DXVECTOR3(0, 0, 0);
			sSkinningVertex *Temp = &m_pNowMesh->m_sSkinningVt[Count];
			*vtmp = m_pNowMesh->m_sVertex[Count].v;
			Temp->m_pVertex = vtmp;
			Temp->m_VtIndex = Count;
			fgets(m_line, 256, pf); // *PHYSIQUE_VERTEXASSIGNMENT_NUMNODE 2
			sscanf(m_line, "%s %d", m_str, &Temp->m_NumBlend);

			Temp->m_bBland = true;
			Temp->m_pBlandVt = new sBlandVertexInfo[Temp->m_NumBlend];
			fgets(m_line, 256, pf); // *PHYSIQUE_VERTEXASSIGNMENT_NODELIST 

			while (1)
			{
				fgets(m_line, 256, pf);
				sscanf(m_line, "%s", m_str);

				if (_stricmp("}", m_str) == 0)
					break;

				if (_stricmp("*PHYSIQUE_VERTEXASSIGNMENT_NODE", m_str) == 0)
				{
					sscanf(m_line, "%s %d %f %s", m_str, //*PHYSIQUE_VERTEXASSIGNMENT_NODE 0 0.999964 "Bip01 L Foot"
						&iTemp, &fTemp,
						NodeName);

					ReadFileName(m_line, Temp->m_pBlandVt[iTemp].m_NodeName);

					Temp->m_pBlandVt[iTemp].m_fWeight = fTemp;
				}
			}

			Count++;
			fgets(m_line, 256, pf);

			continue;
		}

		if (_stricmp(m_str, "*PHYSIQUE_VERTEXASSIGNMENT_NONBLENDED_RIGIDTYPE") == 0)
		{
			vtmp = new D3DXVECTOR3(0, 0, 0);
			sSkinningVertex *Temp = &m_pNowMesh->m_sSkinningVt[Count];
			*vtmp = m_pNowMesh->m_sVertex[Count].v;
			Temp->m_pVertex = vtmp;
			Temp->m_VtIndex = Count;

			sscanf(m_line, "%s %d %s", m_str, &Temp->m_VtIndex, NodeName);

			Temp->m_bBland = false;
			Temp->m_NumBlend = 1;
			Temp->m_pBlandVt = new sBlandVertexInfo;
			ReadFileName(m_line, Temp->m_pBlandVt->m_NodeName);
			Temp->m_pBlandVt->m_fWeight = 1.0f;

			Count++;
			continue;
		}

		if (_stricmp("}", m_str) == 0)
			break;
	}
}
#endif
