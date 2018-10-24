///////////////////////////////////////////////////
//게임속 캐릭터의 각종 속성을 관장하는 코드입니다//
///////////////////////////////////////////////////
#include "CharacterClass.h"
#include "KeyMgr.h"

void CharacterClass::InitCharacter(LPDIRECT3DDEVICE9 pDevice,char* AseFileName,char* ModelName)
{
		char AniFileName[256];
		m_FrameSpeed=FRAMESPEED;
		SetDevice(pDevice);
		::strcpy(m_Name,ModelName);
		::strcpy(AniFileName,ModelName);
		strcat(AniFileName,"AniData.txt");

		m_pAse=new CAse();
		m_pAse->SetDevice(GetDevice());
		m_pAse->LoadAse(AseFileName);
		m_pAse->m_pTextureContainer=new CTextureContainer;
		m_pAse->LoadAseTexture();

		ReadAniMationFromFile(AniFileName);

		SetAnimation("STAND");

		m_pAse->m_pAniName=m_NowAnimationName;
		m_pAse->UpdateAnimation(0.0f);

		
		D3DXVECTOR3 Pos=D3DXVECTOR3(m_Pos._41,m_Pos._42,m_Pos._43);
}


void CharacterClass::SetAnimation(char* AniName)
{
	strcpy(m_BeforeAniName,m_NowAnimationName);
	strcpy(m_NowAnimationName,AniName);

	if(_stricmp(m_NowAnimationName, m_BeforeAniName)!=0 )
	{
		AniSCENE* pDestAniScene=m_pAniSceneList->Search(m_NowAnimationName);
		
		if(m_pNowAniScene->m_bTransition==true && pDestAniScene->m_bTransition == true)
		{
			m_bTransitionAni=true;
		}
		m_bEndMotion=false;

		m_TransitionFrame=0.0f;

		m_AniFrame=0.0f;
	}

	SetNowAniScene(m_NowAnimationName);

}
void CharacterClass::SetNowAniScene(char* AniName)
{
	AniSCENE* TempSceneList=m_pAniSceneList;
	while(TempSceneList)
	{
		if(_stricmp(AniName, TempSceneList->m_AniName)==0)
		{
			m_pNowAniScene=TempSceneList;
			break;
		}
		TempSceneList=TempSceneList->m_pNext;
	}
}

