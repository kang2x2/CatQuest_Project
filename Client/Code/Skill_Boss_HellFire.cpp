#include "Effect_Boss_HellFire.h"
#include "Export_Function.h"
#include "Skill_Boss_HellFire.h"
#include "EventMgr.h"
#include "Effect_Range_Quater.h"
#include "RangeObj.h"
#include "Player.h"
#include "SoundMgr.h"

CSkill_Boss_HellFire::CSkill_Boss_HellFire(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSkill(pGraphicDev, OBJ_ID::SKILL_BOSS_HELLFIRE)
{
}

CSkill_Boss_HellFire::CSkill_Boss_HellFire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_BOSS_HELLFIRE)
{
}

CSkill_Boss_HellFire::CSkill_Boss_HellFire(const CSkill_Boss_HellFire& rhs)
	:CSkill(rhs)
{
}

CSkill_Boss_HellFire::~CSkill_Boss_HellFire()
{
}

HRESULT CSkill_Boss_HellFire::Ready_Object()
{

	__super::Ready_Object();

	m_bActive = true;

	m_fSkillDamage = 30.f;

	m_bBaseEffectEnd = false;
	m_bSkillEffectEnd = false;


	// Naming
	m_szName = L"Skill_Boss_HellFire";


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
}

_int CSkill_Boss_HellFire::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	// Dead condition
	if (!m_pOwnerObject->Is_Active())
	{
		End();

		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect1);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect2);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect3);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect4);

		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect5);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect6);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect7);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect8);

		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect9);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect10);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect11);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect12);

		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect13);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect14);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect15);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect16);


		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect1);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect2);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect3);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect4);

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect5);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect6);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect7);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect8);

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect9);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect10);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect11);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect12);

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect13);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect14);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect15);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect16);
		
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	return iExit;
}

void CSkill_Boss_HellFire::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill_Boss_HellFire::Render_Object()
{
	__super::Render_Object();
}

void CSkill_Boss_HellFire::OnCollision_Enter(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
		dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fSkillDamage, this);
	}
	break;
	default:
	{
	}
	break;
	}

}

