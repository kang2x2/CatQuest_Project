#include "stdafx.h"
#include "..\Header\Environment.h"

#include "Export_Function.h"

CEnvironment::CEnvironment(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ENVIRONMENT, _eID)
	, m_pTextureCom(nullptr), m_bCol(false)
{
}

CEnvironment::CEnvironment(const CEnvironment& rhs)
	: Engine::CGameObject(rhs)
	, m_bCol(rhs.m_bCol)
{
}

CEnvironment::~CEnvironment()
{
}

HRESULT CEnvironment::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CEnvironment::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CEnvironment::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEnvironment::Render_Object()
{
	__super::Render_Object(); // 콜라이더 출력

}

HRESULT CEnvironment::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CEnvironment::Free()
{
	__super::Free();
}

