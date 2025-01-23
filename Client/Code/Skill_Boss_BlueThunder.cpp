#include "Skill_Boss_BlueThunder.h"
#include "Export_Function.h"
#include "Effect_Boss_Thunder.h"
#include "Effect_Boss_ThunderBlue.h"
#include "EventMgr.h"
#include "Effect_Range_Quater.h"
#include "Player.h"
#include "RangeObj.h"

CSkill_Boss_BlueThunder::CSkill_Boss_BlueThunder(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSkill(pGraphicDev, OBJ_ID::SKILL_BOSS_BLUETHUNDER)
{
}

CSkill_Boss_BlueThunder::CSkill_Boss_BlueThunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_BOSS_BLUETHUNDER)
{
}

CSkill_Boss_BlueThunder::CSkill_Boss_BlueThunder(const CSkill_Boss_BlueThunder& rhs)
	:CSkill(rhs)
{
}

CSkill_Boss_BlueThunder::~CSkill_Boss_BlueThunder()
{
}

HRESULT CSkill_Boss_BlueThunder::Ready_Object()
{

	__super::Ready_Object();

	m_bActive = false;
	m_fSkillDamage = 40;

	m_bBaseEffectEnd = false;
	m_bSkillEffectEnd = false;


	// Naming
	m_szName = L"Skill_Boss_BlueThunder";


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
}

_int CSkill_Boss_BlueThunder::Update_Object(const _float& fTimeDelta)
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

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect1);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect2);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect3);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect4);

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect5);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect6);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect7);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect8);
		

		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	// Pos Setting
	//_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
	//m_pTransformCom->Set_Pos(vPos);




	return iExit;
}

void CSkill_Boss_BlueThunder::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill_Boss_BlueThunder::Render_Object()
{
	__super::Render_Object();
}

void CSkill_Boss_BlueThunder::OnCollision_Enter(CGameObject* _pColObj)
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