void CSkill_Boss_HellFire::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Boss_HellFire::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Boss_HellFire::Add_Component()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	// Skill Effect
	// Front
	CSkillEffect* pHellFire1 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire1", pHellFire1), E_FAIL);
	m_pSKillEffect1 = pHellFire1;
	
	CSkillEffect* pHellFire2 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire2", pHellFire2), E_FAIL);
	m_pSKillEffect2 = pHellFire2;

	CSkillEffect* pHellFire3 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire3", pHellFire3), E_FAIL);
	m_pSKillEffect3 = pHellFire3;

	CSkillEffect* pHellFire4 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire4", pHellFire4), E_FAIL);
	m_pSKillEffect4 = pHellFire4;

	// Right
	CSkillEffect* pHellFire5 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire5", pHellFire5), E_FAIL);
	m_pSKillEffect5 = pHellFire5;

	CSkillEffect* pHellFire6 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire6, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire6", pHellFire6), E_FAIL);
	m_pSKillEffect6 = pHellFire6;

	CSkillEffect* pHellFire7 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire7, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire7", pHellFire7), E_FAIL);
	m_pSKillEffect7 = pHellFire7;

	CSkillEffect* pHellFire8 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire8, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire8", pHellFire8), E_FAIL);
	m_pSKillEffect8 = pHellFire8;

	// Left
	CSkillEffect* pHellFire9 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire9, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire9", pHellFire9), E_FAIL);
	m_pSKillEffect9 = pHellFire9;

	CSkillEffect* pHellFire10 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire10, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire10", pHellFire10), E_FAIL);
	m_pSKillEffect10 = pHellFire10;

	CSkillEffect* pHellFire11 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire11, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire11", pHellFire11), E_FAIL);
	m_pSKillEffect11 = pHellFire11;

	CSkillEffect* pHellFire12 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire12, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire12", pHellFire12), E_FAIL);
	m_pSKillEffect12 = pHellFire12;

	// Back
	CSkillEffect* pHellFire13 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire13, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire13", pHellFire13), E_FAIL);
	m_pSKillEffect13 = pHellFire13;

	CSkillEffect* pHellFire14 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire14, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire14", pHellFire14), E_FAIL);
	m_pSKillEffect14 = pHellFire14;

	CSkillEffect* pHellFire15 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire15, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire15", pHellFire15), E_FAIL);
	m_pSKillEffect15 = pHellFire15;

	CSkillEffect* pHellFire16 = CEffect_Boss_HellFire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pHellFire16, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss_HellFire16", pHellFire16), E_FAIL);
	m_pSKillEffect16 = pHellFire16;





	// Effect Range Quater - Base
	// Front
	m_pBaseRangeEffect1 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base1", m_pBaseRangeEffect1), E_FAIL);

	m_pBaseRangeEffect2 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base2", m_pBaseRangeEffect2), E_FAIL);

	m_pBaseRangeEffect3 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base3", m_pBaseRangeEffect3), E_FAIL);
	
	m_pBaseRangeEffect4 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base4", m_pBaseRangeEffect4), E_FAIL);

	// Right
	m_pBaseRangeEffect5 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base5", m_pBaseRangeEffect5), E_FAIL);

	m_pBaseRangeEffect6 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect6, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base6", m_pBaseRangeEffect6), E_FAIL);

	m_pBaseRangeEffect7 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect7, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base7", m_pBaseRangeEffect7), E_FAIL);

	m_pBaseRangeEffect8 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect8, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base8", m_pBaseRangeEffect8), E_FAIL);


	// Left
	m_pBaseRangeEffect9 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect9, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base9", m_pBaseRangeEffect9), E_FAIL);

	m_pBaseRangeEffect10 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect10, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base10", m_pBaseRangeEffect10), E_FAIL);

	m_pBaseRangeEffect11 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect11, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base11", m_pBaseRangeEffect11), E_FAIL);

	m_pBaseRangeEffect12 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect12, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base12", m_pBaseRangeEffect12), E_FAIL);



	// Back
	m_pBaseRangeEffect13 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect13, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base13", m_pBaseRangeEffect13), E_FAIL);

	m_pBaseRangeEffect14 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect14, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base14", m_pBaseRangeEffect14), E_FAIL);

	m_pBaseRangeEffect15 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect15, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base15", m_pBaseRangeEffect15), E_FAIL);

	m_pBaseRangeEffect16 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE);
	NULL_CHECK_RETURN(m_pBaseRangeEffect16, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_HellFire_Base16", m_pBaseRangeEffect16), E_FAIL);





	// RangeObj
	// Front
	// 1
	CRangeObj* pGameObject1 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere1 = dynamic_cast<CSphereCollider*>(pGameObject1->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere1->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject1, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere1", pGameObject1);
	m_pRangeObj1 = pGameObject1;
	dynamic_cast<CRangeObj*>(m_pRangeObj1)->Set_Pos( _vec3{ vOwnerPos.x - 10.f, 0.01f, vOwnerPos.z + 10.f } );
	m_pRangeObj1->Set_Active(false);

	
	// 2
	CRangeObj* pGameObject2 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere2 = dynamic_cast<CSphereCollider*>(pGameObject2->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere2->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject2, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere2", pGameObject2);
	m_pRangeObj2 = pGameObject2;
	dynamic_cast<CRangeObj*>(m_pRangeObj2)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj2->Set_Active(false);

	// 3
	CRangeObj* pGameObject3 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere3 = dynamic_cast<CSphereCollider*>(pGameObject3->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere3->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject3, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere3", pGameObject3);
	m_pRangeObj3 = pGameObject3;
	dynamic_cast<CRangeObj*>(m_pRangeObj3)->Set_Pos(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z - 10.f });

	// 4
	CRangeObj* pGameObject4 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere4 = dynamic_cast<CSphereCollider*>(pGameObject4->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere4->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject4, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere4", pGameObject4);
	m_pRangeObj4 = pGameObject4;
	dynamic_cast<CRangeObj*>(m_pRangeObj4)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z - 10.f } );


	// Right
	// 5
	CRangeObj* pGameObject5 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere5 = dynamic_cast<CSphereCollider*>(pGameObject5->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere5->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject5, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere5", pGameObject5);
	m_pRangeObj5 = pGameObject5;
	dynamic_cast<CRangeObj*>(m_pRangeObj5)->Set_Pos(_vec3{ vOwnerPos.x - 10.f, 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj5->Set_Active(false);


	// 6
	CRangeObj* pGameObject6 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere6 = dynamic_cast<CSphereCollider*>(pGameObject6->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere6->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject6, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere6", pGameObject6);
	m_pRangeObj6 = pGameObject6;
	dynamic_cast<CRangeObj*>(m_pRangeObj6)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj6->Set_Active(false);

	// 7
	CRangeObj* pGameObject7 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere7 = dynamic_cast<CSphereCollider*>(pGameObject7->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere7->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject7, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere7", pGameObject7);
	m_pRangeObj7 = pGameObject7;
	dynamic_cast<CRangeObj*>(m_pRangeObj7)->Set_Pos(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z - 10.f });



	// 8
	CRangeObj* pGameObject8 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere8 = dynamic_cast<CSphereCollider*>(pGameObject8->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere8->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject8, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere8", pGameObject8);
	m_pRangeObj8 = pGameObject8;
	dynamic_cast<CRangeObj*>(m_pRangeObj8)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z - 10.f });


	// Left
	// 9
	CRangeObj* pGameObject9 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere9 = dynamic_cast<CSphereCollider*>(pGameObject9->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere9->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject9, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere9", pGameObject9);
	m_pRangeObj9 = pGameObject9;
	dynamic_cast<CRangeObj*>(m_pRangeObj9)->Set_Pos(_vec3{ vOwnerPos.x - 10.f, 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj9->Set_Active(false);


	// 10
	CRangeObj* pGameObject10 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere10 = dynamic_cast<CSphereCollider*>(pGameObject10->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere10->Set_Radius(7.f); 
	NULL_CHECK_RETURN(pGameObject10, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere10", pGameObject10);
	m_pRangeObj10 = pGameObject10;
	dynamic_cast<CRangeObj*>(m_pRangeObj10)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj10->Set_Active(false);

	// 11
	CRangeObj* pGameObject11 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere11 = dynamic_cast<CSphereCollider*>(pGameObject11->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere11->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject11, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere11", pGameObject11);
	m_pRangeObj11 = pGameObject11;
	dynamic_cast<CRangeObj*>(m_pRangeObj11)->Set_Pos(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z - 10.f });

	// 12
	CRangeObj* pGameObject12 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere12 = dynamic_cast<CSphereCollider*>(pGameObject12->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere12->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject12, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere12", pGameObject12);
	m_pRangeObj12 = pGameObject12;
	dynamic_cast<CRangeObj*>(m_pRangeObj12)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z - 10.f });


	// Back
	// 13
	CRangeObj* pGameObject13 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere13 = dynamic_cast<CSphereCollider*>(pGameObject13->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere13->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject13, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere13", pGameObject13);
	m_pRangeObj13 = pGameObject13;
	dynamic_cast<CRangeObj*>(m_pRangeObj13)->Set_Pos(_vec3{ vOwnerPos.x - 10.f, 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj13->Set_Active(false);


	// 14
	CRangeObj* pGameObject14 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere14 = dynamic_cast<CSphereCollider*>(pGameObject14->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere14->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject14, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere14", pGameObject14);
	m_pRangeObj14 = pGameObject14;
	dynamic_cast<CRangeObj*>(m_pRangeObj14)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z + 10.f });
	m_pRangeObj14->Set_Active(false);

	// 15
	CRangeObj* pGameObject15 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere15 = dynamic_cast<CSphereCollider*>(pGameObject15->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere15->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject15, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere15", pGameObject15);
	m_pRangeObj15 = pGameObject15;
	dynamic_cast<CRangeObj*>(m_pRangeObj15)->Set_Pos(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z - 10.f });

	// 16
	CRangeObj* pGameObject16 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere16 = dynamic_cast<CSphereCollider*>(pGameObject16->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere16->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject16, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere16", pGameObject16);
	m_pRangeObj16 = pGameObject16;
	dynamic_cast<CRangeObj*>(m_pRangeObj16)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z - 10.f });



	return S_OK;


}

HRESULT CSkill_Boss_HellFire::EarlyPlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	//// Player - Transform Com
	//CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	//// Player - Pos
	//_vec3       vPlayerPos;
	//vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);


	


	// Front
	// 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z - 10.f });
	m_pBaseRangeEffect1->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect1->Scaling(1.f, 0.1f, 0.3f);

	// 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z - 20.f });
	m_pBaseRangeEffect2->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect2->Scaling(1.2f, 0.1f, 0.5f);

	// 3
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z - 30.f });
	m_pBaseRangeEffect3->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect3->Scaling(1.4f, 0.5f, 0.7f);

	// 4
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z - 40.f });
	m_pBaseRangeEffect4->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect4->Scaling(1.6f, 0.8f, 1.f);



	// Right
	// 5
	m_pBaseRangeEffect5->Play_Effect(_vec3{ vOwnerPos.x + 10.f, 0.01f, vOwnerPos.z  });
	m_pBaseRangeEffect5->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect5->Scaling(1.f, 0.1f, 0.3f);

	// 6
	m_pBaseRangeEffect6->Play_Effect(_vec3{ vOwnerPos.x + 20.f, 0.01f, vOwnerPos.z  });
	m_pBaseRangeEffect6->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect6->Scaling(1.2f, 0.1f, 0.5f);

	// 7
	m_pBaseRangeEffect7->Play_Effect(_vec3{ vOwnerPos.x + 30.f , 0.01f, vOwnerPos.z  });
	m_pBaseRangeEffect7->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect7->Scaling(1.4f, 0.5f, 0.7f);

	// 8
	m_pBaseRangeEffect8->Play_Effect(_vec3{ vOwnerPos.x + 40.f , 0.01f, vOwnerPos.z  });
	m_pBaseRangeEffect8->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect8->Scaling(1.6f, 0.8f, 1.f);


	// Left
	// 9
	m_pBaseRangeEffect9->Play_Effect(_vec3{ vOwnerPos.x - 10.f, 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect9->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect9->Scaling(1.f, 0.1f, 0.3f);

	// 10
	m_pBaseRangeEffect10->Play_Effect(_vec3{ vOwnerPos.x - 20.f, 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect10->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect10->Scaling(1.2f, 0.1f, 0.5f);

	// 11
	m_pBaseRangeEffect11->Play_Effect(_vec3{ vOwnerPos.x - 30.f , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect11->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect11->Scaling(1.4f, 0.5f, 0.7f);
	
	// 12
	m_pBaseRangeEffect12->Play_Effect(_vec3{ vOwnerPos.x - 40.f , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect12->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect12->Scaling(1.6f, 0.8f, 1.f);


	// Back
	// 13
	m_pBaseRangeEffect13->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z  + 10.f});
	m_pBaseRangeEffect13->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect13->Scaling(1.f, 0.1f, 0.3f);

	// 14
	m_pBaseRangeEffect14->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z + 20.f });
	m_pBaseRangeEffect14->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect14->Scaling(1.2f, 0.1f, 0.5f);

	// 15
	m_pBaseRangeEffect15->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z  + 30.f});
	m_pBaseRangeEffect15->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect15->Scaling(1.4f, 0.5f, 0.7f);

	// 16
	m_pBaseRangeEffect16->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z + 40.f });
	m_pBaseRangeEffect16->Alphaing(1.f, 80.f, 255.f);
	m_pBaseRangeEffect16->Scaling(1.6f, 0.8f, 1.f);





	m_bActive = true;

	return S_OK;
}

HRESULT CSkill_Boss_HellFire::Play()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	//// Player - Transform Com
	//CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	//// Player - Pos
	//_vec3       vPlayerPos;
	//vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);


	m_pBaseRangeEffect1->Set_Active(false);
	m_pBaseRangeEffect5->Set_Active(false);
	m_pBaseRangeEffect9->Set_Active(false);
	m_pBaseRangeEffect13->Set_Active(false);


	m_pSKillEffect1->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z - 10.f } );
	m_pSKillEffect5->Play_Effect(_vec3{ vOwnerPos.x + 10.f , 0.01f  , vOwnerPos.z  });
	m_pSKillEffect9->Play_Effect(_vec3{ vOwnerPos.x - 10.f , 0.01f  , vOwnerPos.z  });
	m_pSKillEffect13->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z +10.f });



	//m_pRangeObj1->Set_Active(true);
	//dynamic_cast<CRangeObj*>(m_pRangeObj1)->Set_Pos(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z -10.f });

	//m_pRangeObj5->Set_Active(true);
	//dynamic_cast<CRangeObj*>(m_pRangeObj5)->Set_Pos(_vec3{ vOwnerPos.x +10.f , 0.01f, vOwnerPos.z });

	//m_pRangeObj9->Set_Active(true);
	//dynamic_cast<CRangeObj*>(m_pRangeObj9)->Set_Pos(_vec3{ vOwnerPos.x -10.f, 0.01f, vOwnerPos.z });

	//m_pRangeObj13->Set_Active(true);
	//dynamic_cast<CRangeObj*>(m_pRangeObj13)->Set_Pos(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z + 10.f });

	m_bActive = true;


	return S_OK;


}

