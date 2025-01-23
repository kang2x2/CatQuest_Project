#include "stdafx.h"
#include "Effect_Boss_HellFire.h"

#include "Export_Function.h"

CEffect_Boss_HellFire::CEffect_Boss_HellFire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject )
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_BOSS_HELLFIRE)
{

}

CEffect_Boss_HellFire::CEffect_Boss_HellFire(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Boss_HellFire::~CEffect_Boss_HellFire()
{
}

HRESULT CEffect_Boss_HellFire::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 10.f , 10.f , 0.f });
	//m_pTransformCom->Set_Pos(_vec3{ 150, 10.f, 70 });

	m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Boss_HellFire::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


	if (m_bActive && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
		m_bActive = false;



	return iExit;
}

void CEffect_Boss_HellFire::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Boss_HellFire::Render_Object()
{
	__super::Render_Object();
}

void CEffect_Boss_HellFire::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, m_pTransformCom->Get_Scale().y, _vPos.z});
	m_bActive = true;
	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

}


HRESULT CEffect_Boss_HellFire::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Boss_HellFire", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Boss_HellFire* CEffect_Boss_HellFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Boss_HellFire* pInstance = new CEffect_Boss_HellFire(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Thunder Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Boss_HellFire::Free()
{
	__super::Free();
}
