#include "stdafx.h"
#include "..\Header\Island_Death.h"

#include "Export_Function.h"

#include "RangeObj.h"
#include "DungeonTextUI.h"

#include "SoundMgr.h"
#include "EffectGenerator.h"

CIsland_Death::CIsland_Death(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIsland(pGraphicDev, OBJ_ID::ISLAND_RANGE_DEATH)
{
}
CIsland_Death::CIsland_Death(const CIsland_Death& rhs)
	: CIsland(rhs)
{

}
CIsland_Death::~CIsland_Death()
{
}

HRESULT CIsland_Death::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 220.f, 0.f , 384.f });

	m_szName = L"Island_Death";

	return S_OK;
}

Engine::_int CIsland_Death::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIsland_Death::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland_Death::Render_Object(void)
{
	__super::Render_Object();
}

HRESULT CIsland_Death::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CIsland_Death::Add_RangeObj()
{
	CRangeObj* pGameObject = nullptr;

	// 01
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_Death_RangeObj_01", pGameObject);
	pGameObject->Set_Radius(110.f);
	pGameObject->Set_Pos(_vec3{ 520.f, 0.f , 520.f });
	m_vecRangeObj.push_back(pGameObject);

	return S_OK;
}



void CIsland_Death::Enter_Player()
{
	// 플레이어가 해당 섬에 처음 들어왔을 때

	// Action : 대륙 이름 UI, 플레이어 미끄러짐, 브금 변경, 눈 이펙트 On
	Engine::CGameObject* pGameObject = nullptr;
	pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
	NULL_CHECK(pGameObject);
	CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject);

	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_drakoth_theme_short.wav", BGM_TYPE::ISLAND_DEATH);

	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);

}

void CIsland_Death::Stay_Player()
{
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_Death::Exit_Player()
{
	// 플레이어가 해당 섬에서 나갔을 때
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(OBJ_ID::TYPEEND);
}

void CIsland_Death::Free()
{
	__super::Free();
}

CIsland_Death* CIsland_Death::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsland_Death* pInstance = new CIsland_Death(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Island_Death Create Failed");
		return nullptr;
	}

	return pInstance;
}