void CSkill_Boss_BlueThunder::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Boss_BlueThunder::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Boss_BlueThunder::Add_Component()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);


	// Skill Effect
	CSkillEffect* pThunderEffect1 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect1", pThunderEffect1), E_FAIL);
	m_pSKillEffect1 = pThunderEffect1;
	
	CSkillEffect* pThunderEffect2 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect2", pThunderEffect2), E_FAIL);
	m_pSKillEffect2 = pThunderEffect2;

	CSkillEffect* pThunderEffect3 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect3", pThunderEffect3), E_FAIL);
	m_pSKillEffect3 = pThunderEffect3;

	CSkillEffect* pThunderEffect4 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect4", pThunderEffect4), E_FAIL);
	m_pSKillEffect4 = pThunderEffect4;


	CSkillEffect* pThunderEffect5 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect5", pThunderEffect5), E_FAIL);
	m_pSKillEffect5 = pThunderEffect5;


	CSkillEffect* pThunderEffect6 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect6, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect6", pThunderEffect6), E_FAIL);
	m_pSKillEffect6 = pThunderEffect6;

	CSkillEffect* pThunderEffect7 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect7, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect7", pThunderEffect7), E_FAIL);
	m_pSKillEffect7 = pThunderEffect7;

	CSkillEffect* pThunderEffect8 = CEffect_Boss_Thunder_Blue::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect8, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect8", pThunderEffect8), E_FAIL);
	m_pSKillEffect8 = pThunderEffect8;



	// Effect Range Quater - Base
	m_pBaseRangeEffect1 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base1", m_pBaseRangeEffect1), E_FAIL);

	m_pBaseRangeEffect2 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base2", m_pBaseRangeEffect2), E_FAIL);

	m_pBaseRangeEffect3 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base3", m_pBaseRangeEffect3), E_FAIL);

	m_pBaseRangeEffect4 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base4", m_pBaseRangeEffect4), E_FAIL);


	m_pBaseRangeEffect5 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base5", m_pBaseRangeEffect5), E_FAIL);

	m_pBaseRangeEffect6 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect6, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base6", m_pBaseRangeEffect6), E_FAIL);

	m_pBaseRangeEffect7 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect7, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base7", m_pBaseRangeEffect7), E_FAIL);

	m_pBaseRangeEffect8 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect8, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base8", m_pBaseRangeEffect8), E_FAIL);



	// RangeObj
	// 1
	CRangeObj* pGameObject1 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere1 = dynamic_cast<CSphereCollider*>(pGameObject1->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere1->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject1, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere1", pGameObject1);
	m_pRangeObj1 = pGameObject1;
	dynamic_cast<CRangeObj*>(m_pRangeObj1)->Set_Pos(_vec3{ vOwnerPos.x - 20, 0.01f, vOwnerPos.z + 20 });
	m_pRangeObj1->Set_Active(false);


	// 2
	CRangeObj* pGameObject2 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere2 = dynamic_cast<CSphereCollider*>(pGameObject2->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere2->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject2, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere2", pGameObject2);
	m_pRangeObj2 = pGameObject2;
	dynamic_cast<CRangeObj*>(m_pRangeObj2)->Set_Pos(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z + 20 });
	m_pRangeObj2->Set_Active(false);

	// 3
	CRangeObj* pGameObject3 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere3 = dynamic_cast<CSphereCollider*>(pGameObject3->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere3->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject3, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere3", pGameObject3);
	m_pRangeObj3 = pGameObject3;
	dynamic_cast<CRangeObj*>(m_pRangeObj3)->Set_Pos(_vec3{ vOwnerPos.x - 20 , 0.01f, vOwnerPos.z - 20 });

	// 4
	CRangeObj* pGameObject4 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere4 = dynamic_cast<CSphereCollider*>(pGameObject4->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere4->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject4, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere4", pGameObject4);
	m_pRangeObj4 = pGameObject4;
	dynamic_cast<CRangeObj*>(m_pRangeObj4)->Set_Pos(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z - 20 });


	// 5
	CRangeObj* pGameObject5 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere5 = dynamic_cast<CSphereCollider*>(pGameObject5->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere5->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject5, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere5", pGameObject5);
	m_pRangeObj5 = pGameObject5;
	dynamic_cast<CRangeObj*>(m_pRangeObj5)->Set_Pos(_vec3{ vOwnerPos.x + 10 , 0.01f, vOwnerPos.z });


	// 6
	CRangeObj* pGameObject6 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere6 = dynamic_cast<CSphereCollider*>(pGameObject6->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere6->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject6, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere6", pGameObject6);
	m_pRangeObj6 = pGameObject6;
	dynamic_cast<CRangeObj*>(m_pRangeObj6)->Set_Pos(_vec3{ vOwnerPos.x - 10 , 0.01f, vOwnerPos.z });


	// 7
	CRangeObj* pGameObject7 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere7 = dynamic_cast<CSphereCollider*>(pGameObject7->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere7->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject7, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere7", pGameObject7);
	m_pRangeObj7 = pGameObject7;
	dynamic_cast<CRangeObj*>(m_pRangeObj7)->Set_Pos(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z + 10 });


	// 8
	CRangeObj* pGameObject8 = CRangeObj::Create(m_pGraphicDev, this, 5.f);
	CSphereCollider* pShpere8 = dynamic_cast<CSphereCollider*>(pGameObject8->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere8->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject8, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Boss_BloodyThunder_Sphere8", pGameObject8);
	m_pRangeObj8 = pGameObject8;
	dynamic_cast<CRangeObj*>(m_pRangeObj8)->Set_Pos(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z - 10 });






	return S_OK;
}

HRESULT CSkill_Boss_BlueThunder::Play()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// Player - Pos
	_vec3       vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20, 0.01f, vOwnerPos.z+ 20 });
	m_pBaseRangeEffect1->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect1->Scaling(2.f, 0.3f, 1.f);

	// 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z +20 });
	m_pBaseRangeEffect2->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect2->Scaling(2.f, 0.3f, 1.f);

	// 3
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vOwnerPos.x -20 , 0.01f, vOwnerPos.z -20 });
	m_pBaseRangeEffect3->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect3->Scaling(2.f, 0.3f, 1.f);

	// 4
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vOwnerPos.x +20 , 0.01f, vOwnerPos.z -20 });
	m_pBaseRangeEffect4->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect4->Scaling(2.f, 0.3f, 1.f);




	// 5
	m_pBaseRangeEffect5->Play_Effect(_vec3{ vOwnerPos.x + 10 , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect5->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect5->Scaling(2.f, 0.3f, 1.f);

	// 6
	m_pBaseRangeEffect6->Play_Effect(_vec3{ vOwnerPos.x -10 , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect6->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect6->Scaling(2.f, 0.3f, 1.f);

	// 7
	m_pBaseRangeEffect7->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z +10 });
	m_pBaseRangeEffect7->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect7->Scaling(2.f, 0.3f, 1.f);

	// 8
	m_pBaseRangeEffect8->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z -10 });
	m_pBaseRangeEffect8->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect8->Scaling(2.f, 0.3f, 1.f);


	m_bActive = false;

	return S_OK;


}

