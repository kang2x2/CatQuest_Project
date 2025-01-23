#include "stdafx.h"
#include "Zeolite.h"

#include "Export_Function.h"

#include "Shadow_Zeolite.h"
#include "TalkMgr.h"
#include "QuestMgr.h"

#include "ZeoliteDust.h"

CZeolite::CZeolite(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_ZEOLITE)
	, m_bDelete(false)
{
}

CZeolite::CZeolite(const CNpc& rhs)
	: CNpc(rhs)
{
}


CZeolite::~CZeolite()
{
}

HRESULT CZeolite::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 156.f, 6.4f , 102.f });
	m_pTransformCom->Set_Scale(_vec3{ 5.f, 8.75f, 5.f });

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Npc_Zeolite_Shadow", CShadow_Zeolite::Create(m_pGraphicDev, this));

	// 가라앉기
	m_tPosDownLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tPosDownLerpY.Set_Lerp(5.f, m_pTransformCom->Get_Info(INFO_POS).y, -6.0f);

	m_tPosDownLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
	m_tPosDownLerpZ.Set_Lerp(5.f, m_pTransformCom->Get_Info(INFO_POS).z, m_pTransformCom->Get_Info(INFO_POS).z - 8.5f);


	// 먼지 생성
	m_tDustCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDustCreateLerp.Set_Lerp(0.02f, 1.f, 0.f);

	// 알파 처리
	m_tAlphaLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaLerp.Set_Lerp(5.f, 255.f, 0.f);

	m_szName = L"Npc_Zeolite";
	m_fAlpha = 255.f;

	return S_OK;
}
static _bool bSound = FALSE;
_int CZeolite::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (m_bDelete)
	{
		if (!bSound)
		{
			// 사운드 플레이
			bSound = TRUE;
			CSoundMgr::GetInstance()->PlaySound(L"dragon_death.wav", CHANNEL_ID::ENVIRONMENT_0, 0.8f);
		}
		m_tAlphaLerp.Update_Lerp(fTimeDelta);
		m_fAlpha = m_tAlphaLerp.fCurValue;

		m_tPosDownLerpY.Update_Lerp(fTimeDelta);
		m_tPosDownLerpZ.Update_Lerp(fTimeDelta);
		m_pTransformCom->Set_Pos({
			m_pTransformCom->Get_Info(INFO_POS).x,
			m_tPosDownLerpY.fCurValue,
			m_tPosDownLerpZ.fCurValue });

		if (!m_tPosDownLerpY.bActive)
		{
			CQuestMgr::GetInstance()->Set_ReadyNext();
			CEventMgr::GetInstance()->Delete_Obj(this);
			// 그럴 일은 없겠지만 혹시라도 다음 프레임에 못들어오게
			m_bDelete = true; 
		}

		m_tDustCreateLerp.Update_Lerp(fTimeDelta);
		if (!m_tDustCreateLerp.bActive)
		{
			CGameObject* pDust = CZeoliteDust::Create(m_pGraphicDev, this);
			NULL_CHECK_RETURN(pDust, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"ZeoliteDust", pDust);

			m_tDustCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tDustCreateLerp.Set_Lerp(0.25f, 1.f, 0.f);
		}
	}

	return iExit;
}

void CZeolite::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CZeolite::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fAlpha, 255, 255, 255));

	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGameObject::Render_Object(); // 콜라이더 출력
}

void CZeolite::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CZeolite::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
	}
	break;
	default:
		break;
	}
}

void CZeolite::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CZeolite::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_Zeolite", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CZeolite* CZeolite::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CZeolite* pInstance = new CZeolite(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_Zeolite Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZeolite::Free()
{
	CGameObject::Free();
}
