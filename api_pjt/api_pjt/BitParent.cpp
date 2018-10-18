#include "BitParent.h"
#include "ManagerHeader.h"

BitParent::BitParent()
{
}

BitParent::~BitParent()
{
}

void BitParent::GetReSize()
{
	m_nWidth = BitMgr::Instance()->GetWidth();
	m_nHeight = BitMgr::Instance()->GetHeight();
}