void CharacterClass::ReadAnimation(cTmInfomation *pTmInfo,sAnimation *p_Animation,FILE *pf)
{
	char TempStr[256];

	while(1)
	{
		fgets(m_pAse->m_line, 256, pf); 
		sscanf( m_pAse->m_line , "%s", m_pAse->m_str);

		if(_stricmp("*NODE_NAME", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %s",m_pAse->m_str,TempStr);
			ReadFileName(m_pAse->m_line,p_Animation->m_Name);
			continue;
		}
		
		if ( _stricmp(m_pAse->m_str, "*CONTROL_SCALE_TRACK") == 0 || _stricmp(m_pAse->m_str, "*CONTROL_SCALE_TCB") == 0
			|| _stricmp(m_pAse->m_str,"*CONTROL_SCALE_BEZIER")==0)
		{
			//Scale일경우
			m_pAse->ReadScale_Track(p_Animation,pf);
			continue;
		}

		if( _stricmp(m_pAse->m_str, "*CONTROL_ROT_TRACK") == 0 || _stricmp(m_pAse->m_str, "*CONTROL_ROT_TCB") == 0
			|| _stricmp(m_pAse->m_str,"*CONTROL_ROT_BEZIER")==0)
		{
			//회전일경우 
			ReadRot_Track(pTmInfo,p_Animation,pf);
			continue;
		}
		
		if(   _stricmp(m_pAse->m_str, "*CONTROL_POS_TRACK")==0  || _stricmp(m_pAse->m_str, "*CONTROL_POS_TCB")==0
			|| _stricmp(m_pAse->m_str,"*CONTROL_POS_BEZIER")==0)
		{
			//이동일경우
			m_pAse->ReadPos_Track(p_Animation,pf);
			continue;
		}

		
		if(_stricmp("}", m_pAse->m_str)==0)
			break;
	}
}

void CharacterClass::ReadAniMationFromFile(char* AniFileName)
{
	FILE* pf2=::fopen(AniFileName,"rt");

	char	TempName[128];
	char	TempBipName[128];
	char	TempStr[128];
	int		iTempNum;

	sAnimation* tempAni;
	AniSCENE*	TempScene;

	while(!feof(pf2))
	{
		fgets(m_pAse->m_line, 256, pf2); 
		sscanf( m_pAse->m_line ,"%s", m_pAse->m_str);

		if(_stricmp("*ANINAME", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %s",m_pAse->m_str,TempName);
			m_pAse->ReadFileName(TempName,TempName);

			while(1)
			{
				fgets(m_pAse->m_line, 256, pf2); 
				sscanf( m_pAse->m_line ,"%s", m_pAse->m_str);

				if(_stricmp("*SCENE", m_pAse->m_str)==0)
				{
					TempScene= new AniSCENE;
					strcpy(TempScene->m_AniName,TempName);
					while(1)
					{
						fgets(m_pAse->m_line, 256, pf2); 
						sscanf( m_pAse->m_line ,"%s", m_pAse->m_str);

						if(_stricmp("*SCENE_TRANSITION", m_pAse->m_str)==0)
						{
							int iTransition;
							sscanf( m_pAse->m_line ,"%s %d", m_pAse->m_str,&iTransition);

							if(iTransition==0)
							{
								TempScene->m_bTransition=false;
							}
							else
							{
								TempScene->m_bTransition=true;
							}
							continue;
						}

						if(_stricmp("*SCENE_FIRSTFRAME", m_pAse->m_str)==0)
						{
							sscanf( m_pAse->m_line ,"%s %d", TempStr,&iTempNum);
							TempScene->m_FirstFrame=(float)iTempNum;
							continue;
						}
						if(_stricmp("*SCENE_LASTFRAME", m_pAse->m_str)==0)
						{
							sscanf( m_pAse->m_line ,"%s %d", TempStr,&iTempNum);
							TempScene->m_LastFrame=(float)iTempNum;
							continue;
						}
						if(_stricmp("*SCENE_FRAMESPEED", m_pAse->m_str)==0)
						{
							sscanf( m_pAse->m_line ,"%s %d", TempStr,&iTempNum);
							TempScene->m_FrameSpeed=(float)iTempNum;
							continue;
						}
						if(_stricmp("*SCENE_TICKSPERFRAME", m_pAse->m_str)==0)
						{
							sscanf( m_pAse->m_line ,"%s %d", TempStr,&iTempNum);
							TempScene->m_TickPerFrame=(float)iTempNum;
							continue;
						}
						if(_stricmp("}", m_pAse->m_str)==0)
						break;
					}
					if(!m_pAniSceneList)
					{
						m_pAniSceneList=TempScene;
						m_pNowAniScene=TempScene;
					}
					else
					{
						m_pAniSceneList->Add(TempScene);
					}
					continue;
				}
				if(_stricmp("*MeshTM", m_pAse->m_str)==0)
				{
					while(1)
					{
						fgets(m_pAse->m_line, 256, pf2); 
						sscanf( m_pAse->m_line ,"%s", m_pAse->m_str);
						if(_stricmp("*NODE_TM", m_pAse->m_str)==0)
						{
							::cMesh *NowMesh=NULL;
							cTmInfomation *TempTmInfo;
							TempTmInfo=new cTmInfomation();
							
							fgets(m_pAse->m_line, 256, pf2); 
							m_pAse->ReadFileName(m_pAse->m_line,m_pAse->m_str);
							if(_stricmp("RUN", TempName)==0)
							{
								int i=0;
							}
							NowMesh=m_pAse->Search(m_pAse->m_str);
		
							TempTmInfo->m_pbipName=NowMesh->m_NodeName;
							ReadTm(TempTmInfo,pf2);
							::strcpy(TempTmInfo->m_AniName,TempName);

							if(NowMesh->m_pTmInfoList==NULL)
							{
								NowMesh->m_pTmInfoList=TempTmInfo;
							}
							else
							{
								NowMesh->m_pTmInfoList->Add(TempTmInfo);
							}
							continue;
						}
						if(_stricmp("}", m_pAse->m_str)==0)
						{
							break;
						}
					}
					continue;
				}
				
				if(_stricmp("*BipTM", m_pAse->m_str)==0)
				{
					
					while(1){
						fgets(m_pAse->m_line, 256, pf2); 
						sscanf( m_pAse->m_line ,"%s", m_pAse->m_str);

						if(_stricmp("*NODE_TM", m_pAse->m_str)==0)
						{
							cTmInfomation *TempTmInfo;
							TempTmInfo=new cTmInfomation();
							
							fgets(m_pAse->m_line, 256, pf2); 
							//sscanf( m_pAse->m_line ,"%s %s", m_pAse->m_str,m_pAse->m_str); //NodeName
							m_pAse->ReadFileName(m_pAse->m_line,m_pAse->m_str);

							if(_stricmp("RUN", m_pAse->m_str)==0)
							{
								int i=0;
							}


							::cMesh *NowMesh=m_pAse->SearchBone(m_pAse->m_str);
							TempTmInfo->m_pbipName=NowMesh->m_NodeName;
							ReadTm(TempTmInfo,pf2);
							::strcpy(TempTmInfo->m_AniName,TempName);

							if(NowMesh->m_pTmInfoList==NULL)
							{
								NowMesh->m_pTmInfoList=TempTmInfo;
							}
							else
							{
								NowMesh->m_pTmInfoList->Add(TempTmInfo);
							}
							continue;
						}

						if(_stricmp("}", m_pAse->m_str)==0)
						{
							break;
						}
					}
					continue;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
				}
				

				if(_stricmp("*TM_ANIMATION", m_pAse->m_str)==0)
				{
					tempAni=new sAnimation();
					tempAni->m_pNowAniScene=m_pNowAniScene;
					strcpy(tempAni->m_AniName,TempName);//,tempAni->m_AniName);

					fgets(m_pAse->m_line, 256, pf2); 
					sscanf( m_pAse->m_line , "%s %s",m_pAse->m_str,TempStr);
	
					m_pAse->ReadFileName(m_pAse->m_line,tempAni->m_Name);

					if(_stricmp("Bip01 Bone29", tempAni->m_Name)==0)
					{
						int i=0;
					}
					m_pAse->m_pNowMesh=m_pAse->SearchBone(tempAni->m_Name);

					if(!m_pAse->m_pNowMesh)
					{
						m_pAse->m_pNowMesh=m_pAse->Search(tempAni->m_Name);
					}

					cTmInfomation* pTM=m_pAse->m_pNowMesh->m_pTmInfoList->SeachTmInfo(tempAni->m_AniName);
			
					if(_stricmp(tempAni->m_AniName,"RUN")==0)
					{
						int a=0;
					}
					ReadAnimation( pTM,tempAni,pf2);
					
					if(m_pAse->m_pNowMesh)
					{
						if(!m_pAse->m_pNowMesh->m_pAniList)
						{
							m_pAse->m_pNowMesh->m_pAniList=tempAni;
						}
						else
						{
							m_pAse->m_pNowMesh->m_pAniList->Add(tempAni);
						}
					}
					continue;
				}

				if(_stricmp("}", m_pAse->m_str)==0)
					break;
			}
		}
	}
	fclose(pf2);
}

void CharacterClass::ReadRot_Track(cTmInfomation *pTmInfo,sAnimation *p_Animation,FILE *pf)
{
	sRot_Track *Temp;
	sRot_Track *Tail=NULL;

	D3DXVECTOR3	vReadRot;

	D3DXQUATERNION	tmpR=pTmInfo->m_TmRot;

	int Index;

	float fW;

	D3DXQUATERNION qR;

	while(1)
	{
		fgets(m_pAse->m_line, 256, pf); 
		sscanf( m_pAse->m_line , "%s", m_pAse->m_str);

		if(_stricmp("*CONTROL_ROT_SAMPLE", m_pAse->m_str)==0)
		{
			Temp=new sRot_Track;

			sscanf( m_pAse->m_line , "%s %d %f %f %f %f",m_pAse->m_str,&Index,&vReadRot.x,&vReadRot.z,&vReadRot.y,&fW);

			Temp->m_iIndex=Index;
			Temp->m_x=vReadRot.x;
			Temp->m_y=vReadRot.y;
			Temp->m_z=vReadRot.z;
			Temp->m_w=fW;

			qR.x=(float)sinf(fW/2.0f) * vReadRot.x;
			qR.y=(float)sinf(fW/2.0f) * vReadRot.y;
			qR.z=(float)sinf(fW/2.0f) * vReadRot.z;
			qR.w=cosf(fW/2.0f);
			if(_stricmp("Bip01 Bone38", p_Animation->m_Name)==0 && _stricmp("RUN", p_Animation->m_AniName)==0)
			{
				char str[256] ={0};
				sprintf( str, "index = %d  , x = %f, y = %f, z = %f, fw = %f\n ", Index,vReadRot.x,	vReadRot.z,vReadRot.y ,fW);
				OutputDebugString( str);
			}


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

		if(_stricmp("}", m_pAse->m_str)==0)
		{
			p_Animation->m_Rot->m_iMyLastIndex=Index;
			break;
		}
	}

}

void CharacterClass::ReadFileName(char* Src,char *Dest)
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

void CharacterClass::ReadTm(cTmInfomation *pTmInfo,FILE* fp)
{
	D3DXMatrixIdentity(&pTmInfo->m_TmMat);
	float fX,fY,fZ,fW;

	while(1)
	{
		fgets( m_pAse->m_line, 256, fp); 
		sscanf( m_pAse->m_line , "%s", m_pAse->m_str);

		if(_stricmp("*TM_ROW0", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&pTmInfo->m_TmMat._11,
				&pTmInfo->m_TmMat._13,
				&pTmInfo->m_TmMat._12);
			continue;
		}

		if(_stricmp("*TM_ROW1", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&pTmInfo->m_TmMat._31,
				&pTmInfo->m_TmMat._33,
				&pTmInfo->m_TmMat._32);
			continue;
		}

		if(_stricmp("*TM_ROW2", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&pTmInfo->m_TmMat._21,
				&pTmInfo->m_TmMat._23,
				&pTmInfo->m_TmMat._22);
			continue;
		}

		if(_stricmp("*TM_ROW3", m_pAse->m_str)==0)
		{
			char temp[256];
			::strcpy(temp,m_pAse->m_line);
			sscanf( temp ,"%s %f %f %f",m_pAse->m_str,
				&(pTmInfo->m_TmMat._41),
				&(pTmInfo->m_TmMat._43),
				&(pTmInfo->m_TmMat._42));
			continue;
		}

		if(_stricmp("*TM_POS", m_pAse->m_str)==0)
		{
			pTmInfo->m_TmPos.x=pTmInfo->m_TmMat._41;
			pTmInfo->m_TmPos.y=pTmInfo->m_TmMat._42;
			pTmInfo->m_TmPos.z=pTmInfo->m_TmMat._43;
			continue;
		}

		if(_stricmp("*TM_ROTAXIS", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}
		if(_stricmp("*TM_ROTANGLE", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f",m_pAse->m_str,&fW);

			pTmInfo->m_TmRot.x=(float)sinf(fW/2.0f) *fX;
			pTmInfo->m_TmRot.y=(float)sinf(fW/2.0f) *fY;
			pTmInfo->m_TmRot.z=(float)sinf(fW/2.0f) *fZ;
			pTmInfo->m_TmRot.w=(float)cosf(fW/2.0f);
			continue;
		}

		if(_stricmp("*TM_SCALE", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&pTmInfo->m_TmScale.x,
				&pTmInfo->m_TmScale.z,
				&pTmInfo->m_TmScale.y);
			continue;
		}
		if(_stricmp("*TM_SCALEAXIS", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f %f %f",m_pAse->m_str,
				&fX,
				&fZ,
				&fY);
			continue;
		}

		if(_stricmp("*TM_SCALEAXISANG", m_pAse->m_str)==0)
		{
			sscanf( m_pAse->m_line , "%s %f",m_pAse->m_str,&fW);
			pTmInfo->m_TmScaleRot.x=(float)sinf(fW/2.0f) *fX;
			pTmInfo->m_TmScaleRot.y=(float)sinf(fW/2.0f) *fY;
			pTmInfo->m_TmScaleRot.z=(float)sinf(fW/2.0f) *fZ;
			pTmInfo->m_TmScaleRot.w=(float)cosf(fW/2.0f);
			continue;
		}

		if(_stricmp("}", m_pAse->m_str)==0)
		{
			D3DXMatrixInverse(&pTmInfo->m_InvTm,NULL,&pTmInfo->m_TmMat);
			break;
		}
	}
}

void CharacterClass::UpdateTransitionAni()
{
	m_TransitionFrame+= 0.001f * (float)(INTERPOLATION_SPEED*2);

	if(m_TransitionFrame >=(float)MAXIMUM_INTERPOLATION_FRAME)
	{
		m_TransitionFrame=0.0f;
		m_bTransitionAni=false;
		return;
	}

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	cMesh* TempMesh=m_pAse->m_pBoneList;

	while(TempMesh)
	{
		if(TempMesh->m_bParents==false)
		{
			TempMesh->UpdateTransitionAniTm(m_NowAnimationName,mat,m_TransitionFrame);
		}
		TempMesh=TempMesh->m_pNext;
	}


	TempMesh=m_pAse->m_pMeshList;

	while(TempMesh)
	{
		if(TempMesh->m_pParents)
		{
			TempMesh->UpdateTransitionAniTm(m_NowAnimationName,mat,m_TransitionFrame);
		}
		else
		{
			if(TempMesh->m_sSkinningVt)
			{
				TempMesh->UpdateSkinning();
			}
			else
			{
				TempMesh->UpdateTransitionAniTm(m_NowAnimationName,mat,m_TransitionFrame);
			}
		}
		TempMesh=TempMesh->m_pNext;
	}
}

void CharacterClass::Update()
{
	UpdateState();

	if(m_bTransitionAni)
	{
		UpdateTransitionAni();
	}
	else
	{
		UpdateAnimation();
	}
	if(m_bTransRot)
	{
		TransRot();
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		SetAnimation("RUN");
	}
	else if (GetAsyncKeyState('2') & 0x8000)
	{
		SetAnimation("STAND");
	}
	else if (GetAsyncKeyState('3') & 0x8000)
	{
		SetAnimation("ATT");
	}
}

void CharacterClass::UpdateAniFrame()
{
	m_AniFrame+= (0.001f * ( (m_pNowAniScene->m_FrameSpeed *5 ) * m_pNowAniScene->m_TickPerFrame));

	if(m_AniFrame >= m_pNowAniScene->m_LastFrame * m_pNowAniScene->m_TickPerFrame)
	{
		m_AniFrame=0.0f;

		m_bEndMotion=true;
	}
}

void CharacterClass::UpdateAnimation()
{
	if(!m_bAniFrameIdle)
	{
		m_AniFrame+= (0.001f * ( (m_pNowAniScene->m_FrameSpeed *7  ) * m_pNowAniScene->m_TickPerFrame));
	}

	if(m_AniFrame >= m_pNowAniScene->m_LastFrame * m_pNowAniScene->m_TickPerFrame)
	{
		m_AniFrame=0.0f;

		m_bEndMotion=true;
	}

	m_pAse->UpdateAnimation(m_AniFrame);
}

void CharacterClass::TransRot()
{
	m_fTransRot+=(0.001f * ROTSPEED);

	D3DXQUATERNION qStartRot,qEndRot,qRot;
	qStartRot=m_qRot;
	qEndRot=m_qDestRot;

	D3DXQuaternionSlerp(&qRot,&qStartRot,&qEndRot,m_fTransRot);

	D3DXMatrixRotationQuaternion(&m_Rot,&qRot);

	if(m_fTransRot>=1.0f)
	{
		m_fTransRot=0.0f;
		m_qRot=m_qDestRot;
		m_bTransRot=false;
	}
}

void CharacterClass::UpdateActionState()
{
	int ActionState=m_eActionState;

	switch(ActionState)
	{
		case ACTION_IDLE:
			IDLE_ActionProcess();
			break;
		case ACTION_RUN:
			RUN_ActionProcess();
			break;
		case ACTION_ATT:
			ATT_ActionProcess();
			break;
	}
}

void CharacterClass::UpdateState()
{
	UpdateActionState();

	if(m_bMove)
		UpdateMove();

	UpdateDestqRot();
}

void CharacterClass::UpdateDestqRot()
{
	D3DXVECTOR3 TempDir=D3DXVECTOR3(0.0f,0.0f,-1.0f);

	if(m_bTransRot==false)
	{
		 float fRad=::acos(D3DXVec3Dot(&m_Direction,&TempDir) / (D3DXVec3Length(&m_Direction) * D3DXVec3Length(&m_Direction) ));

		 float dir = m_Direction.x * TempDir.z - TempDir.x * m_Direction.z;
		 float fx=0.0f,fy=1.0f,fz=0.0f;

		 if(dir < 0.0f)
		 {
			 fRad*=-1.0f;
		 }
		 
		m_bTransRot=true;

		m_qDestRot.w=cosf(fRad / 2.0f);
		m_qDestRot.x=sinf(fRad / 2.0f) *fx;
		m_qDestRot.y=sinf(fRad / 2.0f) *fy;
		m_qDestRot.z=sinf(fRad / 2.0f) *fz;
	}

}

void CharacterClass::UpdateMove()
{
	int DirectionState=(int)m_eDirectionState;

	D3DXMATRIX TempPos;
	D3DXMATRIX TempRot;
	D3DXMatrixIdentity(&TempPos);
	D3DXMatrixIdentity(&TempRot);

	float Move=0.0012*MOVESPEED;

	switch(DirectionState)
	{
		case DIRECTION_UP:
			D3DXMatrixTranslation(&TempPos,0.0f,0.0f,Move);
			m_Direction=D3DXVECTOR3(0.0f,0.0f,1.0f);
			break;
		case DIRECTION_DOWN:
			D3DXMatrixTranslation(&TempPos,0.0f,0.0f,-Move);
			m_Direction=D3DXVECTOR3(0.0f,0.0f,-1.0f);
			break;
		case DIRECTION_LEFT:
			D3DXMatrixTranslation(&TempPos,-Move,0.0f,0.0f);
			m_Direction=D3DXVECTOR3(-1.0f,0.0f,0.0f);
			break;
		case DIRECTION_RIGHT:
			D3DXMatrixTranslation(&TempPos,Move,0.0f,0.0f);
			m_Direction=D3DXVECTOR3(1.0f,0.0f,0.0f);
			break;
		case DIRECTION_UP_LEFT:
			D3DXMatrixTranslation(&TempPos,-Move*0.75,0.0f,Move*0.75);
			m_Direction=D3DXVECTOR3(-0.5f,0.0f,0.5f);
			D3DXVec3Normalize(&m_Direction,&m_Direction);
			break;
		case DIRECTION_UP_RIGHT:
			D3DXMatrixTranslation(&TempPos,Move*0.75,0.0f,Move*0.75);
			m_Direction=D3DXVECTOR3(0.5f,0.0f,0.5f);
			D3DXVec3Normalize(&m_Direction,&m_Direction);
			break;
		case DIRECTION_DOWN_LEFT:
			D3DXMatrixTranslation(&TempPos,-Move*0.75,0.0f,-Move*0.75);
			m_Direction=D3DXVECTOR3(-0.5f,0.0f,-0.5f);
			D3DXVec3Normalize(&m_Direction,&m_Direction);
			break;
		case DIRECTION_DOWN_RIGHT:
			D3DXMatrixTranslation(&TempPos,Move*0.75,0.0f,-Move*0.75);
			m_Direction=D3DXVECTOR3(0.5f,0.0f,-0.5f);
			D3DXVec3Normalize(&m_Direction,&m_Direction);
			break;
	}

	m_Pos*=TempPos;
}

void CharacterClass::UpdateProcessKey(sKeyInfo* spKeyInfo)
{

		////////////////////////////////////////////////////////////////
		//키입력 처리 
		////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////
		if( spKeyInfo->m_bNomalKey)
		{
			if(spKeyInfo->m_bZ || spKeyInfo->m_bLbutton)
			{
				m_eWordKeyState=WORDKEY_Z;
			}
		}
		else
		{
			m_eWordKeyState=WORDKEY_NONE;
		}

		if( spKeyInfo->m_bDirectionKey)
		{
			bool check=false;


			if(  !check && spKeyInfo->m_bUp)
			{
				if(spKeyInfo->m_bLeft)
				m_eDirectionState=DIRECTION_UP_LEFT;
				else if(spKeyInfo->m_bRight)
				m_eDirectionState=DIRECTION_UP_RIGHT;
				else
				m_eDirectionState=DIRECTION_UP;

				check=true;
			}
			if(  !check && spKeyInfo->m_bDown)
			{
				if(spKeyInfo->m_bLeft)
				m_eDirectionState=DIRECTION_DOWN_LEFT;
				
				else if(spKeyInfo->m_bRight)
				m_eDirectionState=DIRECTION_DOWN_RIGHT;
				
				else
				m_eDirectionState=DIRECTION_DOWN;
				check=true;
			}
			
			if(  !check && spKeyInfo->m_bLeft)
			{
				if(spKeyInfo->m_bUp)
				m_eDirectionState=DIRECTION_UP_LEFT;
				else if(spKeyInfo->m_bDown)
				m_eDirectionState=DIRECTION_DOWN_LEFT;
				
				else
				m_eDirectionState=DIRECTION_LEFT;
				check=true;
			}
			if(  !check && spKeyInfo->m_bRight)
			{
				if(spKeyInfo->m_bUp)
				m_eDirectionState=DIRECTION_UP_RIGHT;
				else if(spKeyInfo->m_bDown)
				m_eDirectionState=DIRECTION_DOWN_RIGHT;
				
				else
				m_eDirectionState=DIRECTION_RIGHT;
				check=true;
			}

		}
		else
		{
			m_eDirectionState=DIRECTION_NONE;
		}
}

void CharacterClass::IDLE_ActionProcess()
{
	//this->m_Direction = ::D3DXVECTOR3(0.0f, 0.0f, 1.0f);//계속 한 방향을 바라보도록 함
	

	if(m_eDirectionState!=DIRECTION_NONE)
	{
		m_eActionState=ACTION_RUN;
		m_bMove=true;
		SetAnimation("RUN");
	}
	else
	{
		if( !m_ATT && m_eWordKeyState==WORDKEY_Z)
		{
			m_eActionState=ACTION_ATT;
			m_AttIdle=true;
			m_bAniFrameIdle=true;
			m_bMove=false;
			SetAnimation("ATT");
		}
	}
	
}//대기상태 처리
void CharacterClass::RUN_ActionProcess()
{
	if(m_eDirectionState==DIRECTION_NONE)
	{
		m_eActionState=ACTION_IDLE;
		SetAnimation("STAND");
	}
}//뛰기상태 처리
void CharacterClass::ATT_ActionProcess()
{
	cKeyMgr *pKeyMgr = cKeyMgr::CreateKeyMgr();
	pKeyMgr=cKeyMgr::GetKeyMgr();

	if(m_AttIdle==true)
	{
		if(pKeyMgr->m_sKeyInfo->m_bZ==false && pKeyMgr->m_sKeyInfo->m_bLbutton ==false)
		{
			m_AttIdle=false;
			m_bAniFrameIdle=false;
			m_ATT=true;
			
			m_Power=m_Power+(m_AniFrame /m_fAttGage);
		}
		else
		{
			if( (m_AniFrame+m_fAttFrameSpeed) <= m_fAttGage)
			{
				m_Power+=m_fAttFrameSpeed / m_fAttGage;
				m_AniFrame+=m_fAttFrameSpeed;

			}
			else
			{
				m_Power=1.8f;
			}
		}
	}

	if(m_bEndMotion==true)
	{
		m_eActionState=ACTION_IDLE;
		m_ATT=false;
		SetAnimation("STAND");
	}

}//공격상태 처리 

void CharacterClass::Render()
{
	::D3DXMATRIX Rot;
	D3DXMatrixRotationX(&Rot,3.14f/8.0f);

	cMesh *TempMesh=m_pAse->m_pMeshList;

	while(TempMesh)
	{
		Rot=m_Rot*Rot;

		m_pAse->RenderAse(m_Scale,m_Rot,m_Pos,TempMesh);

		TempMesh=TempMesh->m_pNext;
	}

	
}

float CharacterClass::Get_pos_x()
{
	return m_Pos._41;
}
float CharacterClass::Get_pos_z()
{
	return m_Pos._43;
}



