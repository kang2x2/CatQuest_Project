#include "stdafx.h"

#include "Export_Function.h"

#include "TrapBigFist.h"
#include "Player.h"
#include "SoundMgr.h"

#include "TrapBigFistDust.h"

CTrapBigFist::CTrapBigFist(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos)
	: CProjectile(pGraphicDev, OBJ_ID::PROJECTILE_TRAP_BIGFIST)
	, m_fDamage(40.f), m_bCreateDust(false)
{
	m_vPos = _vPos;
}

CTrapBigFist::CTrapBigFist(const CProjectile& rhs)
	: CProjectile(rhs)
{
}

CTrapBigFist::~CTrapBigFist()
{
}

HRESULT CTrapBigFist::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(m_vPos);
	m_pTransformCom->Set_Scale(_vec3{ 0.74f * 6.f, 1.36f * 6.f, 1.36f * 6.f });

	m_tDropLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDropLerp.Set_Lerp(0.5f, 30.f, m_pTransformCom->Get_Scale().y * 0.7f);

	m_bActive = true;
	m_pOwner = nullptr;

	m_szName = L"TrapBigFist";

	return S_OK;
}

_int CTrapBigFist::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	// m_tDropLerp.Update_Lerp(fTimeDelta);
	// m_pTransformCom->Set_PosY(m_tDropLerp.fCurValue);

	if (!m_tDropLerp.bActive)
	{
		if (!m_bCreateDust)
		{
			CSoundMgr::GetInstance()->PlaySound(L"enemy_impact1.wav", CHANNEL_ID::ENVIRONMENT_1, BINGO_COL_FIST);

			//CGameObject* m_pDust = CTrapBigFistDust::Create
			//(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS));
			//NULL_CHECK_RETURN(m_pDust, E_FAIL);
			//CEventMgr::GetInstance()->Add_Obj(L"FistDust", m_pDust);
			//m_bCreateDust = true;
		}
	}

	return iExit;
}

void CTrapBigFist::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTrapBigFist::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));
	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTrapBigFist::OnCollision_Enter(CGameObject* _pColObj)
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

HRESULT CTrapBigFist::Add_Component()
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

CTrapBigFist* CTrapBigFist::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos)
{
	CTrapBigFist* pInstance = new CTrapBigFist(pGraphicDev, _vPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TrapBigFist Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTrapBigFist::Free()
{
	__super::Free();
}
