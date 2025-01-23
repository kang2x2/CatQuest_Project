#include "stdafx.h"
#include "..\Header\Island_Ice.h"

#include "Export_Function.h"

#include "Management.h"
#include "Player.h"
#include "RangeObj.h"
#include "DungeonTextUI.h"
#include "SoundMgr.h"
#include "EffectGenerator.h"
CIsland_Ice::CIsland_Ice(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIsland(pGraphicDev, OBJ_ID::ISLAND_RANGE_ICE)
{
}
CIsland_Ice::CIsland_Ice(const CIsland_Ice& rhs)
	: CIsland(rhs)
{

}
CIsland_Ice::~CIsland_Ice()
{
}

HRESULT CIsland_Ice::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 220.f, 0.f , 384.f });

	m_szName = L"Island_Ice";

	return S_OK;
}

Engine::_int CIsland_Ice::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIsland_Ice::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland_Ice::Render_Object(void)
{
	__super::Render_Object();
}

HRESULT CIsland_Ice::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CIsland_Ice::Add_RangeObj()
{
	CRangeObj* pGameObject = nullptr;
	
	// 01
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Ice_RangeObj_01", pGameObject);
	pGameObject->Set_Radius(55.f);
	pGameObject->Set_Pos(_vec3{ 140.f, 0.f , 364.f });
	m_vecRangeObj.push_back(pGameObject);

	// 02
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Ice_RangeObj_02", pGameObject);
	pGameObject->Set_Radius(63.f);
	pGameObject->Set_Pos(_vec3{ 228.f, 0.f , 390.f });
	m_vecRangeObj.push_back(pGameObject);

	// 03
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Ice_RangeObj_03", pGameObject);
	pGameObject->Set_Radius(48.f);
	pGameObject->Set_Pos(_vec3{ 290.f, 0.f , 420.f });
	m_vecRangeObj.push_back(pGameObject);

	return S_OK;
}

void CIsland_Ice::Enter_Player()
{
	// 플레이어가 해당 섬에 처음 들어왔을 때

	// Action : 대륙 이름 UI, 플레이어 미끄러짐, 브금 변경, 눈 이펙트 On
	
	CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_BACK_TO_TOP);


	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());

	NULL_CHECK(pPlayer);

	pPlayer->Set_CurGroudType(GROUND_TYPE::ICE);


	Engine::CGameObject* pGameObject = nullptr;
	pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
	NULL_CHECK(pGameObject);
	CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject);

	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_calm_theme.wav", BGM_TYPE::ISLAND_ICE);


	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Ice::Stay_Player()
{
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Ice::Exit_Player()
{
	// 플레이어가 해당 섬에서 나갔을 때

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());

	NULL_CHECK(pPlayer);

	pPlayer->Set_CurGroudType(GROUND_TYPE::NORMAL);
	
	//pPlayer->Get_RigidBody()->Set_MaxSpeed_By_Df();
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(OBJ_ID::TYPEEND);
}

void CIsland_Ice::Free()
{
	__super::Free();
}

CIsland_Ice* CIsland_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsland_Ice* pInstance = new CIsland_Ice(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Island_Ice Create Failed");
		return nullptr;
	}

	return pInstance;
}
