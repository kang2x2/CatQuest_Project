#include "stdafx.h"
#include "Effect_Heal.h"

#include "Export_Function.h"
#include "Player.h"

CEffect_Heal::CEffect_Heal(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_HEAL), m_iPawScale(0.f)
{
}

CEffect_Heal::CEffect_Heal(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Heal::~CEffect_Heal()
{
}

HRESULT CEffect_Heal::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 15.f, 15.f, 15.f });
	m_pTransformCom->Set_Pos(_vec3{ 130, 7.f, 70 });

	m_pUITransform[0]->Set_Scale(_vec3{ 0.f, 0.f, 0.f });

	m_bActive = false;
	m_bPawExpand = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Heal::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bActive)
	{
		CTransform* pTransform = dynamic_cast<CTransform*>(CManagement::GetInstance()->Get_Component(OBJ_TYPE::PLAYER, L"Player", 
			COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
		if (nullptr != pTransform)
		{
			_vec3 pPlayerPos = pTransform->Get_Info(INFO::INFO_POS);
			m_pTransformCom->Set_Pos(_vec3{ pPlayerPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, pPlayerPos.z + 2.f });
			for (_uint i = 0; i < 2; ++i)
			{
				m_pUITransform[i]->Set_Pos(_vec3{ pPlayerPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, pPlayerPos.z - 3.f});
			}
		}

		if (6 == m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame())
			m_bPawExpand = true;

		if(m_bPawExpand)
		{
			//m_pUITransform[0]->Set_Scale(_vec3{ 1.f, 1.f, 1.f });
			_vec3 vPawScale = _vec3{ 1.f, 1.f, 1.f };
			_vec3 vOut = m_pUITransform[0]->Lerp(vPawScale, vPawScale * 3.f, 0.5f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_pUITransform[0]->Set_Scale(vOut);
			}
			else
			{
				if (m_pAnimatorCom->Get_CurAniamtion()->Is_End())
				{
					m_pUITransform[0]->Reset_Lerp();
					m_pUITransform[0]->Set_Scale(_vec3{ 0.f, 0.f, 0.f });
					m_bPawExpand = false;
					m_bActive = false;
				}
			}
		}	
	}
	

	return iExit;
}

void CEffect_Heal::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Heal::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	__super::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransform[0]->Get_WorldMat());
	m_pUITexutre[0]->Render_Texture();
	m_pBufferCom->Render_Buffer();
}

void CEffect_Heal::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, _vPos.z + 2.f});
	m_bActive = true;
	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);
	CCameraMgr::GetInstance()->Shake_Camera(0.15, 30);
}

HRESULT CEffect_Heal::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_Heal", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITexutre[0] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealPaw", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITexutre[1] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealSpark", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	for (_uint i = 0; i < 2; ++i)
	{
		pComponent = m_pUITransform[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}

	return S_OK;
}

CEffect_Heal* CEffect_Heal::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Heal* pInstance = new CEffect_Heal(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Heal Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Heal::Free()
{
	__super::Free();
}
