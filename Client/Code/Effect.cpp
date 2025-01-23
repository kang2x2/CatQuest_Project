#include "stdafx.h"
#include "..\Header\Effect.h"

#include "Export_Function.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::EFFECT, _eID)
{
}

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::EFFECT, _eID)
	, m_pOwnerobject(_pOwnerObject)
{
	ZeroMemory(&m_vOffSet, sizeof(_vec3));
	ZeroMemory(&m_vSize, sizeof(_vec3));
	ZeroMemory(&m_vRot, sizeof(_vec3));
}

CEffect::CEffect(const CEffect & rhs)
	: Engine::CGameObject(rhs)
{
}

CEffect::~CEffect()
{
}

HRESULT CEffect::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = false;

	return S_OK;
}

_int CEffect::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (nullptr != m_pAnimatorCom)
		m_pAnimatorCom->Update_Animator(fTimeDelta);

	//m_pAnimatorCom->Update_Animator(fTimeDelta); // 마지막 병합에서는 주석 처리 되어 있었음

	return iExit;
}

void CEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect::Render_Object()
{
	if(nullptr != m_pAnimatorCom)
		m_pAnimatorCom->Render_Animator();

	// m_pAnimatorCom->Render_Animator(); // 마지막 병합에서는 주석 처리 되어 있었음

	__super::Render_Object(); // 콜라이더 출력
}


HRESULT CEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	return S_OK;
}

//CEffect * CEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
//{
//	CEffect*	pInstance = new CEffect(pGraphicDev, _pOwnerObject);
//
//	if (FAILED(pInstance->Ready_Object()))
//	{
//		Safe_Release(pInstance);
//
//		MSG_BOX("Effect Create Failed");
//		return nullptr;
//	}
//
//	return pInstance;
//}

void CEffect::Free()
{
	__super::Free();
}
