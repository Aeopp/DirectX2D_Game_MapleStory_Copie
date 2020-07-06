#include "Ref.h"

CRef::CRef() : m_iRef{ 1 } ,
m_bEnable{ true },
m_bLife{ true }  
{
}

void CRef::AddRef() 
{
	++m_iRef;
}