HRESULT CSkill_Boss_BlueThunder::LatePlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// Player - Pos
	_vec3       vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);




	// 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20.f, 0.01f, vOwnerPos.z + 20.f });
	m_pBaseRangeEffect1->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect1->Scaling(2.f, 0.3f, 1.f);

	// 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20.f , 0.01f, vOwnerPos.z + 20.f });
	m_pBaseRangeEffect2->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect2->Scaling(2.f, 0.3f, 1.f);

	// 3
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vOwnerPos.x - 20.f , 0.01f, vOwnerPos.z - 20.f });
	m_pBaseRangeEffect3->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect3->Scaling(2.f, 0.3f, 1.f);

	// 4
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vOwnerPos.x + 20.f , 0.01f, vOwnerPos.z - 20.f });
	m_pBaseRangeEffect4->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect4->Scaling(2.f, 0.3f, 1.f);


	// 5
	m_pBaseRangeEffect5->Play_Effect(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect5->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect5->Scaling(2.f, 0.3f, 1.f);

	// 6
	m_pBaseRangeEffect6->Play_Effect(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z });
	m_pBaseRangeEffect6->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect6->Scaling(2.f, 0.3f, 1.f);

	// 7
	m_pBaseRangeEffect7->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z + 10.f });
	m_pBaseRangeEffect7->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect7->Scaling(2.f, 0.3f, 1.f);

	// 8
	m_pBaseRangeEffect8->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z -10.f });
	m_pBaseRangeEffect8->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect8->Scaling(2.f, 0.3f, 1.f);




	m_bActive = true;


	m_pRangeObj1->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj1)->Set_Pos(_vec3{ vOwnerPos.x - 20.f, 0.01f, vOwnerPos.z + 20.f });

	m_pRangeObj2->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj2)->Set_Pos(_vec3{ vOwnerPos.x + 20.f , 0.01f, vOwnerPos.z + 20.f });

	m_pRangeObj3->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj3)->Set_Pos(_vec3{ vOwnerPos.x - 20.f , 0.01f, vOwnerPos.z - 20.f });

	m_pRangeObj4->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj4)->Set_Pos(_vec3{ vOwnerPos.x + 20.f , 0.01f, vOwnerPos.z - 20.f });

	m_pRangeObj5->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj5)->Set_Pos(_vec3{ vOwnerPos.x + 10.f , 0.01f, vOwnerPos.z });

	m_pRangeObj6->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj6)->Set_Pos(_vec3{ vOwnerPos.x - 10.f , 0.01f, vOwnerPos.z });

	m_pRangeObj7->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj7)->Set_Pos(_vec3{ vOwnerPos.x  , 0.01f, vOwnerPos.z + 10.f });

	m_pRangeObj8->Set_Active(true);
	dynamic_cast<CRangeObj*>(m_pRangeObj8)->Set_Pos(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z - 10.f });




	_float fSkillEffectScaleY = m_pSKillEffect1->Get_Transform()->Get_Scale().y;


	m_pSKillEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20 , 0.01f  , vOwnerPos.z + 20 });
	m_pSKillEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f  , vOwnerPos.z + 20 });
	m_pSKillEffect3->Play_Effect(_vec3{ vOwnerPos.x - 20 , 0.01f  , vOwnerPos.z - 20 });
	m_pSKillEffect4->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f  , vOwnerPos.z - 20 });


	m_pSKillEffect5->Play_Effect(_vec3{ vOwnerPos.x +10.f , 0.01f  , vOwnerPos.z  });
	m_pSKillEffect6->Play_Effect(_vec3{ vOwnerPos.x -10.f , 0.01f  , vOwnerPos.z  });
	m_pSKillEffect7->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f  , vOwnerPos.z + 10.f });
	m_pSKillEffect8->Play_Effect(_vec3{ vOwnerPos.x  , 0.01f  , vOwnerPos.z - 10.f });



	

	


	return S_OK;
}

HRESULT CSkill_Boss_BlueThunder::End()
{

	 m_pBaseRangeEffect1->Set_Active(false);
	 m_pBaseRangeEffect2->Set_Active(false);
	 m_pBaseRangeEffect3->Set_Active(false);
	 m_pBaseRangeEffect4->Set_Active(false);

	 m_pBaseRangeEffect5->Set_Active(false);
	 m_pBaseRangeEffect6->Set_Active(false);
	 m_pBaseRangeEffect7->Set_Active(false);
	 m_pBaseRangeEffect8->Set_Active(false);


	return S_OK;
}

HRESULT CSkill_Boss_BlueThunder::LateEnd()
{
	

	m_pRangeObj1->Set_Active(false);
	m_pRangeObj2->Set_Active(false);
	m_pRangeObj3->Set_Active(false);
	m_pRangeObj4->Set_Active(false);

	m_pRangeObj5->Set_Active(false);
	m_pRangeObj6->Set_Active(false);
	m_pRangeObj7->Set_Active(false);
	m_pRangeObj8->Set_Active(false);






	m_pSKillEffect1->Set_Active(false);
	m_pSKillEffect2->Set_Active(false);
	m_pSKillEffect3->Set_Active(false);
	m_pSKillEffect4->Set_Active(false);



	m_pSKillEffect5->Set_Active(false);
	m_pSKillEffect6->Set_Active(false);
	m_pSKillEffect7->Set_Active(false);
	m_pSKillEffect8->Set_Active(false);


	m_bActive = false;

	return E_NOTIMPL;
}

CSkill_Boss_BlueThunder* CSkill_Boss_BlueThunder::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSkill_Boss_BlueThunder* pInstance = new CSkill_Boss_BlueThunder(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CSkill_Boss_BlueThunder Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkill_Boss_BlueThunder::Free()
{
	__super::Free();
}