HRESULT CSkill_Boss_HellFire::LatePlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	//// Player - Transform Com
	//CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	//// Player - Pos
	//_vec3       vPlayerPos;
	//vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	m_pBaseRangeEffect2->Set_Active(false);
	m_pBaseRangeEffect6->Set_Active(false);
	m_pBaseRangeEffect10->Set_Active(false);
	m_pBaseRangeEffect14->Set_Active(false);


	m_pSKillEffect2->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z - 20.f }, _vec3{1.3f, 1.3f, 1.3f});
	m_pSKillEffect6->Play_Effect(_vec3{ vOwnerPos.x + 20.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.3f, 1.3f, 1.3f });
	m_pSKillEffect10->Play_Effect(_vec3{ vOwnerPos.x - 20.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.3f, 1.3f, 1.3f });
	m_pSKillEffect14->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z + 20.f }, _vec3{ 1.3f, 1.3f, 1.3f });

	m_bActive = true;

	return S_OK;
}

HRESULT CSkill_Boss_HellFire::LastPlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	//// Player - Transform Com
	//CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	//// Player - Pos
	//_vec3       vPlayerPos;
	//vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);



	m_pBaseRangeEffect3->Set_Active(false);
	m_pBaseRangeEffect7->Set_Active(false);
	m_pBaseRangeEffect11->Set_Active(false);
	m_pBaseRangeEffect15->Set_Active(false);


	m_pSKillEffect3->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z - 30.f }, _vec3{ 1.5f, 1.5f, 1.5f });
	m_pSKillEffect7->Play_Effect(_vec3{ vOwnerPos.x + 30.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.5f, 1.5f, 1.5f });
	m_pSKillEffect11->Play_Effect(_vec3{ vOwnerPos.x - 30.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.5f, 1.5f, 1.5f });
	m_pSKillEffect15->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z + 30.f }), _vec3{ 1.5f, 1.5f, 1.5f };
	

	m_bActive = true;

	return S_OK;
}

