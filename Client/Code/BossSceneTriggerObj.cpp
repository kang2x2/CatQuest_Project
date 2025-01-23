#include "stdafx.h"
#include "..\Header\BossSceneTriggerObj.h"

#include "Export_Function.h"

#include "Management.h"
#include "RangeObj.h"
#include "BossSceneMgr.h"
#include "Player.h"

CBossSceneTriggerObj::CBossSceneTriggerObj(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev, OBJ_TYPE::TRIGGER, OBJ_ID::BOSS_SCENE_TRIGGER)
	, m_bInPlayer(FALSE)
	, m_pRangeObj(nullptr)
{
}
CBossSceneTriggerObj::CBossSceneTriggerObj(const CBossSceneTriggerObj& rhs)
	: CGameObject(rhs)
{

}
CBossSceneTriggerObj::~CBossSceneTriggerObj()
{
}

HRESULT CBossSceneTriggerObj::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ BOSS_POS_X, 0.f , BOSS_POS_Z - 30.f }); 

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_szName = L"BossSceneTriggerObj";

	return S_OK;
}

Engine::_int CBossSceneTriggerObj::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	
	return iExit;
}

void CBossSceneTriggerObj::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
	
	if (m_bInPlayer)
	{
		CBossSceneMgr::GetInstance()->Start_BossScene();

		CPlayer* pPlayer = static_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());
		pPlayer->Block_Input(TRUE);

		CEventMgr::GetInstance()->Delete_Obj(this);
	}
}

void CBossSceneTriggerObj::Render_Object(void)
{
	__super::Render_Object();
}

void CBossSceneTriggerObj::OnCollision_Enter(CGameObject* _pColObj)
{
	m_bInPlayer = TRUE;
}

void CBossSceneTriggerObj::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBossSceneTriggerObj::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBossSceneTriggerObj::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CBossSceneTriggerObj::Add_RangeObj()
{
	// 01
	m_pRangeObj = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(m_pRangeObj, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"BossSceneTriggerObj_RangeObj", m_pRangeObj);

	m_pRangeObj->Set_Radius(10.f);
	m_pRangeObj->Set_Pos(_vec3{ m_pTransformCom->Get_Info(INFO_POS).x, 0.f , m_pTransformCom->Get_Info(INFO_POS).z });

	return S_OK;
}



void CBossSceneTriggerObj::Free()
{
	__super::Free();
}

CBossSceneTriggerObj* CBossSceneTriggerObj::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossSceneTriggerObj* pInstance = new CBossSceneTriggerObj(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Boss Scene Rigger Obj Create Failed");
		return nullptr;
	}

	return pInstance;
}
