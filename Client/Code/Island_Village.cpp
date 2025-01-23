#include "stdafx.h"
#include "..\Header\Island_Village.h"

#include "Export_Function.h"

#include "EffectGenerator.h"
#include "RangeObj.h"
#include "DungeonTextUI.h"
#include "SoundMgr.h"
CIsland_Village::CIsland_Village(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIsland(pGraphicDev, OBJ_ID::ISLAND_RANGE_VILLAGE)
{
}
CIsland_Village::CIsland_Village(const CIsland_Village& rhs)
	: CIsland(rhs)
{

}
CIsland_Village::~CIsland_Village()
{
}

HRESULT CIsland_Village::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 220.f, 0.f , 384.f });

	m_szName = L"Island_Village";

	return S_OK;
}

Engine::_int CIsland_Village::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIsland_Village::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland_Village::Render_Object(void)
{
	__super::Render_Object();
}

HRESULT CIsland_Village::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CIsland_Village::Add_RangeObj()
{
	CRangeObj* pGameObject = nullptr;

	// 01
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Village_RangeObj_01", pGameObject);
	pGameObject->Set_Radius(115.f);
	pGameObject->Set_Pos(_vec3{ START_POS_WORLD_X + 70.f, 0.f , START_POS_WORLD_Z + 70.f });
	m_vecRangeObj.push_back(pGameObject);

	//// 02
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Village_RangeObj_02", pGameObject);
	pGameObject->Set_Radius(125.f);
	pGameObject->Set_Pos(_vec3{ START_POS_WORLD_X - 57.f, 0.f , START_POS_WORLD_Z + 7.f });
	m_vecRangeObj.push_back(pGameObject);

	return S_OK;
}

void CIsland_Village::Enter_Player()
{

	if (!CCameraMgr::GetInstance()->Is_BackView())
	{
		Engine::CGameObject* pGameObject = nullptr;
		pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
		NULL_CHECK(pGameObject);
		CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject);
		CSoundMgr::GetInstance()->ChangeBGM(L"catquest_overworld_02_theme.wav", BGM_TYPE::ISLAND_VILLAGE);
	}


	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Village::Stay_Player()
{
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Village::Exit_Player()
{
	// 플레이어가 해당 섬에서 나갔을 때
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(OBJ_ID::TYPEEND);
}

void CIsland_Village::Free()
{
	__super::Free();
}

CIsland_Village* CIsland_Village::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsland_Village* pInstance = new CIsland_Village(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Island_Village Create Failed");
		return nullptr;
	}

	return pInstance;
}
