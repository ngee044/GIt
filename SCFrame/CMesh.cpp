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
HRESULT
Mesh::InitMesh(LPCSTR filename)
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
void 
Mesh::Render()
{
	for( DWORD i=0; i<m_numMaterial; i++ )
	{

		m_pd3dDevice->SetMaterial( &m_MeshMaterial[i] );
		m_pd3dDevice->SetTexture( 0, m_MeshTexture[i] );

		m_Mesh->DrawSubset( i );
	}
}
void 
Mesh::Cleanup()
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