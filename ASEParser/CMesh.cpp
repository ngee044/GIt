#include "header.h"
ASEMesh::ASEMesh()
{
	//
}
ASEMesh::~ASEMesh()
{
	vector<CNormal*>::iterator iter;
	for(iter=m_NormalList.begin();iter !=m_NormalList.end();iter++)
	{
		delete *iter;

	}
	m_NormalList.clear();

}