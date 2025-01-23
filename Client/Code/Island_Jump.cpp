#include "stdafx.h"
#include "..\Header\Island_Jump.h"

#include "Export_Function.h"

#include "RangeObj.h"
#include "EffectGenerator.h"

CIsland_Jump::CIsland_Jump(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIsland(pGraphicDev, OBJ_ID::ISLAND_RANGE_JUMP)
{
}
CIsland_Jump::CIsland_Jump(const CIsland_Jump& rhs)
	: CIsland(rhs)
{

}
CIsland_Jump::~CIsland_Jump()
{
}

HRESULT CIsland_Jump::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 220.f, 0.f , 384.f });

	m_szName = L"Island_Jump";

	return S_OK;
}

Engine::_int CIsland_Jump::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIsland_Jump::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland_Jump::Render_Object(void)
{
	__super::Render_Object();
}

HRESULT CIsland_Jump::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}


HRESULT CIsland_Jump::Add_RangeObj()
{
	CRangeObj* pGameObject = nullptr;

	// 00
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_00", pGameObject);
	pGameObject->Set_Radius(33.f);
	pGameObject->Set_Pos(_vec3{ 370.f, 0.f , 270.f });
	m_vecRangeObj.push_back(pGameObject);

	// 01
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_01", pGameObject);
	pGameObject->Set_Radius(6.f);
	pGameObject->Set_Pos(_vec3{ 339.f, 0.f , 295.f });
	m_vecRangeObj.push_back(pGameObject);

	// 02
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_02", pGameObject);
	pGameObject->Set_Radius(7.f);
	pGameObject->Set_Pos(_vec3{ 345.f, 0.f , 308.f });
	m_vecRangeObj.push_back(pGameObject);

	// 03
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_03", pGameObject);
	pGameObject->Set_Radius(7.f);
	pGameObject->Set_Pos(_vec3{ 333.f, 0.f , 318.f });
	m_vecRangeObj.push_back(pGameObject);

	// 04
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_04", pGameObject);
	pGameObject->Set_Radius(8.f);
	pGameObject->Set_Pos(_vec3{ 346.f, 0.f , 327.f });
	m_vecRangeObj.push_back(pGameObject);

	// 05
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_05", pGameObject);
	pGameObject->Set_Radius(8.f);
	pGameObject->Set_Pos(_vec3{ 333.f, 0.f , 338.f });
	m_vecRangeObj.push_back(pGameObject);

	// 06
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_06", pGameObject);
	pGameObject->Set_Radius(9.f);
	pGameObject->Set_Pos(_vec3{ 320.f, 0.f , 350.f });
	m_vecRangeObj.push_back(pGameObject);

	// 07
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_07", pGameObject);
	pGameObject->Set_Radius(8.f);
	pGameObject->Set_Pos(_vec3{ 303.f, 0.f , 360.f });
	m_vecRangeObj.push_back(pGameObject);

	// 08
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Jump_RangeObj_08", pGameObject);
	pGameObject->Set_Radius(30.f);
	pGameObject->Set_Pos(_vec3{ 280.f, 0.f , 380.f });
	m_vecRangeObj.push_back(pGameObject);
	return S_OK;
}

void CIsland_Jump::Enter_Player()
{
	// 플레이어가 해당 섬에 처음 들어왔을 때

	// Action : 대륙 이름 UI, 플레이어 미끄러짐, 브금 변경, 눈 이펙트 On
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Jump::Stay_Player()
{
}

void CIsland_Jump::Exit_Player()
{
	// 플레이어가 해당 섬에서 나갔을 때
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(OBJ_ID::TYPEEND);
}

void CIsland_Jump::Free()
{
	__super::Free();
}

CIsland_Jump* CIsland_Jump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsland_Jump* pInstance = new CIsland_Jump(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Island_Jump Create Failed");
		return nullptr;
	}

	return pInstance;
}