HRESULT CSkill_Boss_HellFire::FinalPlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	//// Player - Transform Com
	//CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	//// Player - Pos
	//_vec3       vPlayerPos;
	//vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	//NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);



	m_pBaseRangeEffect4->Set_Active(false);
	m_pBaseRangeEffect8->Set_Active(false);
	m_pBaseRangeEffect12->Set_Active(false);
	m_pBaseRangeEffect16->Set_Active(false);


	m_pSKillEffect4->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z - 40.f }, _vec3{ 1.7f, 1.7f, 1.7f });
	m_pSKillEffect8->Play_Effect(_vec3{ vOwnerPos.x + 40.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.7f, 1.7f, 1.7f });
	m_pSKillEffect12->Play_Effect(_vec3{ vOwnerPos.x - 40.f , 0.01f  , vOwnerPos.z }, _vec3{ 1.7f, 1.7f, 1.7f });
	m_pSKillEffect16->Play_Effect(_vec3{ vOwnerPos.x, 0.01f  , vOwnerPos.z + 40.f }, _vec3{ 1.7f, 1.7f, 1.7f });


	m_bActive = true;

	return S_OK;
}

HRESULT CSkill_Boss_HellFire::EarlyEnd()
{
	return S_OK;
}

HRESULT CSkill_Boss_HellFire::End()
{
	// m_bActive = true;

	m_pBaseRangeEffect1->Set_Active(false);
	m_pBaseRangeEffect5->Set_Active(false);
	m_pBaseRangeEffect9->Set_Active(false);
	m_pBaseRangeEffect13->Set_Active(false);



	m_pBaseRangeEffect2->Set_Active(false);
	m_pBaseRangeEffect6->Set_Active(false);
	m_pBaseRangeEffect10->Set_Active(false);
	m_pBaseRangeEffect14->Set_Active(false);


	m_pBaseRangeEffect3->Set_Active(false);
	m_pBaseRangeEffect7->Set_Active(false);
	m_pBaseRangeEffect11->Set_Active(false);
	m_pBaseRangeEffect15->Set_Active(false);


	m_pBaseRangeEffect4->Set_Active(false);
	m_pBaseRangeEffect8->Set_Active(false);
	m_pBaseRangeEffect12->Set_Active(false);
	m_pBaseRangeEffect16->Set_Active(false);

	m_bActive = true;
	return S_OK;
}

HRESULT CSkill_Boss_HellFire::LateEnd()
{
	

	return S_OK;
}

HRESULT CSkill_Boss_HellFire::LastEnd()
{
	return S_OK;
}

HRESULT CSkill_Boss_HellFire::FinalEnd()
{
	return S_OK;
}

CSkill_Boss_HellFire* CSkill_Boss_HellFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSkill_Boss_HellFire* pInstance = new CSkill_Boss_HellFire(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CSkill_Boss_HellFire Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkill_Boss_HellFire::Free()
{
	__super::Free();
}
