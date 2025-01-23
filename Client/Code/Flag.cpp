#include "stdafx.h"
#include "..\Header\Flag.h"
#include "EventMgr.h"
#include "Export_Function.h"
#include "FlagOwner.h"
#include "SoundMgr.h"
#include "EnterUI.h"

CFlag::CFlag(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::FLAG, _eID)
	, m_iCurIn(0)
	, m_iPrevIn(0)
	, m_fTranslucent(0.f)
	, m_eCurCollison(PLAYER_COLLISION2::NONE)
	, m_bCol(false) , m_bCreate(false), m_bDelete(false)
{

}

CFlag::CFlag(const CFlag& rhs)
	: Engine::CGameObject(rhs)
{
}

CFlag::~CFlag()
{
}

HRESULT CFlag::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 9.f, 9.f, 4.5f });

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_CHECK;

	// 투명도 러프 (생성, 소멸)
	m_tCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tCreateLerp.Set_Lerp(0.5f, 0.f, 255.f);
	m_tDeleteLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDeleteLerp.Set_Lerp(0.5f, 255.f, 0.f);

	m_bActive = false;

	return S_OK;
}

_int CFlag::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	Check_Player_Collision();

	if (PLAYER_COLLISION2::ENTER == m_eCurCollison)
		Enter_Player();
	else if (PLAYER_COLLISION2::EXIT == m_eCurCollison)
		Exit_Player();

	if (m_bCreate)
	{
		m_tCreateLerp.Update_Lerp(fTimeDelta);
		m_fTranslucent = m_tCreateLerp.fCurValue;
	}
	if (m_bDelete)
	{
		m_tDeleteLerp.Update_Lerp(fTimeDelta);
		m_fTranslucent = m_tDeleteLerp.fCurValue;
		if (!m_tDeleteLerp.bActive)
		{
			m_bActive = false;
		}
	}



	return iExit;
}

void CFlag::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFlag::Render_Object()
{
	_matrix matWorld = m_pTransformCom->Get_WorldMat();
	_matrix matBill;
	
	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	m_pTransformCom->Set_Rot({ D3DXToRadian(-50.f), 0.f, 0.f});

	m_pFlagTexCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

void CFlag::OnCollision_Enter(CGameObject* _pColObj)
{
	NULL_CHECK(m_pFlagOwner);
	m_pFlagOwner->Check_Player_Collision(m_eID);
	++m_iCurIn;
}

void CFlag::OnCollision_Stay(CGameObject* _pColObj)
{
	m_pFlagOwner->Check_Player_Collision(m_eID);

	//if (m_eFlagTag != FLAG_TAG::FLAG_START)
	//{
	//	CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
	//		(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
	//	m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
	//}
}

void CFlag::OnCollision_Exit(CGameObject* _pColObj)
{
	--m_iCurIn;
	//if (m_eFlagTag != FLAG_TAG::FLAG_START)
	//{
	//	// UI Off
	//	CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
	//		(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
	//
	//	m_pEnterUI->EnterUI_Off();
	//}

}

HRESULT CFlag::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Buffer
	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	// Rc Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);


	return S_OK;
}

HRESULT CFlag::Add_RangeObj()
{
	return S_OK;
}

void CFlag::Check_Player_Collision()
{
	if (0 == m_iPrevIn && 0 < m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION2::ENTER;
		m_iPrevIn = m_iCurIn;

		return;
	}
	else if (0 < m_iPrevIn && 0 == m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION2::EXIT;
		m_iPrevIn = m_iCurIn;

		return;
	}

	if (0 < m_iCurIn)
		m_eCurCollison = PLAYER_COLLISION2::STAY;
	else
		m_eCurCollison = PLAYER_COLLISION2::NONE;

	m_iPrevIn = m_iCurIn;

}

void CFlag::Enter_Player()
{

}

void CFlag::Exit_Player()
{

}

void CFlag::Free()
{
	__super::Free();
}
