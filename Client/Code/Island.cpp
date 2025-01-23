#include "stdafx.h"
#include "..\Header\Island.h"

#include "Export_Function.h"

#include "RangeObj.h"

CIsland::CIsland(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ISLAND, _eID)
	, m_iCurIn(0)
	, m_iPrevIn(0)
	, m_eCurCollison(PLAYER_COLLISION::NONE)
{
}
CIsland::CIsland(const CIsland& rhs)
	: Engine::CGameObject(rhs)
{

}
CIsland::~CIsland()
{
}

HRESULT CIsland::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CIsland::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	Check_Player_Collision();

	if (PLAYER_COLLISION::ENTER == m_eCurCollison)
		Enter_Player();
	else if (PLAYER_COLLISION::EXIT == m_eCurCollison)
		Exit_Player();
	else if (PLAYER_COLLISION::STAY == m_eCurCollison)
		Stay_Player();

	return iExit;
}

void CIsland::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	__super::Render_Object();
}

void CIsland::OnCollision_Enter(CGameObject* _pColObj)
{
	++m_iCurIn;
}

void CIsland::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CIsland::OnCollision_Exit(CGameObject* _pColObj)
{
	--m_iCurIn;
}

HRESULT CIsland::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CIsland::Add_RangeObj()
{
	return S_OK;
}

void CIsland::Check_Player_Collision()
{
	if (0 == m_iPrevIn && 0 < m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION::ENTER;
		m_iPrevIn = m_iCurIn;

		return;
	}
	else if (0 < m_iPrevIn && 0 == m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION::EXIT;
		m_iPrevIn = m_iCurIn;

		return;
	}

	if(0 < m_iCurIn)
		m_eCurCollison = PLAYER_COLLISION::STAY;
	else
		m_eCurCollison = PLAYER_COLLISION::NONE;

	m_iPrevIn = m_iCurIn;
}

void CIsland::Enter_Player()
{
	// 플레이어가 해당 섬에 처음 들어왔을 때
}

void CIsland::Exit_Player()
{
	// 플레이어가 해당 섬에서 나갔을 때
}

void CIsland::Free()
{
	__super::Free();
}

//CIsland* CIsland::Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
//{
//	CIsland* pInstance = new CIsland(pGraphicDev, _eID);
//
//	if (FAILED(pInstance->Ready_Object()))
//	{
//		Safe_Release(pInstance);
//
//		MSG_BOX("Island Create Failed");
//		return nullptr;
//	}
//
//	return pInstance;
//}
