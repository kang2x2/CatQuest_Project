#include "stdafx.h"

#include "Export_Function.h"

#include "PlayerHitEffect.h"

CPlayerHitEffect::CPlayerHitEffect(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_PLAYERHITEFFECT)
{
	m_vPos = _pPos;
}

CPlayerHitEffect::CPlayerHitEffect(const CPlayerHitEffect& rhs)
	: CEffect(rhs)
{
}

CPlayerHitEffect::~CPlayerHitEffect()
{
}

HRESULT CPlayerHitEffect::Ready_Object()
{
	srand((unsigned int)time(NULL));

	m_fRandRotZ = (rand() % 6) * 15;

	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;
	// Cut
	m_bSizeUp = true;
	m_fCutSize = 0.f;
	m_fCutMaxSize = 2.4f;

	return S_OK;
}

_int CPlayerHitEffect::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 플레이어보다 늦게 그려지게 

	// Cut
	m_pTransformCom->Set_Pos(m_vPos);
	m_pTransformCom->Set_Scale(_vec3{ 6.f, m_fCutSize, 6.f });
	m_pTransformCom->Set_Rot(_vec3{ 0.f, 0.f, m_fRandRotZ });

	return iExit;
}

void CPlayerHitEffect::LateUpdate_Object()
{
	if (m_bSizeUp)
	{
		m_fCutSize += 0.6f;
		if (m_fCutSize > m_fCutMaxSize)
		{
			m_bSizeUp = false;
		}
	}
	else
	{
		m_fCutSize -= 0.6f;
		if (m_fCutSize < 0.f)
		{
			CEventMgr::GetInstance()->Delete_Obj(this);
		}
	}

	__super::LateUpdate_Object();
}

void CPlayerHitEffect::Render_Object()
{
	// Cut
	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CPlayerHitEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Cut
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Monster_Cut_Effect", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CPlayerHitEffect* CPlayerHitEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CPlayerHitEffect* pInstance = new CPlayerHitEffect(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Hit Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerHitEffect::Free()
{
	__super::Free();
}
