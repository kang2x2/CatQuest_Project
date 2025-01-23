#include "stdafx.h"
#include "Effect_ThornAttack.h"

#include "Export_Function.h"

CEffect_ThornAttack::CEffect_ThornAttack(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_THORN_ATTACK)
{
}

CEffect_ThornAttack::CEffect_ThornAttack(const CEffect_ThornAttack& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_ThornAttack::~CEffect_ThornAttack()
{
}

HRESULT CEffect_ThornAttack::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 5.f, 10.f, 10.f });
	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	_vec3 vPos = m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS);
	if (m_pOwnerobject->Get_Transform()->Get_Scale().x < 0)
	{
		m_pTransformCom->Set_Pos(_vec3{ vPos.x - 2.5f, 10.f, vPos.z });
	}
	else
	{
		m_pTransformCom->Set_Pos(_vec3{ vPos.x + 2.f, 10.f, vPos.z });
	}

	return S_OK;
}

_int CEffect_ThornAttack::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}
	

	return iExit;
}

void CEffect_ThornAttack::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_ThornAttack::Render_Object()
{
	__super::Render_Object();
}

void CEffect_ThornAttack::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

HRESULT CEffect_ThornAttack::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_ThornAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.04f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_ThornAttack* CEffect_ThornAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_ThornAttack* pInstance = new CEffect_ThornAttack(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_ThornAttack Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_ThornAttack::Free()
{
	__super::Free();
}
