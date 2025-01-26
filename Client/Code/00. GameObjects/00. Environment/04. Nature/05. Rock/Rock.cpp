#include "stdafx.h"
#include "..\Header\Rock.h"

#include "Export_Function.h"

#include "EventMgr.h"

CRock::CRock(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: CEnvironment(pGraphicDev, _eID)
{
}

CRock::CRock(const CRock& rhs)
	: CEnvironment(rhs)
{
}

CRock::~CRock()
{
}

HRESULT CRock::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CRock::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CRock::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// CEnvironment::Render_Object(); // 콜라이더 필요 없음.
}

void CRock::Play_ColLogic(const _float& fTimeDelta)
{
}

HRESULT CRock::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CRock::Free()
{
	__super::Free();
}
