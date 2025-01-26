#include "stdafx.h"

#include "Export_Function.h"

#include "TrapFist.h"
#include "Player.h"
#include "SoundMgr.h"

#include "TrapFistDust.h"

CTrapFist::CTrapFist(LPDIRECT3DDEVICE9 pGraphicDev)
	: CProjectile(pGraphicDev, OBJ_ID::PROJECTILE_TRAP_FIST)
	, m_fDamage(40.f), m_bCreateDust(false)
{
}

CTrapFist::CTrapFist(const CProjectile& rhs)
	: CProjectile(rhs)
{
}

CTrapFist::~CTrapFist()
{
}

HRESULT CTrapFist::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	std::mt19937 gen(m_Random());

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	std::uniform_real_distribution<float> xDist(120.f, 190.f);
	std::uniform_real_distribution<float> zDist(115.f, 165.f);


	m_pTransformCom->Set_Pos({ xDist(gen) , 30.f ,zDist(gen) });
	m_pTransformCom->Set_Scale(_vec3{ 0.74f * 2.f, 1.36f * 2.f, 1.36f * 2.f });

	m_tDropLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDropLerp.Set_Lerp(0.5f, 30.f, m_pTransformCom->Get_Scale().y * 0.7f);

	m_tDeAlphaLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDeAlphaLerp.Set_Lerp(0.5f, 255.f, 0.f);

	m_bActive = true;
	m_fTranslucent = 255.f;

	m_pOwner = nullptr;

	m_szName = L"TrapFist";

	return S_OK;
}

_int CTrapFist::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	m_tDropLerp.Update_Lerp(fTimeDelta);
	m_pTransformCom->Set_PosY(m_tDropLerp.fCurValue);

	if (!m_tDropLerp.bActive)
	{
		if (!m_bCreateDust)
		{
			CSoundMgr::GetInstance()->PlaySound(L"enemy_impact1.wav", CHANNEL_ID::ENVIRONMENT_1, BINGO_COL_FIST);

			CGameObject* m_pDust = CTrapFistDust::Create
			(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS));
			NULL_CHECK_RETURN(m_pDust, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"FistDust", m_pDust);
			m_bCreateDust = true;
		}

		m_tDeAlphaLerp.Update_Lerp(fTimeDelta);
		m_fTranslucent = m_tDeAlphaLerp.fCurValue;
		if (!m_tDeAlphaLerp.bActive)
		{
			CEventMgr::GetInstance()->Delete_Obj(this);
		}
	}

	return iExit;
}

void CTrapFist::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTrapFist::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fTranslucent, 255, 255, 255));
	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTrapFist::OnCollision_Enter(CGameObject* _pColObj)
{
	CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	switch (_pColObj->Get_Type())
	{
	case OBJ_TYPE::PLAYER:
		dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
		break;
	default:
		break;
	}
}

HRESULT CTrapFist::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bingo_Trap_Fist", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CTrapFist* CTrapFist::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTrapFist* pInstance = new CTrapFist(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TrapFist Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTrapFist::Free()
{
	__super::Free();
}
