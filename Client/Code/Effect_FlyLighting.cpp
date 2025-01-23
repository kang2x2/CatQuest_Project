#include "stdafx.h"
#include "Effect_FlyLighting.h"

#include "Export_Function.h"

CEffect_FlyLighting::CEffect_FlyLighting(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_FLYLINGHTING)
{
}

CEffect_FlyLighting::CEffect_FlyLighting(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_FlyLighting::~CEffect_FlyLighting()
{
}

HRESULT CEffect_FlyLighting::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 8.f, 16.f, 16.f });

	m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_FlyLighting::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bActive && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
		m_bActive = false;

	return iExit;
}

void CEffect_FlyLighting::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_FlyLighting::Render_Object()
{
	__super::Render_Object();
}

void CEffect_FlyLighting::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, 10.5f, _vPos.z + 3.5f });
	m_bActive = true;
	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);
}

HRESULT CEffect_FlyLighting::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Flight_Lighting", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.04f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_FlyLighting* CEffect_FlyLighting::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_FlyLighting* pInstance = new CEffect_FlyLighting(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlyLighting Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_FlyLighting::Free()
{
	__super::Free();
}
