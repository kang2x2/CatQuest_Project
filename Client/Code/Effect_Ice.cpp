#include "stdafx.h"
#include "Effect_Ice.h"
#include "Player.h"
#include "Skill.h"
#include "Export_Function.h"

CEffect_Ice::CEffect_Ice(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_FREEZING)
{
}

CEffect_Ice::CEffect_Ice(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Ice::~CEffect_Ice()
{
}

HRESULT CEffect_Ice::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 17.f, 17.f, 17.f });
	m_pTransformCom->Set_Pos(_vec3{ 130, 6.f, 70 });

	m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Ice::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bActive && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
		m_bActive = false;

	return iExit;
}

void CEffect_Ice::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Ice::Render_Object()
{
	__super::Render_Object();
}

void CEffect_Ice::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, _vPos.z - 5.2f });
	m_bActive = true;
	if (m_pOwnerobject->Get_Type() == OBJ_TYPE::SKILL)
	{
		CGameObject* pSkillOwner = static_cast<CSkill*>(m_pOwnerobject)->Get_SkillOwner();
		if (pSkillOwner->Get_Type() == OBJ_TYPE::PLAYER)
		{
			if (static_cast<CPlayer*>(pSkillOwner)->Get_PlayerClass() == CLASS_TYPE::THORN)
				m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_DIE);
			else
				m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);
		}
	}
	else
		m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);
}

HRESULT CEffect_Ice::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_Ice", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.05f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_CrystalIce", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_DIE, 0.05f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Ice* CEffect_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Ice* pInstance = new CEffect_Ice(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Fire Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Ice::Free()
{
	__super::Free();
}
