#include "..\..\Header\Component.h"

CComponent::CComponent()
	: m_pGraphicDev(nullptr), m_bClone(false), m_pOwnerObject(nullptr), m_bActive(true)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType)
	: m_pGraphicDev(pGraphicDev), m_bClone(false), m_pOwnerObject(nullptr), m_bActive(true), m_eType(_eType)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs, CGameObject* _pOwnerObject)
	: m_pGraphicDev(rhs.m_pGraphicDev), m_bClone(true), m_pOwnerObject(_pOwnerObject), m_bActive(true), m_eType(rhs.m_eType)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::~CComponent()
{
}

void CComponent::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
