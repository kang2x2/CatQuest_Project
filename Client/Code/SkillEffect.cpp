#include "stdafx.h"

#include "Export_Function.h"
#include "SkillEffect.h"

CSkillEffect::CSkillEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID)
	:CEffect(pGraphicDev, _pOwnerObject, _eID)
	, m_pTextureCom(nullptr)
	, m_pAnimation(nullptr)
	, m_bEnd(true)
{
}

CSkillEffect::CSkillEffect(const CEffect& rhs)
	: CEffect(rhs)
{
}

CSkillEffect::~CSkillEffect()
{
}

HRESULT CSkillEffect::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CSkillEffect::Update_Object(const _float& fTimeDelta)
{
	if (m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		m_bActive = false;
	}

	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSkillEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CSkillEffect::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pAnimatorCom->Render_Animator();

	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

void CSkillEffect::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Scale(_vSize);
	m_pTransformCom->Set_Pos(_vPos);

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	m_bActive = true;
}

HRESULT CSkillEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	return S_OK;
}

void CSkillEffect::Free()
{
	__super::Free();
}
