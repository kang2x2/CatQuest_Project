#include "stdafx.h"
#include "Effect_Cast_Blue.h"

#include "Export_Function.h"

CEffect_Cast_Blue::CEffect_Cast_Blue(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_CAST_BLUE)
{
}

CEffect_Cast_Blue::CEffect_Cast_Blue(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Cast_Blue::~CEffect_Cast_Blue()
{
}

HRESULT CEffect_Cast_Blue::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 12.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 110, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Cast_Blue::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CEffect_Cast_Blue::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Cast_Blue::Render_Object()
{
	__super::Render_Object();
}

HRESULT CEffect_Cast_Blue::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_Cast_Blue", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Cast_Blue* CEffect_Cast_Blue::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Cast_Blue* pInstance = new CEffect_Cast_Blue(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Cast Blue Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Cast_Blue::Free()
{
	__super::Free();
}
