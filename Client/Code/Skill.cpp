#include "stdafx.h"
#include "Skill.h"

#include "Export_Function.h"

#include "SkillEffect.h"
#include "Effect_Range_Quater.h"

CSkill::CSkill(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::SKILL, _eID)
	, m_pSKillEffect(nullptr)
	, m_pRangeEffect(nullptr)
	, m_bPlay(false)
	, m_pRangeObj(nullptr)
	, m_iLv(0)
{
}

CSkill::CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::SKILL, _eID)
	, m_pOwnerObject(_pOwnerObject)
	, m_bPlay(false)
{	
}

CSkill::CSkill(const CSkill& rhs)
	: Engine::CGameObject(rhs)
{
}

CSkill::~CSkill()
{
}

HRESULT CSkill::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CSkill::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CSkill::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill::Render_Object()
{
	__super::Render_Object(); // 콜라이더 출력
}

HRESULT CSkill::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

HRESULT CSkill::Play()
{
	NULL_CHECK_RETURN(m_pSKillEffect, E_FAIL);
	NULL_CHECK_RETURN(m_pRangeEffect, E_FAIL);
	return S_OK;
}



HRESULT CSkill::End()
{
	if(nullptr != m_pSKillEffect)
		m_pSKillEffect->Set_Active(FALSE);
	if (nullptr != m_pRangeEffect)
		m_pRangeEffect->Set_Active(FALSE);

	return S_OK;
}

void CSkill::Free()
{
	__super::Free();
}
